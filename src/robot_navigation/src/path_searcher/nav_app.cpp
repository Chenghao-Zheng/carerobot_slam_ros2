/***
 * @                       _oo0oo_
 * @                      o8888888o
 * @                      88" . "88
 * @                      (| --_- |)
 * @                      0\  =  /0
 * @                    ___/`---'\___
 * @                  .' \\|     |// '.
 * @                 / \\|||  :  |||// \
 * @                / _||||| -:- |||||- \
 * @               |   | \\\  - /// |   |
 * @               | \_|  ''\---/''  |_/ |
 * @               \  .-\__  '-'  ___/-. /
 * @             ___'. .'  /--.--\  `. .'___
 * @           me"" '<  `.___\_<|>_/___.' >' "".
 * @         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 * @         \  \ `_.   \_ __\ /__ _/   .-` /  /
 * @     =====`-.____`.___ \_____/___.-`___.-'=====
 * @                       `=---='
 * @
 * @
 * @     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @
 * @           佛祖保佑     永不宕机     永无BUG
 * @
 * @Author: your name
 * @Date: 2022-12-06 15:06:40
 * @LastEditTime: 2026-08-31
 * @FilePath: /tianbot_mini/src/astar_super/src/path_searcher/nav_app.cpp
 */

#include "path_searcher/nav_app.h"

// 构造函数：继承 rclcpp::Node
navSolution::navSolution(int flag) : Node("nav_solution_node")
{
  this->choose = flag;
  this->All();

  // ROS 2 推荐在主函数中 spin，若在构造函数中维持循环可使用 rclcpp::spin_some
  rclcpp::Rate loop_rate(50);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(this->get_node_base_interface());
    loop_rate.sleep();
  }

  delete jps_path_finder;
  delete astar_path_finder;
  delete rrt_path_finder;
  delete hybrid_astar_finder;
}

// A*搜索全局路径
// 优化并发布
void navSolution::AstarFindPath(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint)
{
  RCLCPP_INFO(this->get_logger(), "\033[1;32m A* find path! \033[0m");
  is_use_jps = false;
  rclcpp::Time time_3 = this->now();
  astar_path_finder->AstarWorldSearch(startMapPoint, goalMapPoint);
  rclcpp::Time time_4 = this->now();
  pathNav.worldpath = astar_path_finder->getWorldPath();               // 获取路径
  pathNav.visitWorldNodes = astar_path_finder->getVisitedWorldNodes(); // 获取访问节点
  astar_path_finder->resetUsedGrids();                                 // 复位已经访问的地图
  visual_VisitedNode(visited_nodes_pub, pathNav.visitWorldNodes);      // 可视化访问节点
  PublishPath(PathPub_Astar, pathNav.worldpath);                       // 发布路径
  RCLCPP_INFO(this->get_logger(), "\033[1;32m time is %f ms,path size is %ld \033[0m",
              (time_4 - time_3).seconds() * 1000.0, pathNav.worldpath.size());

  rclcpp::Time start_time = this->now();
  // pathNav.optpath = MinimumSnapFlow.Minimum_Snap(pathNav.worldpath);
  // pathNav.optpath = MinimumSnapFlow.SubsectionPath_Minimum_Snap(pathNav.worldpath);
  pathNav.optpath = Bezier_Flow.SubsectionPath_Bezier(pathNav.worldpath);
  rclcpp::Time end_time = this->now();
  RCLCPP_INFO(this->get_logger(), "\033[1;32m --> Time in Minimum Snap is %f ms  \033[0m",
              (end_time - start_time).seconds() * 1000.0);
  PublishPath(trajectory_pub_, pathNav.optpath);
}

