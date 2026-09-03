/***
 * @          佛曰:
 * @                  写字楼里写字间，写字间里程序员；
 * @                  程序人员写程序，又拿程序换酒钱。
 * @                  酒醒只在网上坐，酒醉还来网下眠；
 * @                  酒醉酒醒日复日，网上网下年复年。
 * @                  但愿老死电脑间，不愿鞠躬老板前；
 * @                  奔驰宝马贵者趣，公交自行程序员。
 * @                  别人笑我忒疯癫，我笑自己命太贱；
 * @                  不见满街漂亮妹，哪个归得程序员？
 * @
 * @Author: your name
 * @Date: 2022-12-03 20:30:41
 * @LastEditTime: 2023-01-06 20:00:18
 * @LastEditors: your name
 * @Description:
 * @FilePath: /tianbot_mini/src/astar_super/src/path_searcher/JPS_searcher.cpp
 * @可以输入预定的版权声明、个性签名、空行等
 */

#include "path_searcher/JPS_searcher.h"
#include <rclcpp/rclcpp.hpp>

using namespace std;
using namespace Eigen;

JPSPathFinder::JPSPathFinder()
{
  jn2d = new JPS2DNeib(); // 创建

  g_method = Manhattan; // 默认使用曼哈顿距离
  h_method = Manhattan; // 默认使用曼哈顿距离

  g_value = 1.0; // 默认权重是1
  h_value = 1.0; // 默认权重是1
}

// 用于传参 (ROS 2 版)
void JPSPathFinder::InitParams(std::shared_ptr<rclcpp::Node> node)
{
	node->declare_parameter<double>("jps_weight/g", 1.0);
	node->declare_parameter<double>("jps_weight/h", 1.0);
	node->declare_parameter<int>("jps_heuristic/distance", 0);
	node->declare_parameter<int>("jps_glength/distance", 0);
	node->declare_parameter<double>("jps_search/radius", 100.0);
	node->declare_parameter<bool>("jps_search/is_use_esdf", false);

	node->get_parameter("jps_weight/g", g_value);
	node->get_parameter("jps_weight/h", h_value);
	node->get_parameter("jps_heuristic/distance", h_method);
	node->get_parameter("jps_glength/distance", g_method);
	node->get_parameter("jps_search/radius", search_radius);
	node->get_parameter("jps_search/is_use_esdf", is_use_esdf);
}

// 获取系统时间 精确到ns (ROS 2 版)
uint64_t JPSPathFinder::getSystemNSec(void)
{
	return rclcpp::Clock().now().nanoseconds();
}

// 判断跳点是否被占据具体实现
inline bool JPSPathFinder::isOccupied(const int &idx_x, const int &idx_y) const
{
  return (idx_x < X_SIZE && idx_y < Y_SIZE && (data[idx_x * Y_SIZE + idx_y] == OBSTACLE));
}

// 判断跳点是否是自由的具体实现形式
inline bool JPSPathFinder::isFree(const int &idx_x, const int &idx_y) const
{
  return (idx_x < X_SIZE && idx_y < Y_SIZE && (data[idx_x * Y_SIZE + idx_y] < OBSTACLE));
}

// 判断跳点是否是自由的
inline bool JPSPathFinder::isFree(const Eigen::Vector2i &index) const
{
  return isFree(index(0), index(1));
}

// 搜索路径判断，原理有点与最优化中的步长加速法相似
inline void JPSPathFinder::JPSGetSucc(GridNodePtr currentPtr, vector<GridNodePtr> &neighborPtrSets, vector<double> &edgeCostSets, vector<double> &aclDist)
{
  // 邻近节点清空
  neighborPtrSets.clear();
  edgeCostSets.clear();
  aclDist.clear();
  // 计算向量模长，其绝对值相加
  const int norm1 = abs(currentPtr->dir(0)) + abs(currentPtr->dir(1));

  int num_neib = jn2d->nsz[norm1][0];  // 邻近节点数
  int num_fneib = jn2d->nsz[norm1][1]; // 强制节点数

  int id = (currentPtr->dir(0) + 1) + 3 * (currentPtr->dir(1) + 1);

  for (int dev = 0; dev < num_neib + num_fneib; ++dev)
  {
    Vector2i neighborIdx; // 邻居节点
    Vector2i expandDir;   // 扩展节点坐标向量形式

    if (dev < num_neib)
    { // 扩展节点坐标，这里可以看作是普通节点
      expandDir(0) = jn2d->ns[id][0][dev];
      expandDir(1) = jn2d->ns[id][1][dev];

      // 跳点检测
      if (!jump(currentPtr->index, expandDir, neighborIdx))
        continue;
    }
    else
    {
      int nx = currentPtr->index(0) + jn2d->f1[id][0][dev - num_neib];
      int ny = currentPtr->index(1) + jn2d->f1[id][1][dev - num_neib];

      // 判断当前节点是否被占据
      if (isOccupied(nx, ny))
      {
        expandDir(0) = jn2d->f2[id][0][dev - num_neib];
        expandDir(1) = jn2d->f2[id][1][dev - num_neib];

        // 如果跳点失败，那么结束当前循环，进行下一轮循环
        if (!jump(currentPtr->index, expandDir, neighborIdx))
          continue;
      }
      else
        continue;
    }

    GridNodePtr nodePtr = GridNodeMap[neighborIdx(0)][neighborIdx(1)];
    nodePtr->dir = expandDir;

    // 跳点搜索结束开始设定节点
    neighborPtrSets.push_back(nodePtr);
    double dist = 0.0; // 用于计算历史代价数值
    switch (g_method)
    {
    case Euclidean:
    {
      double dx = abs((double)(neighborIdx(0) - currentPtr->index(0)));
      double dy = abs((double)(neighborIdx(1) - currentPtr->index(1)));
      dist = std::sqrt((std::pow(dx, 2.0) + std::pow(dy, 2.0)));
      break;
    }
    case Manhattan:
    {
      double dx = abs((double)(neighborIdx(0) - currentPtr->index(0)));
      double dy = abs((double)(neighborIdx(1) - currentPtr->index(1)));
      dist = dx + dy;
      break;
    }
    case L_infty:
    {
      double dx = abs((double)(neighborIdx(0) - currentPtr->index(0)));
      double dy = abs((double)(neighborIdx(1) - currentPtr->index(1)));
      dist = std::max({dx, dy});
      break;
    }
    case Diagonal:
    {
      double Distance[2];
      Distance[0] = abs((double)(neighborIdx(0) - currentPtr->index(0)));
      Distance[1] = abs((double)(neighborIdx(1) - currentPtr->index(1)));
      std::sort(Distance, Distance + 2);
      dist = Distance[0] + Distance[1] + (std::sqrt(2.0) - 2) * Distance[0];
      break;
    }

    default:
      break;
    }
    dist = dist * g_value; // 距离*权重
    // 用欧氏距离计算g数值
    edgeCostSets.push_back(dist);

    double distance = sqrt(
        (neighborIdx(0) - currentPtr->index(0)) * (neighborIdx(0) - currentPtr->index(0)) +
        (neighborIdx(1) - currentPtr->index(1)) * (neighborIdx(1) - currentPtr->index(1)));
    aclDist.push_back(distance);
  }
}

// 跳点路径搜索判断点是否可用
bool JPSPathFinder::jump(const Vector2i &curIdx, const Vector2i &expDir, Vector2i &neiIdx)
{
  neiIdx = curIdx + expDir;

  if (!isFree(neiIdx)) // 此点非空无法跳点
    return false;

  if (neiIdx == goalIdx) // 如果是目标点可以跳
    return true;

  if (hasForced(neiIdx, expDir)) // 如果是强制节点可以跳
    return true;

  const int id = (expDir(0) + 1) + 3 * (expDir(1) + 1);
  const int norm1 = abs(expDir(0)) + abs(expDir(1));
  int num_neib = jn2d->nsz[norm1][0];

  for (int k = 0; k < num_neib - 1; ++k)
  {
    Vector2i newNeiIdx;
    Vector2i newDir(jn2d->ns[id][0][k], jn2d->ns[id][1][k]);
    if (jump(neiIdx, newDir, newNeiIdx))
      return true;
  }

  return jump(neiIdx, expDir, neiIdx);
}