// rrt搜索全局路径
// 优化并发布
void navSolution::rrtFindPath(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint)
{
  RCLCPP_INFO(this->get_logger(), "\033[1;32m RRT* find path! \033[0m");
  rclcpp::Time time_1 = this->now();
  rrt_path_finder->FindPath(startMapPoint, goalMapPoint);
  rclcpp::Time time_2 = this->now();
  pathNav.worldpath = rrt_path_finder->path; // 获取路径

  RCLCPP_INFO(this->get_logger(), "\033[1;32m time is %f ms,path size is %ld \033[0m",
              (time_2 - time_1).seconds() * 1000.0, pathNav.worldpath.size());

  PublishPath(PathPub_RRT, pathNav.worldpath); // 发布路径

#if 0
  rclcpp::Time start_time = this->now();
  pathNav.optpath = MinimumSnapFlow.Minimum_Snap(pathNav.worldpath);
  rclcpp::Time end_time = this->now();
  RCLCPP_INFO(this->get_logger(), "\033[1;32m --> Time in Minimum Snap is %f ms  \033[0m",
              (end_time - start_time).seconds() * 1000.0);
  PublishPath(trajectory_pub_, pathNav.optpath);
#endif
}

// JPS搜索全局路径
// 优化并发布
void navSolution::JPSFindPath(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint)
{
  RCLCPP_INFO(this->get_logger(), "\033[1;32m JPS finding path! \033[0m");
  is_use_jps = true;
  rclcpp::Time time_1 = this->now();
  jps_path_finder->JPSWorldSearch(startMapPoint, goalMapPoint);
  rclcpp::Time time_2 = this->now();
  pathNav.worldpath = jps_path_finder->getJPSWorldPath();            // 获取路径
  pathNav.visitWorldNodes = jps_path_finder->getVisitedWorldNodes(); // 获取访问节点
  jps_path_finder->resetUsedGrids();                                 // 复位已经访问的地图

  RCLCPP_INFO(this->get_logger(), "\033[1;32m time is %f ms,path size is %ld \033[0m",
              (time_2 - time_1).seconds() * 1000.0, pathNav.worldpath.size());

  visual_VisitedNode(visited_nodes_pub, pathNav.visitWorldNodes); // 可视化访问节点
  PublishPath(PathPub_JPS, pathNav.worldpath);                    // 发布路径

  rclcpp::Time start_time = this->now();
  pathNav.optpath = MinimumSnapFlow.Minimum_Snap(pathNav.worldpath);
  rclcpp::Time end_time = this->now();
  RCLCPP_INFO(this->get_logger(), "\033[1;32m --> Time in Minimum Snap is %f ms  \033[0m",
              (end_time - start_time).seconds() * 1000.0);
  PublishPath(trajectory_pub_, pathNav.optpath);
}

void navSolution::HybridAstarFindPath(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint)
{
  RCLCPP_INFO(this->get_logger(), "Start find path with HybridAstar");

  hybrid_astar_finder->reset();
  // 记录路径搜索需要的时间
  rclcpp::Time time_1 = this->now();
  int status = hybrid_astar_finder->search(startMapPoint, Eigen::Vector2d(0.0, 0.0), Eigen::Vector2d(1.0, 1.0),
                                            goalMapPoint, Eigen::Vector2d(0, 0), true);
  rclcpp::Time time_2 = this->now();

  // 如果没有找到
  if (status == Hybrid_astar::NO_PATH) {
    std::cout << "[kino replan]: kinodynamic search fail!" << std::endl;

    // 再次复位
    hybrid_astar_finder->reset();
    // 重新搜索
    status = hybrid_astar_finder->search(startMapPoint, Eigen::Vector2d(0.0, 0.0), Eigen::Vector2d(1.0, 1.0),
                                          goalMapPoint, Eigen::Vector2d(0, 0), false);

    // 两次搜索还是没有找到 寄了
    if (status == Hybrid_astar::NO_PATH) {
      std::cout << "[kino replan]: Can't find path." << std::endl;
    } else {
      std::cout << "[kino replan]: retry search success." << std::endl;
    }
  }

  pathNav.worldpath = hybrid_astar_finder->getKinoTraj(0.01); //获取路径
  RCLCPP_INFO(this->get_logger(), "time is %fms,path size is %ld", (time_2 - time_1).seconds() * 1000.0, pathNav.worldpath.size());

  PublishPath(PathPub_Hybrid, pathNav.worldpath);  
}

void navSolution::StartFindPath(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint)
{
  RCLCPP_INFO(this->get_logger(), "\033[1;32m start: %f %f \033[0m",
              startMapPoint[0], startMapPoint[1]);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m goal: %f %f \033[0m",
              goalMapPoint[0], goalMapPoint[1]);
  // 记录路径搜索需要的时间
  if (this->choose == 1)
  {
    JPSFindPath(startMapPoint, goalMapPoint);
  }
  else if (this->choose == 2)
  {
    AstarFindPath(startMapPoint, goalMapPoint);
  }
  else if (this->choose == 3)
  {
    rrtFindPath(startMapPoint, goalMapPoint);
  }
  else if(this->choose == 4)
  {
    HybridAstarFindPath(startMapPoint, goalMapPoint);
  }
  else if (this->choose == 5)
  {
    JPSFindPath(startMapPoint, goalMapPoint);
    AstarFindPath(startMapPoint, goalMapPoint);
    rrtFindPath(startMapPoint, goalMapPoint);
    HybridAstarFindPath(startMapPoint, goalMapPoint);
  }
}

void navSolution::MapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
{
  pathNav.origin_x = msg->info.origin.position.x; // 获得栅格地图的原点x值(相对世界坐标系),单位为m
  pathNav.origin_y = msg->info.origin.position.y; // 获得栅格地图的原点y值(相对世界坐标系),单位为m
  pathNav.resolution = msg->info.resolution;      // 获得栅格地图的分辨率
  pathNav.width = msg->info.width;                // 获得栅格地图的宽
  pathNav.height = msg->info.height;              // 获得栅格地图的高
  RCLCPP_INFO(this->get_logger(), "\033[1;32m ***********map message**********\033[0m");
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_x: %f  \033[0m", pathNav.origin_x);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_y: %f  \033[0m", pathNav.origin_y);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m resolution: %f  \033[0m", pathNav.resolution);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m width: %d  \033[0m", pathNav.width);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m height: %d  \033[0m", pathNav.height);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m *********************************\033[0m");

  NavtfGrid(msg, pathNav.mapData, pathNav.width, pathNav.height);
  mapInit(); // 地图初始化
}

void navSolution::NavtfGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr &data, std::vector<int> &map, int x_size, int y_size)
{
  map.resize(x_size * y_size);
  for (int i = 0; i < x_size; i++)
  {
    for (int j = 0; j < y_size; j++)
    { /* 将ros解析的地图转变为正常的先行后列的顺序 */
      map[i * y_size + j] = int(data->data[j * x_size + i]);
    }
  }
}

void navSolution::mapInit(void)
{
  astar_path_finder = new AstarPathFinder(); // 重置
  jps_path_finder = new JPSPathFinder();     
  rrt_path_finder = new RRTstarPlanner();

  if (this->choose == 1)
  {
    jps_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                             pathNav.width, pathNav.height, pathNav.mapData);
  }
  else if (this->choose == 2)
  {
    astar_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                               pathNav.width, pathNav.height, pathNav.mapData);
  }
  else if (this->choose == 3)
  {
    rrt_path_finder->initMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                             pathNav.width, pathNav.height, pathNav.mapData);
  }
  else if(this->choose == 4)
  {
    hybrid_astar_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                                 pathNav.width, pathNav.height, pathNav.mapData);
  }
  else if (this->choose == 5)
  {
    jps_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                             pathNav.width, pathNav.height, pathNav.mapData);
    astar_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                               pathNav.width, pathNav.height, pathNav.mapData);
    rrt_path_finder->initMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                             pathNav.width, pathNav.height, pathNav.mapData);
    hybrid_astar_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                                 pathNav.width, pathNav.height, pathNav.mapData);
  }
}