// 判断是否已经强制
inline bool JPSPathFinder::hasForced(const Vector2i &idx, const Vector2i &dir)
{
  int norm1 = abs(dir(0)) + abs(dir(1));
  int id = (dir(0) + 1) + 3 * (dir(1) + 1);

  switch (norm1)
  {
  case 1:
    for (int fn = 0; fn < 2; ++fn)
    {
      int nx = idx(0) + jn2d->f1[id][0][fn];
      int ny = idx(1) + jn2d->f1[id][1][fn];
      if (isOccupied(nx, ny))
        return true;
    }
    return false;

  case 2:
    for (int fn = 0; fn < 2; ++fn)
    {
      int nx = idx(0) + jn2d->f1[id][0][fn];
      int ny = idx(1) + jn2d->f1[id][1][fn];
      if (isOccupied(nx, ny))
        return true;
    }
    return false;
  default:
    return false;
  }
}

// JPS路径搜索，直接放入世界坐标系下的坐标即可进行搜索
int JPSPathFinder::JPSWorldSearch(Vector2d startpoint, Vector2d endpoint)
{
  Vector2i node1, node2;
  worldToMap(startpoint[0], startpoint[1], node1[0], node1[1]);
  worldToMap(endpoint[0], endpoint[1], node2[0], node2[1]);

  return JPSGraphSearch(node1, node2);
}

int JPSPathFinder::JPSGraphSearch(Eigen::Vector2i start_pt, Eigen::Vector2i end_pt)
{
  uint64_t time_1 = getSystemNSec();

  if (isOccupied(start_pt[0], start_pt[1]))
  {
    std::cout << "start point is" << start_pt[0] << "  " << end_pt[1] << std::endl;
    std::cout << "failed to get a path.start point is obstacle." << std::endl;
    return IN_OCCUPIED;
  }
  if (isOccupied(end_pt[0], end_pt[1]))
  {
    std::cout << "target point is" << end_pt[0] << "  " << end_pt[1] << std::endl;
    std::cout << "failed to get a path.target point is obstacle." << std::endl;
    return IN_OCCUPIED;
  }

  GridNodePtr startPtr = GridNodeMap[start_pt(0)][start_pt(1)];
  GridNodePtr endPtr = GridNodeMap[end_pt(0)][end_pt(1)];

  startpoint = start_pt;
  endpoint = end_pt;

  goalIdx = end_pt;

  openSet.clear();

  GridNodePtr currentPtr = NULL;
  GridNodePtr neighborPtr = NULL;

  startPtr->gScore = 0;
  startPtr->fScore = h_value * getHeu(startPtr, endPtr);
  startPtr->aclDistance = 0;

  startPtr->id = 1;
  startPtr->nodeMapIt = openSet.insert(make_pair(startPtr->fScore, startPtr));

  double tentative_gScore;
  vector<GridNodePtr> neighborPtrSets;
  vector<double> edgeCostSets;
  vector<double> aclDist;

	const int tolerance = ceil(1/resolution_);

  while (!openSet.empty())
  {
    currentPtr = openSet.begin()->second;
    currentPtr->id = -1;

		double tempWorldx,tempWorldy;
		mapToWorld(currentPtr->index(0),currentPtr->index(1),tempWorldx,tempWorldy);
		double startWorldx,startWorldy;
		mapToWorld(startPtr->index(0),startPtr->index(1),startWorldx,startWorldy);

		bool reach_horizon = sqrt(
															pow(abs(tempWorldx-startWorldx),2)+
															pow(abs(tempWorldy-startWorldy),2)
															) >= search_radius;

		bool near_end = abs(currentPtr->index(0) - endPtr->index(0) <= tolerance) &&
											abs(currentPtr->index(1) - endPtr->index(1)) <= tolerance;
		
		bool is_shot_succ_ = false;
		if(reach_horizon || near_end)
		{
			terminatePtr = currentPtr;
		}

    if (reach_horizon)
    {
			std::cout << "reach horizon" << std::endl;
			return REACH_HORIZON;
    }

    openSet.erase(openSet.begin());

    JPSGetSucc(currentPtr, neighborPtrSets, edgeCostSets, aclDist);

    for (int i = 0; i < (int)neighborPtrSets.size(); i++)
    {
      neighborPtr = neighborPtrSets[i];

      tentative_gScore = currentPtr->gScore + edgeCostSets[i];
      double tentative_aclDist = currentPtr->aclDistance + aclDist[i];

      if (neighborPtr->id == 0)
      {
        neighborPtr->gScore = tentative_gScore;
        neighborPtr->fScore = neighborPtr->gScore + h_value * getHeu(neighborPtr, endPtr);
        neighborPtr->aclDistance = tentative_aclDist;
        neighborPtr->cameFrom = currentPtr;

        for (int i = 0; i < 2; i++)
        {
          neighborPtr->dir(i) = neighborPtr->index(i) - currentPtr->index(i);
          if (neighborPtr->dir(i) != 0)
            neighborPtr->dir(i) /= abs(neighborPtr->dir(i));
        }

        neighborPtr->nodeMapIt = openSet.insert(make_pair(neighborPtr->fScore, neighborPtr));

        if (neighborPtr->index == goalIdx)
        {
          uint64_t time_2 = getSystemNSec();
          terminatePtr = neighborPtr;
          JPSLastParams.lastTime = (double)(time_2 - time_1) / 10000000;
          JPSLastParams.lastDist = currentPtr->aclDistance;
          findFlag = true;
          return REACH_END;
        }
        else
        {
          neighborPtr->id = 1;
          continue;
        }
      }
      else if (neighborPtr->id == 1 && tentative_gScore <= neighborPtr->gScore)
      {
        neighborPtr->gScore = tentative_gScore;
        neighborPtr->aclDistance = tentative_aclDist;

        neighborPtr->fScore = neighborPtr->gScore + h_value * getHeu(neighborPtr, endPtr);
        neighborPtr->cameFrom = currentPtr;

        for (int i = 0; i < 2; i++)
        {
          neighborPtr->dir(i) = neighborPtr->index(i) - currentPtr->index(i);
          if (neighborPtr->dir(i) != 0)
            neighborPtr->dir(i) /= abs(neighborPtr->dir(i));
        }

        openSet.erase(neighborPtr->nodeMapIt);
        neighborPtr->nodeMapIt = openSet.insert(make_pair(neighborPtr->fScore, neighborPtr));
      }
      else
      {
        continue;
      }
    }
  }
  uint64_t time_2 = getSystemNSec();
  if (time_2 - time_1 > 100000000)
  {
    std::cout << "Time consume in Astar path finding is " << (time_2 - time_1) << std::endl;
    std::cout << "Path find failed." << std::endl;
    findFlag = false;
  }
  return NO_PATH;
}