void navSolution::StartPoseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = "map";
  node_vis.header.stamp = this->now();
  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  node_vis.id = 0;

  node_vis.pose.orientation.x = 0.0;
  node_vis.pose.orientation.y = 0.0;
  node_vis.pose.orientation.z = 0.0;
  node_vis.pose.orientation.w = 1.0;

  node_vis.color.a = 1.0;
  node_vis.color.r = 1.0;
  node_vis.color.g = 0.0;
  node_vis.color.b = 0.0;

  node_vis.scale.x = pathNav.resolution * 2;
  node_vis.scale.y = pathNav.resolution * 2;
  node_vis.scale.z = pathNav.resolution * 2;
  geometry_msgs::msg::Point pt;
  pt.x = msg->pose.pose.position.x;
  pt.y = msg->pose.pose.position.y;
  pt.z = 0.0;
  RCLCPP_INFO(this->get_logger(), "Start x:%f y:%f", pt.x, pt.y);
  node_vis.points.push_back(pt);

  StartPoint->publish(node_vis);
}

void navSolution::GoalPoseCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = "map";
  node_vis.header.stamp = this->now();
  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  node_vis.id = 0;

  node_vis.pose.orientation.x = 0.0;
  node_vis.pose.orientation.y = 0.0;
  node_vis.pose.orientation.z = 0.0;
  node_vis.pose.orientation.w = 1.0;

  node_vis.color.a = 1.0;
  node_vis.color.r = 0.0;
  node_vis.color.g = 0.0;
  node_vis.color.b = 1.0;
  node_vis.scale.x = pathNav.resolution * 2;
  node_vis.scale.y = pathNav.resolution * 2;
  node_vis.scale.z = pathNav.resolution * 2;

  geometry_msgs::msg::Point pt;
  pt.x = msg->pose.position.x;
  pt.y = msg->pose.position.y;
  pt.z = 0.0;
  node_vis.points.push_back(pt);
  GoalPoint->publish(node_vis);

  pathNav.goalMapPoint[0] = pt.x;
  pathNav.goalMapPoint[1] = pt.y;

  pathNav.startMapPoint[0] = pathNav.start_x;
  pathNav.startMapPoint[1] = pathNav.start_y;

  // 搜索路径
  StartFindPath(pathNav.startMapPoint, pathNav.goalMapPoint);
}

void navSolution::PublishPath(rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pathPublish, std::vector<Eigen::Vector2d> path)
{
  nav_msgs::msg::Path pathTopic;
  pathTopic.poses.clear();
  for (unsigned int i = 0; i < path.size(); i++)
  {
    geometry_msgs::msg::PoseStamped pathPose;
    pathPose.pose.position.x = path[i][0];
    pathPose.pose.position.y = path[i][1];
    pathPose.pose.position.z = 0;

    pathPose.pose.orientation.x = 0.0;
    pathPose.pose.orientation.y = 0.0;
    pathPose.pose.orientation.z = 0.0;
    pathPose.pose.orientation.w = 1.0;
    pathTopic.header.stamp = this->now();
    pathTopic.header.frame_id = "odom";
    pathTopic.poses.push_back(pathPose);
  }
  pathPublish->publish(pathTopic);
}