vector<Vector2i> JPSPathFinder::getJPSPath()
{
  vector<Vector2i> path;
  vector<GridNodePtr> gridPath;

  GridNodePtr tmp_ptr = terminatePtr;
  while (tmp_ptr->cameFrom != NULL)
  {
    gridPath.push_back(tmp_ptr);
    tmp_ptr = tmp_ptr->cameFrom;
  }

  for (auto ptr : gridPath)
    path.push_back(ptr->index);

  path.push_back(startpoint);

  reverse(path.begin(), path.end());

  double firstDis;
  Vector2i fistNode = path[1];
  firstDis = sqrt(
      (double)((fistNode(0) - startpoint(0)) * (fistNode(0) - startpoint(0))) +
      (double)((fistNode(1) - startpoint(1)) * (fistNode(1) - startpoint(1))));

  world_distance = firstDis + JPSLastParams.dist;

  return path;
}

// 获取世界路径，最终在世界坐标系下的路径
vector<Vector2d> JPSPathFinder::getJPSWorldPath(void)
{
  vector<Vector2d> path;
  vector<GridNodePtr> gridPath;

  GridNodePtr tmp_ptr = terminatePtr;
  while (tmp_ptr->cameFrom != NULL)
  {
    gridPath.push_back(tmp_ptr);
    tmp_ptr = tmp_ptr->cameFrom;
  }

  for (auto ptr : gridPath)
  {
    Vector2d worldpoint;
    mapToWorld(ptr->index[0], ptr->index[1], worldpoint[0], worldpoint[1]);
    path.push_back(worldpoint);
  }

  Vector2d worldpoint;
  mapToWorld(startpoint[0], startpoint[1], worldpoint[0], worldpoint[1]);
  path.push_back(worldpoint);

  reverse(path.begin(), path.end());

  double firstDis;
  Vector2i firstNode = startpoint;
  worldToMap(path[0][0], path[1][1], firstNode[0], firstNode[1]);
  firstDis = sqrt(
      (double)((firstNode[0] - startpoint[0]) * (firstNode[0] - startpoint[0])) +
      (double)((firstNode[1] - startpoint[1]) * (firstNode[1] - startpoint[1])));

  world_distance = firstDis + JPSLastParams.dist;

  return path;
}