void navSolution::visual_VisitedNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish, std::vector<Eigen::Vector2d> visitnodes)
{
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = "map";
  node_vis.header.stamp = this->now();

  if (is_use_jps)
  {
    node_vis.ns = "demo_node/jps_path";
    node_vis.color.a = 0.25;
    node_vis.color.r = 1.0;
    node_vis.color.g = 0.0;
    node_vis.color.b = 0.0;
  }
  else
  {
    node_vis.color.a = 0.25;
    node_vis.color.r = 0.0;
    node_vis.color.g = 1.0;
    node_vis.color.b = 0.0;
    node_vis.ns = "demo_node/astar_path";
  }

  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  node_vis.id = 0;

  node_vis.pose.orientation.x = 0.0;
  node_vis.pose.orientation.y = 0.0;
  node_vis.pose.orientation.z = 0.0;
  node_vis.pose.orientation.w = 1.0;

  node_vis.scale.x = pathNav.resolution * 2;
  node_vis.scale.y = pathNav.resolution * 2;
  node_vis.scale.z = pathNav.resolution * 2;

  geometry_msgs::msg::Point pt;
  for (int i = 0; i < int(visitnodes.size()); i++)
  {
    pt.x = visitnodes[i][0];
    pt.y = visitnodes[i][1];
    node_vis.points.push_back(pt);
  }

  pathPublish->publish(node_vis);
}

void navSolution::All(void)
{
  // ROS 2 话题发布者创建
  PathPub_JPS = this->create_publisher<nav_msgs::msg::Path>("/pathJPS", 15);
  PathPub_Astar = this->create_publisher<nav_msgs::msg::Path>("/pathAstar", 15);
  PathPub_RRT = this->create_publisher<nav_msgs::msg::Path>("/pathRRTstar", 15);
  PathPub_Hybrid = this->create_publisher<nav_msgs::msg::Path>("/pathHybrid", 15);

  trajectory_pub_ = this->create_publisher<nav_msgs::msg::Path>("generated_trajectory", 10);
  
  // ROS 2 订阅者创建
  mapSub = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
    "/map", 1, std::bind(&navSolution::MapCallback, this, std::placeholders::_1));
  startSub = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
    "/initialpose", 1, std::bind(&navSolution::StartPoseCallback, this, std::placeholders::_1));
  goalSub = this->create_subscription<geometry_msgs::msg::PoseStamped>(
    "/goal", 1, std::bind(&navSolution::GoalPoseCallback, this, std::placeholders::_1));

  StartPoint = this->create_publisher<visualization_msgs::msg::Marker>("/start_point", 1);
  GoalPoint = this->create_publisher<visualization_msgs::msg::Marker>("/goal_point", 1);
  visited_nodes_pub = this->create_publisher<visualization_msgs::msg::Marker>("visited_nodes_vis", 1);

  // 参数声明与获取
  double astar_weight_g = this->declare_parameter<double>("astar_weight.g", 1.0);
  double astar_weight_h = this->declare_parameter<double>("astar_weight.h", 1.0);
  int astar_heuristic = this->declare_parameter<int>("astar_heuristic.distance", 0);
  int astar_glength = this->declare_parameter<int>("astar_glength.distance", 0);

  double jps_weight_g = this->declare_parameter<double>("jps_weight.g", 1.0);
  double jps_weight_h = this->declare_parameter<double>("jps_weight.h", 1.0);
  int jps_heuristic = this->declare_parameter<int>("jps_heuristic.distance", 0);
  int jps_glength = this->declare_parameter<int>("jps_glength.distance", 0);

  astar_path_finder->setParams(astar_weight_g, astar_weight_h, astar_glength, astar_heuristic);
  jps_path_finder->setParams(jps_weight_g, jps_weight_h, jps_glength, jps_heuristic);
  hybrid_astar_finder->InitParams(this->shared_from_this());

  double max_vel = this->declare_parameter<double>("minimum_snap.max_vel", 1.0);
  double max_acce = this->declare_parameter<double>("minimum_snap.max_acce", 1.0);
  int order = this->declare_parameter<int>("minimum_snap.order", 3);
  MinimumSnapFlow.setParams(order, max_vel, max_acce);

  // 固定起点
  pathNav.start_x = this->declare_parameter<double>("planning.start_x", 2.0);
  pathNav.start_y = this->declare_parameter<double>("planning.start_y", 0.0);
}