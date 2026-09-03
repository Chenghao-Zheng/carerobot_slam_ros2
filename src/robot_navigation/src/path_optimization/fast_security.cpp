#include "path_optimization/fast_security.h"

Fast_Security::Fast_Security(/* args */)
{

}

Fast_Security::~Fast_Security()
{
}

void Fast_Security::InitParams(rclcpp::Node::SharedPtr nh)
{
  // 查看访问点
  visitNodesPub = nh->create_publisher<visualization_msgs::msg::Marker>("/STATE_VISITED_nodes", 10);
  // 查看选出来的优化点
  visitOptpathPub = nh->create_publisher<visualization_msgs::msg::Marker>("/Opt_path_visit", 10);
  // 查看采样点
  sampleNodesPub = nh->create_publisher<visualization_msgs::msg::Marker>("/Sample_node", 10);
  // 查看连续点
  continuNodesPub = nh->create_publisher<visualization_msgs::msg::Marker>("/Continu_node", 10);
  // 查看补充扩展节点
  suppleMentPub = nh->create_publisher<visualization_msgs::msg::Marker>("/Supplement_node", 10);

  // 获取安全走廊搜索长度或者说宽度
  // 最小按照实车半径去给,这里保守一点给2.0
  nh->declare_parameter("Fast_security/search_length", 2.0);
  nh->get_parameter("Fast_security/search_length", search_length);

  // 获取连续部分走廊系数
  // 距离场系数
  nh->declare_parameter("Fast_security/Kcontinu_esdf", 1.0);
  nh->get_parameter("Fast_security/Kcontinu_esdf", Kcontinu_esdf);
  // 到上一个点距离代价系数
  nh->declare_parameter("Fast_security/Kcontinu_ldis", 1.0);
  nh->get_parameter("Fast_security/Kcontinu_ldis", Kcontinu_ldis);
  // 到终点部分距离代价系数
  nh->declare_parameter("Fast_security/Kcontinu_edis", 1.0);
  nh->get_parameter("Fast_security/Kcontinu_edis", Kcontinu_edis);

  // 获取间断部分走廊系数
  // 距离场系数
  nh->declare_parameter("Fast_security/Kinterru_esdf", 1.0);
  nh->get_parameter("Fast_security/Kinterru_esdf", Kinterru_esdf);
  // 到上一个点距离代价系数
  nh->declare_parameter("Fast_security/Kinterru_ldis", 1.0);
  nh->get_parameter("Fast_security/Kinterru_ldis", Kinterru_ldis);
  // 到终点部分距离代价系数
  nh->declare_parameter("Fast_security/Kinterru_edis", 1.0);
  nh->get_parameter("Fast_security/Kinterru_edis", Kinterru_edis);
  // 重合点系数
  nh->declare_parameter("Fast_security/Kinterru_rep", 1.0);
  nh->get_parameter("Fast_security/Kinterru_rep", Kinterru_rep);

  // 获取阶梯部分走廊系数
  // 距离场系数
  nh->declare_parameter("Fast_security/Kstep_esdf", 1.0);
  nh->get_parameter("Fast_security/Kstep_esdf", Kstep_esdf);
  // 到上一个点距离代价系数
  nh->declare_parameter("Fast_security/Kstep_ldis", 1.0);
  nh->get_parameter("Fast_security/Kstep_ldis", Kstep_ldis);
  // 到终点部分距离代价系数
  nh->declare_parameter("Fast_security/Kstep_edis", 1.0);
  nh->get_parameter("Fast_security/Kstep_edis", Kstep_edis);
  // 重合点系数
  nh->declare_parameter("Fast_security/Kstep_rep", 1.0);
  nh->get_parameter("Fast_security/Kstep_rep", Kstep_rep);

}

// 复位访问的节点
void Fast_Security::resetSTATE_VISITED(void)
{
  // 清空优化路径
  optpath.clear();
  // 连续点集合
  continuAssem.clear();
  // 垂直与连续点的向量清空
  vercontAssem.clear();

  // 分段清0
  dividePath.clear();
  // 垂直于分段的向量清0
  verdividePath.clear();
  // 连续分段
  continuDivid.clear();
  // 垂直于连续分段
  vercontinuDivid.clear();

  // 栅格路径清0
  origingridPath.clear();
  // 优化路径清0
  optedpath.clear();

  visualOptpoints.clear();
}

/**
 * @brief 栅格地图坐标系转世界坐标系
 * @param mx   地图坐标x
 * @param my   地图坐标y
 * @param wx   世界坐标x
 * @param wy   世界坐标y
 * @return
 * @attention
 * @todo
 * */
Vector2d Fast_Security::mapToWorld(Vector2i mapt) const
{
  double wx,wy;
  wx = origin_x + (mapt[0] + 0.5) * resolution;
  wy = origin_y + (mapt[1] + 0.5) * resolution;

  return Vector2d(wx,wy);
}

/**
 * @brief 世界坐标系转栅格地图坐标系
 * @param wx   世界坐标x
 * @param wy   世界坐标y        if(isOccupied(pointS))
      {
        break;
      }
  * @param mx   地图坐标x
  * @param my   地图坐标y
  * @return
  * @attention
  * @todo
  * */
Vector2i Fast_Security::worldToMap(Vector2d worldpt) const
{
  int mx,my;

  mx = (int)(1.0 * (worldpt[0] - origin_x) * resolution_inv);
  my = (int)(1.0 * (worldpt[1] - origin_y) * resolution_inv);

  return Vector2i(mx,my);
}

// 判断是否在地图中
bool Fast_Security::isInMap(Eigen::Vector2d worldpt)
{
  if (worldpt(0) < origin_x || worldpt(1) < origin_y)
  {
    return false;
  }

  if (worldpt(0) > mapover_x || worldpt(1) > mapover_y)
  {
    return false;
  }

  return true;
}

// 判断点是否被占据的具体实现形式
bool Fast_Security::isOccupied(const Vector2d worldpt) const
{
  // 转换为栅格坐标
  Vector2i gridmap = worldToMap(worldpt);
  // 判断是否被占据 或者说是不是障碍物
  int idx = gridmap[0];
  int idy = gridmap[1];

  return (idx < grid_map_x && idy < grid_map_y && (mapdata[idx + idy * grid_map_x] == OCCUPIED));
}

// 判断点是否被占据的具体实现形式
bool Fast_Security::isOccupied(const Vector2i gridpt) const
{
  // 判断是否被占据 或者说是不是障碍物
  int idx = gridpt[0];
  int idy = gridpt[1];

  return (idx < grid_map_x && idy < grid_map_y && (mapdata[idx + idy * grid_map_x] == OCCUPIED));
}

// 设定访问节点
void Fast_Security::setSTATE_VISITED(const Vector2i gridpt)
{
  // 判断是否被占据 或者说是不是障碍物
  int idx = gridpt[0];
  int idy = gridpt[1];    

  search_data[idx + idy * grid_map_x] += 1;
}

// 判断点是否重复
bool Fast_Security::isRepeated(const Vector2i gridpt) const
{
  // 判断是否被占据 或者说是不是障碍物
  int idx = gridpt[0];
  int idy = gridpt[1];

  if (search_data[idx + idy * grid_map_x] >= 2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// 获取访问的次数
int Fast_Security::getSTATE_VISITEDNum(const Vector2i gridpt) const
{
  // 判断是否被占据 或者说是不是障碍物
  int idx = gridpt[0];
  int idy = gridpt[1];

  return search_data[idx + idy * grid_map_x];
}

// 获取当前点的势场数值
int8_t Fast_Security::getESDFvalue(Vector2i gridpt)
{
  // 判断是否被占据 或者说是不是障碍物
  int idx = gridpt[0];
  int idy = gridpt[1];

  return (mapdata[idx + idy * grid_map_x]);
}

// 判断向量是否共线
bool Fast_Security::isCollinear(Vector2i vector1,Vector2i vector2,bool strict)
{
  if(strict == true)
  {
    if(vector1(0)*vector2(1) == vector1(1)*vector2(0))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    double angle = calVectorAngle(vector1,vector2);
    if(angle >= 0 && angle < PI/16)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

// 判断向量是否共线
bool Fast_Security::isCollinear(Vector2d vector1,Vector2d vector2,bool strict)
{
  if(strict == true)
  {
    if(vector1(0)*vector2(1) == vector1(1)*vector2(0))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    double angle = calVectorAngle(vector1,vector2);
    if(angle >= 0 && angle < PI/16)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

// 计算单位向量
Vector2d Fast_Security::calUnitvector(Vector2i unitv)
{
  double x = double(unitv[0]);
  double y = double(unitv[1]);
  Vector2d unitVector = Vector2d(x,y);
  unitVector = unitVector * 1.0f/(sqrt(pow(abs(x),2)+pow(abs(y),2)));
  return unitVector;
}

// 计算单位向量
Vector2d Fast_Security::calUnitvector(Vector2d unitv)
{
  unitv = unitv * 1.0f/(sqrt(pow(abs(unitv[0]),2)+pow(abs(unitv[1]),2)));
  return unitv;
}

// 计算两个点之间的长度欧氏距离
double Fast_Security::calPointLength(Vector2i vector1,Vector2i vector2)
{
  return (sqrt((vector1[0]-vector2[0])*(vector1[0]-vector2[0])+(vector1[1]-vector2[1])*(vector1[1]-vector2[1])));
}

// 计算两个点之间的长度欧氏距离
double Fast_Security::calPointLength(Vector2d vector1,Vector2d vector2)
{
  return (sqrt((vector1[0]-vector2[0])*(vector1[0]-vector2[0])+(vector1[1]-vector2[1])*(vector1[1]-vector2[1])));
}


// 计算向量之间的夹角
double Fast_Security::calVectorAngle(Vector2i vector1,Vector2i vector2)
{
  Vector2d vectorFirst = calUnitvector(vector1);
  Vector2d vectorSecond = calUnitvector(vector2);

  double vector_angle = vectorFirst[0]*vectorSecond[0] + vectorFirst[1]*vectorSecond[1];
  return acos(vector_angle);
}

// 计算向量之间的夹角
double Fast_Security::calVectorAngle(Vector2d vector1,Vector2d vector2)
{
  Vector2d vectorFirst = calUnitvector(vector1);
  Vector2d vectorSecond = calUnitvector(vector2);

  double vector_angle = vectorFirst[0]*vectorSecond[0] + vectorFirst[1]*vectorSecond[1];
  return acos(vector_angle);
}

// 计算向量之间的乘积
double Fast_Security::calVectorProduct(Vector2i vector1,Vector2i vector2)
{
  Vector2d vectorFirst = calUnitvector(vector1);
  Vector2d vectorSecond = calUnitvector(vector2);

  double vector_product = vectorFirst[0]*vectorSecond[0] + vectorFirst[1]*vectorSecond[1];

  return vector_product;
}

// 将世界坐标点转换成栅格坐标系下的整数点
vector<Vector2i> Fast_Security::worldPathToGridPath(vector<Vector2d> worldPath)
{
  int worldLength = worldPath.size();
  vector<Vector2i> GridPath;
  for(int i=0;i<worldLength;i++)
  {
    Vector2i gridNode = worldToMap(worldPath[i]);
    GridPath.push_back(gridNode);
  }
  
  return GridPath;
}

// 将栅格坐标系下的整数点转换成世界坐标系下的点
vector<Vector2d> Fast_Security::GridPathToWorldPath(vector<Vector2i> gridPath)
{
  int worldLength = gridPath.size();
  vector<Vector2d> worldPath;
  for(int i=0;i<worldLength;i++)
  {
    Vector2d worldNode = mapToWorld(gridPath[i]);
    worldPath.push_back(worldNode);
  }
  
  return worldPath;  
}

// 搜索障碍物
void Fast_Security::Search_Obstacle(double searchLength,Vector2i point,Vector2i vertical_m,int &add_num,int &min_num)
{
  int add_temp = search_num/2;
  int min_temp = search_num/2;
  
  for(int j=1;j<searchLength/2+1;j++)
  {
    Vector2i pointS;
    pointS = point + j*vertical_m;
    if(isOccupied(pointS))
    {
      add_temp = j;
      break;
    }
  }

  for (int j=1;j<searchLength/2+1;j++)
  {
    Vector2i pointS;
    pointS = point - j*vertical_m;
    if(isOccupied(pointS))
    {
      min_temp = j;
      break;
    }
  }

  add_num = add_temp;
  min_num = min_temp;
}

// 节点扩展
void Fast_Security::Node_Extension(int addsearch,int minsearch,Vector2i point,Vector2i vertical_m,vector<Vector2i> &pointExtension)
{
  setSTATE_VISITED(point);
  pointExtension.push_back(point);
  
  for(int j=1;j<addsearch+1;j++)
  {
    Vector2i pointS;
    pointS = point + j*vertical_m;
    if(isOccupied(pointS))
    {
      break;
    }
    else
    {
      setSTATE_VISITED(pointS);
      pointExtension.push_back(pointS);
    }
  }

  for (int j=1;j<minsearch+1;j++)
  {
    Vector2i pointS;
    pointS = point - j*vertical_m;
    if(isOccupied(pointS))
    {
      break;
    }
    else
    {
      setSTATE_VISITED(pointS);
      pointExtension.push_back(pointS);
    }
  }
}

// 中断节点扩展
void Fast_Security::Inflect_Extension(int test,vector<Vector2i> &front1Extension,vector<Vector2i> &front2Extension,
vector<Vector2i> &after1Extension,vector<Vector2i> &after2Extension)
{
  front1Extension.clear();
  front2Extension.clear();
  after1Extension.clear();
  after2Extension.clear();

  if(max_step_vec[test] < search_num/4)
  {
    max_step_vec[test] = search_num/4;
  }
  if(max_step_vec[test+1] < search_num/4)
  {
    max_step_vec[test+1] = search_num/4;
  }
  
  for(int step = 0;step<max_step_vec[test]+search_num/8;step++)
  {
    Vector2i tempoint = frontVec[test] + step*frontToafterVec[test];
    
    if(!isOccupied(tempoint))
    {
      Node_Extension(inflect_add_search[4*test],inflect_min_search[4*test],tempoint,verfrontToafterVec[test],front1Extension);
    }
    else
    {
      break;
    }
  }

  for(int step = 0;step<max_step_vec[test]+search_num/8;step++)
  {
    Vector2i tempoint = frontVec[test] - step*frontToafterVec[test];
    
    if(!isOccupied(tempoint))
    {
      Node_Extension(inflect_add_search[4*test+1],inflect_min_search[4*test+1],
      tempoint,verfrontToafterVec[test],front2Extension);
    }
    else
    {
      break;
    }
  }

  for(int step = 0;step<max_step_vec[test]+search_num/8;step++)
  {
    Vector2i tempoint = afterVec[test] + step*afterTofrontVec[test];

    if(!isOccupied(tempoint))
    {
      Node_Extension(inflect_add_search[4*test+2],inflect_min_search[4*test+2],
      tempoint,verfrontToafterVec[test],after1Extension);
    }
    else
    {
      break;
    }
  }

  for(int step = 0;step<max_step_vec[test]+search_num/8;step++)
  {
    Vector2i tempoint = afterVec[test] - step*afterTofrontVec[test];

    if(!isOccupied(tempoint))
    {
      Node_Extension(inflect_add_search[4*test+3],inflect_min_search[4*test+3],
      tempoint,verfrontToafterVec[test],after2Extension);
    }
    else
    {
      break;
    }
  }
}

void Fast_Security::Rectangle_Extension(int addsearch,int minsearch,Vector2i point,vector<Vector2i> &pointExtension)
{
  pointExtension.clear();
  Vector2i horizen = Vector2i(1,0);
  Vector2i vertical = Vector2i(0,1);
  
  for (int step = 0; step < addsearch; step++)
  {
    Vector2i tempoint = point + step * horizen;
    if(!isOccupied(tempoint))
    {
      Node_Extension(addsearch,minsearch,tempoint,vertical,pointExtension);
    }
    else
    {
      break;
    }
  }

  for (int step = 1; step < minsearch; step++)
  {
    Vector2i tempoint = point - step * horizen;
    if(!isOccupied(tempoint))
    {
      Node_Extension(addsearch,minsearch,tempoint,vertical,pointExtension);
    }
    else
    {
      break;
    }
  }  
}

// 连续扩展部分提取
void Fast_Security::ContinuExtension_Extract(vector<vector<Vector2i>> &continu_sample)
{
  continu_sample.clear();
  int start = 0;
  if(continuNum.size() >= 1)
  {
    for(int i=start;i<continuNum.size();i++)
    {
      int num = start + continuNum[i];
      continu_sample.push_back(continuPoints[start+continuNum[i]/8]);
      continu_sample.push_back(continuPoints[start+continuNum[i]/4]);
      continu_sample.push_back(continuPoints[num-continuNum[i]/4]);
      continu_sample.push_back(continuPoints[num-continuNum[i]/8]);
      start+=continuNum[i];
    }
  }
  else
  {
    return;
  }
}

// 连续点扩展
void Fast_Security::Continu_Extension(vector<vector<Vector2i>> &pointsMap,vector<vector<Vector2d>> &pointsWorld)
{
  pointsMap.clear();
  pointsWorld.clear();

  continuNum.clear();

  if(continuDivid.size()>0)
  {
    int num = 0;
    for (int i = 0; i < continuDivid.size()-1; i++)
    {
      if(continuDivid[i].first == continuDivid[i+1].first)
      {
        num++;
      }
      else
      {
        continuNum.push_back(num);
        num = 0;      
      }
    }

    int thelastNum = 0;
    for (int i = 0; i < continuDivid.size(); i++)
    {
      if(continuDivid[i].first == flagOK[flagOK.size()-1])
      {
        thelastNum++;
      }
    }
    continuNum.push_back(thelastNum);

    int lastNum = continuNum[continuNum.size()-1];
    int allNum = 0;
    for (int i = 0; i < continuNum.size()-1; i++)
    {
      allNum += continuNum[i];
    }

    int last_add_num = 0;
    int last_min_num = 0;
    int last_add_search = search_num/2;
    int last_min_search = search_num/2;
    for (int i = 0; i < lastNum; i++)
    {
      Search_Obstacle(search_num,continuDivid[allNum+i].second,
      vercontinuDivid[allNum+i].second,last_add_num,last_min_num);
      if(last_add_num < last_add_search)
      {
        last_add_search = last_add_num;
      }
      if(last_min_num < last_min_search)
      {
        last_min_search = last_min_num;
      }
    }

    if(continuNum.size()>1)
    {
      int time = 0;
      for(int i=0;i<continuDivid.size()-1;i++)
      {
        int add_search = continu_add_search[time];
        int min_search = continu_min_search[time];
        
        if(add_search < 6 && min_search < 6)
        {
          add_search = 6;
          min_search = 6;
        }

        vector<Vector2i> pointExtension;

        if(i<allNum)
        {
          if(continuDivid[i].first == continuDivid[i+1].first)
          {
            Node_Extension(add_search,min_search,continuDivid[i].second,vercontinuDivid[i].second,pointExtension);
            pointsMap.push_back(pointExtension);
            pointsWorld.push_back(GridPathToWorldPath(pointExtension));

            vector<Vector2d> tempworld = GridPathToWorldPath(pointExtension);
          }
          else
          {
            time++;
            if(time >= continu_add_search.size())
            {
              time = continu_add_search.size()-1;
            }
          }
        }
        else
        {
          Node_Extension(last_add_search,last_min_search,continuDivid[i].second,vercontinuDivid[i].second,pointExtension);
          pointsMap.push_back(pointExtension);
          pointsWorld.push_back(GridPathToWorldPath(pointExtension));

          vector<Vector2d> tempworld = GridPathToWorldPath(pointExtension);   
        }
      }
    }
  }
}

// 中断区域扩展
void Fast_Security::Interrupt_Extension(vector<vector<Vector2i>> &pointsMap,vector<vector<Vector2d>> &pointsWorld)
{
  pointsMap.clear();
  pointsWorld.clear();

  frontVec.clear();
  afterVec.clear();

  frontToafterVec.clear();
  afterTofrontVec.clear();
  verfrontToafterVec.clear();
  max_step_vec.clear();

  inflect_add_search.clear();
  inflect_min_search.clear();

  if(dividNodes.size() > 0)
  {
    for(int i=1;i<=dividNodes.size()-1;i++)
    {
      int max_step;
      if(i%2 == 1)
      {
        Vector2i front = dividNodes[i-1];
        Vector2i after = dividNodes[i];

        int distance_x = abs(front[0] - after[0]);
        int distance_y = abs(front[1] - after[1]);
        max_step = max(distance_x,distance_y);
        
        max_step_vec.push_back(max_step);
      }
      
      if(i%2 == 1 && i<=dividNodes.size()-2)
      {
        Vector2i front = dividNodes[i];
        Vector2i after = dividNodes[i+1];

        frontVec.push_back(front);
        afterVec.push_back(after);

        Vector2i frontToafter = front - after;
        int distance_x = frontToafter[0];
        int distance_y = frontToafter[1];
        if(distance_x != 0 && distance_y != 0)
        {
          frontToafter[0] = distance_x / abs(distance_x);
          frontToafter[1] = distance_y / abs(distance_y);
        }
        if(distance_x == 0 && distance_y != 0)
        {
          frontToafter[0] = 0;
          frontToafter[1] = distance_y / abs(distance_y);
        }
        if(distance_x != 0 && distance_y == 0)
        {
          frontToafter[0] = distance_x / abs(distance_x);
          frontToafter[1] = 0;
        }

        Vector2i afterTofront = -frontToafter;
        Vector2i verfrontToafter = Vector2i(frontToafter[1],-frontToafter[0]);
        
        frontToafterVec.push_back(frontToafter);
        afterTofrontVec.push_back(afterTofront);
        verfrontToafterVec.push_back(verfrontToafter);
      }
    }

    for (int i = 0; i < frontToafterVec.size(); i++)
    {
      FindInflectLimitExten(i);
    }
    
    if(frontToafterVec.size()>0)
    {
      for (int i = 0; i < frontToafterVec.size(); i++)
      {
        vector<Vector2i> front1Extension,after1Extension;
        vector<Vector2i> front2Extension,after2Extension;

        Inflect_Extension(i,front1Extension,front2Extension,after1Extension,after2Extension);
        pointsMap.push_back(front1Extension);
        pointsMap.push_back(front2Extension);
        pointsMap.push_back(after1Extension);
        pointsMap.push_back(after2Extension);
        
        vector<Vector2d> worldPoints1 = GridPathToWorldPath(front1Extension);
        vector<Vector2d> worldPoints2 = GridPathToWorldPath(front2Extension); 
        vector<Vector2d> worldPoints3 = GridPathToWorldPath(after1Extension);  
        vector<Vector2d> worldPoints4 = GridPathToWorldPath(after2Extension); 
        
        pointsWorld.push_back(worldPoints1);
        pointsWorld.push_back(worldPoints2);
        pointsWorld.push_back(worldPoints3);
        pointsWorld.push_back(worldPoints4);
      }
    }
  }
  else
  {
    pointsMap.clear();
    pointsWorld.clear();    
    return;
  }
}

// 设定地图参数
void Fast_Security::SetMapParams(double resolution_,double origin_x_,double origin_y_,
                    int map_x_size,int map_y_size,std::vector<int8_t> _mapData)
{
  resolution = resolution_;
  resolution_inv = 1.0/resolution;

  origin_x = origin_x_;
  origin_y = origin_y_;

  grid_map_x = map_x_size;
  grid_map_y = map_y_size;

  mapover_x = grid_map_x*resolution;
  mapover_y = grid_map_y*resolution;

  search_num = search_length * resolution_inv;

	mapdata = new int8_t[grid_map_x * grid_map_y];
	memset(mapdata, 0, grid_map_x * grid_map_y * sizeof(int8_t));

  for(int x=0;x<grid_map_x;x++){
    for(int y=0;y<grid_map_y;y++)
    {
      mapdata[x+y*grid_map_x] = _mapData[x+y*grid_map_x];
    }
  }

  search_data.resize(grid_map_x*grid_map_y);
  search_data.assign(grid_map_x*grid_map_y,0);
  
  bezier_opt.reset(new BEZIER);
  bezier_opt->setParams(3.0,0.2,4);
}

// 路径点采样
void Fast_Security::SampleGridPath(vector<Vector2i> gridpath)
{
  int path_node_num = gridpath.size();

  int inflectnum = 0;
  int continunum = 0;

  int dividNum = 1;

  inflectAssem.clear();

  for(int i=1;i<path_node_num-1;i++)
  {
    pointa = gridpath[i-1];
    pointb = gridpath[i];

    v_b_a = pointb - pointa; 
    ver_b_a = Vector2i(v_b_a[1],-v_b_a[0]);

    nowvec = ver_b_a;

    if(!isCollinear(nowvec,lastvec,true))
    {
      inflectnum = i;
      inflectAssem.push_back(pointb);
    }
    else
    {
      if(i-continunum == 1)
      {
        continuAssem.push_back(pointb);
        vercontAssem.push_back(ver_b_a);

        continuDivid.push_back(make_pair(dividNum,pointb));
        vercontinuDivid.push_back(make_pair(dividNum,ver_b_a));
      }
      else
      {
        dividNum ++;
      }
      continunum = i;
    }
    lastvec = nowvec;
  }

  vector<pair<int,Vector2i>> tempcontinDiv = continuDivid;
  vector<pair<int,Vector2i>> vertempcontinDiv = vercontinuDivid;
  continuDivid.clear();
  vercontinuDivid.clear();

  flagOK.clear();
  bool hasAdd = false;
  int time = 0;
  int continuDivNum = search_num/4;
  if(continuDivNum > 5)
  {
    continuDivNum = 5;
  }
  for (int i = 0; i < tempcontinDiv.size()-1; i++)
  {
    if(tempcontinDiv[i].first == tempcontinDiv[i+1].first)
    {
      time++;
      if(time >= continuDivNum && hasAdd == false)
      {
        hasAdd = true;
        flagOK.push_back(tempcontinDiv[i].first);
      }
    }
    else
    {
      time = 0;
      hasAdd = false;
    }
  }
  
  for (int num = 0; num < flagOK.size(); num++)
  {
    for (int i = 0; i < tempcontinDiv.size(); i++)
    {
      if(tempcontinDiv[i].first == flagOK[num])
      {
        continuDivid.push_back(tempcontinDiv[i]);
        vercontinuDivid.push_back(vertempcontinDiv[i]);
      }
    }
  }
}

// 搜索扩展限制点
void Fast_Security::FindContinueLimitExten(vector<int> &add_search_vec,vector<int> &min_search_vec)
{
  add_search_vec.clear();
  min_search_vec.clear();

  int search_add_num = 0;
  int search_min_num = 0;
  int add_search;
  int min_search;

  if(continuDivid.size()>0)
  {
    for(int i=0;i<continuDivid.size()-1;i++)
    {
      if(continuDivid[i].first == continuDivid[i+1].first)
      {
        Search_Obstacle(search_num,continuDivid[i].second,vercontinuDivid[i].second,search_add_num,search_min_num);
        if(search_add_num < add_search)
        {
          add_search = search_add_num;
        }
        if(search_min_num < min_search)
        {
          min_search = search_min_num;
        }
      }
      else
      {
        add_search_vec.push_back(add_search);
        min_search_vec.push_back(min_search);

        add_search = search_num/2;
        min_search = search_num/2;

        search_add_num = 0;
        search_min_num = 0;
      }
    }
  }
  else
  {
    add_search_vec.clear();
    min_search_vec.clear();    
  }
}

// 搜索扩展限制点
void Fast_Security::FindInflectLimitExten(int test)
{
  int search_add_num = 0;
  int search_min_num = 0;
  int add_search = search_num/2;
  int min_search = search_num/2;

  for(int step = 0;step<search_num/2;step++)
  {
    Vector2i tempoint = frontVec[test] + step*frontToafterVec[test];
    Search_Obstacle(search_num,tempoint,verfrontToafterVec[test],search_add_num,search_min_num);
    if(search_add_num < add_search)
    {
      add_search = search_add_num;
    }
    if(search_min_num < min_search)
    {
      min_search = search_min_num;
    }
  }

  inflect_add_search.push_back(add_search);
  inflect_min_search.push_back(min_search);

  add_search = search_num/2;
  min_search = search_num/2;
  search_add_num = 0;
  search_min_num = 0;

  for(int step = 0;step<search_num/2;step++)
  {
    Vector2i tempoint = frontVec[test] - step*frontToafterVec[test];
    Search_Obstacle(search_num,tempoint,verfrontToafterVec[test],search_add_num,search_min_num);
    if(search_add_num < add_search)
    {
      add_search = search_add_num;
    }
    if(search_min_num < min_search)
    {
      min_search = search_min_num;
    }
  }

  inflect_add_search.push_back(add_search);
  inflect_min_search.push_back(min_search);

  add_search = search_num/2;
  min_search = search_num/2;
  search_add_num = 0;
  search_min_num = 0;

  for(int step = 0;step<search_num/2;step++)
  {
    Vector2i tempoint = afterVec[test] + step*afterTofrontVec[test];
    Search_Obstacle(search_num,tempoint,verfrontToafterVec[test],search_add_num,search_min_num);
    if(search_add_num < add_search)
    {
      add_search = search_add_num;
    }
    if(search_min_num < min_search)
    {
      min_search = search_min_num;
    }
  }

  inflect_add_search.push_back(add_search);
  inflect_min_search.push_back(min_search);

  add_search = search_num/2;
  min_search = search_num/2;
  search_add_num = 0;
  search_min_num = 0;

  for(int step = 0;step<search_num/2;step++)
  {
    Vector2i tempoint = afterVec[test] - step*afterTofrontVec[test];
    Search_Obstacle(search_num,tempoint,verfrontToafterVec[test],search_add_num,search_min_num);
    if(search_add_num < add_search)
    {
      add_search = search_add_num;
    }
    if(search_min_num < min_search)
    {
      min_search = search_min_num;
    }
  }

  inflect_add_search.push_back(add_search);
  inflect_min_search.push_back(min_search);

  add_search = search_num/2;
  min_search = search_num/2;
  search_add_num = 0;
  search_min_num = 0;  

  for (int i = 0; i < inflect_add_search.size(); i++)
  {
    if(inflect_add_search[i] < search_num/4 && inflect_min_search[i] < search_num/4)
    {
      inflect_add_search[i] = search_num/4;
      inflect_min_search[i] = search_num/4;
    }
  }
}

// 计算分段点
void Fast_Security::CalDivideNodes(vector<Vector2i> &dividMap,vector<Vector2d> &dividWorld)
{
  dividMap.clear();
  dividWorld.clear();

  if(continuDivid.size()>0)
  {
    vector<Vector2i> frontpoints;
    for(int i = 0;i<continuDivid.size()-1;i++)
    {
      if(continuDivid[i].first != continuDivid[i+1].first)
      {
        frontpoints.push_back(continuDivid[i].second);
      }
    }
    vector<Vector2i> afterpoints;
    for(int i = 1;i<continuDivid.size();i++)
    {
      if(continuDivid[i].first != continuDivid[i-1].first)
      {
        afterpoints.push_back(continuDivid[i].second);
      }
    }

    for (int i = 0; i < afterpoints.size(); i++)
    {
      dividMap.push_back(frontpoints[i]);
      dividMap.push_back(afterpoints[i]);

      dividWorld.push_back(mapToWorld(frontpoints[i]));
      dividWorld.push_back(mapToWorld(afterpoints[i]));
    }
  }
  else
  {
    dividMap.clear();
    dividWorld.clear();    
  }
}

vector<Vector2d> Fast_Security::Fast_Security_Search(vector<Vector2d> oripath)
{
  completed_flag = 0;
  resetSTATE_VISITED();

  search_data.assign(grid_map_x*grid_map_y,0);
  
  int path_node_num = oripath.size();
  vector<Vector2i> gridpath = worldPathToGridPath(oripath);
  origingridPath = gridpath;

  if(path_node_num < 3)
  {
    return oripath;
  }
  else{
    grid_map_start = gridpath[0];
    grid_map_end = gridpath[path_node_num-1];

    SampleGridPath(gridpath);
    CalDivideNodes(dividNodes,worldividNodes);
    FindContinueLimitExten(continu_add_search,continu_min_search);
    Continu_Extension(continuPoints,continuPointsWorld);
    ContinuExtension_Extract(continuSample);
    Interrupt_Extension(inflectPoins,inflectPoinsWorld);

    optedpath = PathOptimization(continuSample,inflectPoins);
  }

  return optedpath;
}

void Fast_Security::visualNodes(void)
{
  visual_SamplesNode(continuNodesPub,continuPointsWorld,0.5,1,0,0,1);
  visual_SamplesNode(visitNodesPub,inflectPoinsWorld,0.5,1,0,0,1);
  visual_SamplesNode(sampleNodesPub,connectPointsWorld,0.5,1,0,0,1);
  visual_STATE_VISITEDNode(visitOptpathPub,optedpath,0.5,1,0,0,1);
}

// 查询间断点的数目
void Fast_Security::CheckInflectNum(vector<Vector2i> gridPath,Vector2i firstpoint,Vector2i secondpoint,int &firstnum,int &secondnum)
{
  for (int length = 0; length < gridPath.size(); length++)
  {
    if(gridPath[length] == firstpoint)
    {
      firstnum = length;
    }
    if(gridPath[length] == secondpoint)
    {
      secondnum = length;
    }
  }
}

// 输出路径点前后共线段的坐标位置集合
vector<int> Fast_Security::CollinearPosition(vector<Vector2i> gridPath)
{
  vector<int> collinear_Num; 
  for (int i = 1; i < gridPath.size()-1; i++)
  {
    Vector2i lastpoint = gridPath[i-1];
    Vector2i nowpoint = gridPath[i];
    Vector2i nextpoint = gridPath[i+1];

    Vector2i last_now = nowpoint-lastpoint;
    Vector2i now_next = nextpoint - nowpoint;

    if(isCollinear(last_now,now_next,true))
    {
      collinear_Num.push_back(i);
    }
  }

  return collinear_Num;
}

// 对路径进行分段
void Fast_Security::DividPath(vector<Vector2i> gridPath,vector<int> dividvec,vector<vector<Vector2d>> &dividpath)
{
  dividpath.clear();  

  for (int i = 0; i < dividvec.size(); i++)
  {
    if(i<dividvec.size()-1)
    {
      int start = dividvec[i];
      int end = dividvec[i+1]+1;
      if(i == dividvec.size()-2)
      {
        end = dividvec[i+1];
      }
      if(i == 0)
      {
        vector<Vector2i> tempath;
        for (int j = 0; j < start; j++)
        {
          tempath.push_back(gridPath[j]);
        }
        dividpath.push_back(GridPathToWorldPath(tempath));
      }
      if(i > 0)
      {
        vector<Vector2i> tempath;
        for (int j = start; j < end; j++)
        {
          tempath.push_back(gridPath[j]);
        }
        dividpath.push_back(GridPathToWorldPath(tempath));
      }
    }
    if(i==dividvec.size()-1)
    {
      vector<Vector2i> tempath;
      for (int j = dividvec[i]; j < gridPath.size(); j++)
      {
        tempath.push_back(gridPath[j]);
      }
      dividpath.push_back(GridPathToWorldPath(tempath));
    }
  }
}

// 使用贝塞尔曲线对路径进行优化
vector<Vector2d> Fast_Security::BezierPathOpt(vector<vector<Vector2d>> needoptpath)
{
  vector<Vector2d> worldpath;
  vector<vector<pair<int,Vector2d>>> waitopt;

  for (int i = 0; i < needoptpath.size(); i++)
  {
    vector<pair<int,Vector2d>> sub;
    for (int j = 0; j < needoptpath[i].size(); j++)
    {
      sub.push_back(make_pair(0,needoptpath[i][j]));
    }
    waitopt.push_back(sub);    
  }

  for (int i = 0; i < needoptpath.size(); i++)
  {
    vector<Vector2d> dividopt = needoptpath[i];
    int dividlength = dividopt.size();
    if(dividlength <= 4)
    {
      vector<Vector2d> newoptpath = bezier_opt->BezierPath(dividopt);
      for (int num = 0; num < newoptpath.size(); num++)
      {
        worldpath.push_back(newoptpath[num]);
      }
    }
    if(dividlength > 4)
    {      
      for (int num = 0; num < dividlength/4; num++)
      {
        vector<Vector2d> tempath;
        tempath.push_back(dividopt[num*4]);
        tempath.push_back(dividopt[num*4+1]);
        tempath.push_back((dividopt[num*4+2]));
        tempath.push_back(dividopt[num*4+3]);
        vector<Vector2d> newoptpath = bezier_opt->BezierPath(tempath);        
        
        for (int length = 0; length < newoptpath.size(); length++)
        {
          worldpath.push_back(newoptpath[length]);
        }        
      }
      int lastlength = dividlength%4;
      if(lastlength > 0)
      {
        vector<Vector2d> tempath;
        for (int num = 0; num < lastlength; num++)
        {
          tempath.push_back(dividopt[4*(dividlength/4)+num]);
        }

        vector<Vector2d> newoptpath = bezier_opt->BezierPath(tempath);
        for (int length = 0; length < newoptpath.size(); length++)
        {
          worldpath.push_back(newoptpath[length]);
        }         
      }
    }
  }

  vector<Vector2i> tempath = worldPathToGridPath(worldpath);
  vector<Vector2i> interpo_path;
  Setlength_Interpolation_Path(0.2,tempath,interpo_path);
  vector<Vector2d> lastpath = GridPathToWorldPath(interpo_path);
  
  vector<Vector2d> optedpath;
  Vector2d lastpoint;
  for (int i = 0; i < lastpath.size(); i++)
  {
    if(i == 0)
    {
      optedpath.push_back(lastpath[0]);
      lastpoint = lastpath[0];
    }
    if(i>0)
    {
      double distance = calPointLength(lastpath[i],lastpoint);
      if(distance >= 0.2)
      {
        optedpath.push_back(lastpath[i]);
        lastpoint = lastpath[i];
      }
    }
    if(i == lastpath.size()-1)
    {
      optedpath.push_back(lastpath[i]);      
    }
  }
  
  return optedpath;
}

// 获取优化后的路径的欧几里得距离场信息数据
void Fast_Security::GetPathESDFvalue(int &sum_esdf,double &ave_esdf,int &path_num)
{
  sum_esdf = 0;
  ave_esdf = 0;
  path_num = 0;
  int optedpath_num = optedpath.size();

  if(optedpath_num > 0)
  {
    Vector2d nowpoint = optedpath[0];
    for (int i = 0; i < optedpath_num; i++)
    {
      if(calPointLength(nowpoint,optedpath[i]) >= resolution)
      {
        path_num ++;
        sum_esdf += getESDFvalue(worldToMap(optedpath[i]));
        nowpoint = optedpath[i];
      }
    }
    
    ave_esdf = sum_esdf/(1.0f*path_num);
  }
  else
  {
    return;
  }
}

// 检查点之间有没有障碍物
bool Fast_Security::CheckObstaclePoints(Vector2i firstpoint,Vector2i secondpoint)
{
  bool has_obstacle = false;
  double length = calPointLength(firstpoint,secondpoint);
  Vector2i direct = secondpoint-firstpoint;
  Vector2d direct_unit = calUnitvector(direct);
  for (int step = 0; step < length; step++)
  {
    Vector2d searchpoint = mapToWorld(firstpoint) + step*direct_unit*resolution;
    if(isOccupied(searchpoint))
    {
      has_obstacle = true;
      break;
    }
  }

  return has_obstacle;
}

// 对路径按照固定间距分段
void Fast_Security::Setlength_DividPath(double step,vector<Vector2i> oldpath,vector<Vector2i> &newpath)
{
  Vector2i lastpoint;
  for (int i = 0; i < oldpath.size(); i++)
  {
    if(i == 0)
    {
      newpath.push_back(oldpath[0]);
      lastpoint = oldpath[0];
    }
    if(i>0)
    {
      double distance = calPointLength(mapToWorld(oldpath[i]),mapToWorld(lastpoint));
      if(distance >= 0.2)
      {
        newpath.push_back(oldpath[i]);
        lastpoint = oldpath[i];
      }
    }
    if(i == oldpath.size()-1)
    {
      newpath.push_back(oldpath[i]);      
    }
  }
}

// 对路径进行插值
void Fast_Security::Setlength_Interpolation_Path(double length,vector<Vector2i> oldpath,vector<Vector2i> &newpath)
{
  double steplength = length;
  double interpolation_length = resolution;

  newpath.clear();
  for (int i = 0; i < oldpath.size()-1; i++)
  {
    Vector2i nowpoint = oldpath[i];
    Vector2i nextpoint = oldpath[i+1];
    double distance = calPointLength(nowpoint,nextpoint)*resolution;

    if(distance > steplength)
    {
      Vector2i now_next = nextpoint-nowpoint;
      Vector2d unit_now_next = calUnitvector(now_next);

      newpath.push_back(oldpath[i]);
      int step_num = distance/interpolation_length; 
      for (int j = 1; j < step_num; j++)
      {
        Vector2d startpoint = mapToWorld(nowpoint);
        Vector2d interpolationpoint = startpoint+j*unit_now_next*resolution;
        newpath.push_back(worldToMap(interpolationpoint));
      }
    }
    else
    {
      newpath.push_back(oldpath[i]);
    }
  }
}

// 对路径进行优化
vector<Vector2d> Fast_Security::PathOptimization(vector<vector<Vector2i>> continu,vector<vector<Vector2i>> inflect)
{
  vector<Vector2d> worldpath;
  vector<Vector2i> optpath;
  vector<pair<int,Vector2i>> samplePoints;

  vector<pair<Vector2i,Vector2i>> sampleSortPoints;

  optimiPoints.clear();
  optimiPointsWorld.clear();
  connectPointsWorld.clear();

  for (int i = 0; i < continu.size(); i++)
  {
    if(continu[i].size() > 0)
    {
      if(continu[i].size() > 0)
      {
        optimiPoints.push_back(make_pair(1,continu[i]));
        optimiPointsWorld.push_back(GridPathToWorldPath(continu[i]));
      }
    }

    if(i%4 == 0 && i/2+1 < dividNodes.size())
    {
      if(i < continu.size()-1)
      {
        Vector2i first = dividNodes[i/2];
        Vector2i second = dividNodes[i/2+1];
        int firstNum = 0;
        int secondNum = 0;
        CheckInflectNum(origingridPath,first,second,firstNum,secondNum);
        if(secondNum - firstNum > 3)
        {
          Vector2i first_second = origingridPath[secondNum] - origingridPath[firstNum];
          Vector2i ver_first_second;

          if(first_second[0] == 0 && first_second[1] > 0)
          {
            ver_first_second = Vector2i(1,0);
          }
          if(first_second[0] > 0 && first_second[1] == 0)
          {
            ver_first_second = Vector2i(0,1);
          }
          if(first_second[0] * first_second[1] > 0)
          {
            ver_first_second = Vector2i(1,-1);
          }
          if(first_second[0] * first_second[1] < 0)
          {
            ver_first_second = Vector2i(1,1);
          }
          for (int start = firstNum; start < secondNum; start++)
          {
            vector<Vector2i> pointExtension;
            if(getSTATE_VISITEDNum(origingridPath[start]) == 0)
            {
              Node_Extension(search_num/2,search_num/2,origingridPath[start],ver_first_second,pointExtension);
              optimiPoints.push_back(make_pair(3,pointExtension));       

              optimiPointsWorld.push_back(GridPathToWorldPath(pointExtension));
              connectPointsWorld.push_back(GridPathToWorldPath(pointExtension));
            }
          }
        }
      }
    }

    if(i%4 == 1 && (i-1)*4+3 < inflect.size())
    {
      if(inflect[(i-1)*4].size() > 0)
      {
        optimiPoints.push_back(make_pair(2,inflect[(i-1)*4]));
        optimiPointsWorld.push_back(GridPathToWorldPath(inflect[(i-1)*4]));
      }
      if(inflect[(i-1)*4+1].size() > 0)
      {
        optimiPoints.push_back(make_pair(2,inflect[(i-1)*4+1]));
        optimiPointsWorld.push_back(GridPathToWorldPath(inflect[(i-1)*4+1]));
      }
      if(inflect[(i-1)*4+2].size() > 0)
      {
        optimiPoints.push_back(make_pair(2,inflect[(i-1)*4+2]));
        optimiPointsWorld.push_back(GridPathToWorldPath(inflect[(i-1)*4+2]));
      }
      if(inflect[(i-1)*4+3].size() > 0)
      {
        optimiPoints.push_back(make_pair(2,inflect[(i-1)*4+3]));
        optimiPointsWorld.push_back(GridPathToWorldPath(inflect[(i-1)*4+3]));
      }
    }
  }

  double max_distance = calPointLength(grid_map_start,grid_map_end);
  Vector2i last;
  for (int i = 0; i < optimiPoints.size(); i++)
  {
    pair<int,vector<Vector2i>> tempoints = optimiPoints[i];
    if(tempoints.first == 1)
    {
      double nowvisit;
      double min_cost = 10000;
      double cost;
      int8_t now_esdf;

      Vector2i nowpoint;
      Vector2i tempoint;
      double last_distance = calPointLength(last,tempoints.second[0]);
      double end_distance = calPointLength(grid_map_end,tempoints.second[0]);
      double refer_esdf = getESDFvalue(tempoints.second[0]);
      double dangerous = refer_esdf/100.0f;
      for(size_t t=0;t<tempoints.second.size();t++)
      {
        nowpoint = tempoints.second[t];
        nowvisit = getSTATE_VISITEDNum(nowpoint);
        now_esdf = getESDFvalue(nowpoint);
        double distance = calPointLength(nowpoint,last);
        double dis_end = calPointLength(nowpoint,grid_map_end);
        double esdf_edis = dis_end/max_distance;
        esdf_edis = LIMIT_VALUE(esdf_edis,0.5,1.0);
        cost = (esdf_edis)*Kcontinu_esdf*now_esdf/(refer_esdf+1.0) + (1-dangerous)*Kcontinu_ldis*distance/(last_distance+1.0) 
        + (1-dangerous)*Kcontinu_edis*dis_end/(end_distance+1.0);
        if(cost < min_cost)
        {
          min_cost = cost;
          tempoint = nowpoint;
        }
      }
      last = tempoint;
      sampleSortPoints.push_back(make_pair(tempoints.second[0],tempoint));
    }
    if(tempoints.first == 2)
    {
      double nowvisit;
      double min_cost = 10000;
      double cost;
      int8_t now_esdf;

      Vector2i nowpoint;
      Vector2i tempoint;
      double last_distance = calPointLength(last,tempoints.second[0]);
      double end_distance = calPointLength(grid_map_end,tempoints.second[0]);
      double refer_esdf = getESDFvalue(tempoints.second[0]);
      double dangerous = refer_esdf/100.0f;
      for(size_t t=0;t<tempoints.second.size();t++)
      {
        nowpoint = tempoints.second[t];
        nowvisit = getSTATE_VISITEDNum(nowpoint);
        now_esdf = getESDFvalue(nowpoint);
        double dis_end = calPointLength(nowpoint,grid_map_end);
        double distance = calPointLength(nowpoint,last);
        double esdf_edis = dis_end/max_distance;
        esdf_edis = LIMIT_VALUE(esdf_edis,0.5,1.0);
        cost = (esdf_edis)*esdf_edis*Kinterru_esdf*now_esdf/(refer_esdf+1.0) + (1-dangerous)*Kinterru_rep*1.0f/nowvisit + 
        Kinterru_ldis*distance/(last_distance+1.0) + (1-dangerous)*Kinterru_edis*dis_end/(end_distance+1.0);
        if(cost < min_cost && nowvisit > 1)
        {
          min_cost = cost;
          tempoint = nowpoint;
        }
      }
      last = tempoint;
      sampleSortPoints.push_back(make_pair(tempoints.second[0],tempoint));
    }
    if(tempoints.first == 3)
    {
      double nowvisit;
      double min_cost = 10000;
      double cost;
      int8_t now_esdf;

      Vector2i nowpoint;
      Vector2i tempoint;
      double last_distance = calPointLength(last,tempoints.second[0]);
      double end_distance = calPointLength(grid_map_end,tempoints.second[0]);
      double refer_esdf = getESDFvalue(tempoints.second[0]);
      double dangerous = refer_esdf/100.0f;
      for(size_t t=0;t<tempoints.second.size();t++)
      {
        nowpoint = tempoints.second[t];
        nowvisit = getSTATE_VISITEDNum(nowpoint);
        now_esdf = getESDFvalue(nowpoint);
        double distance = calPointLength(nowpoint,last);
        double dis_end = calPointLength(nowpoint,grid_map_end);
        double esdf_edis = dis_end/max_distance;
        esdf_edis = LIMIT_VALUE(esdf_edis,0.5,1.0);
        cost = (esdf_edis)*esdf_edis*Kstep_esdf*now_esdf/(refer_esdf+1.0) + (1-dangerous)*Kstep_ldis*distance/(last_distance+1.0)
        + (1-dangerous)*Kstep_edis*dis_end/(end_distance+1.0);
        if(cost < min_cost)
        {
          min_cost = cost;
          tempoint = nowpoint;
        }
      }
      last = tempoint;
      sampleSortPoints.push_back(make_pair(tempoints.second[0],tempoint));
    }
  }

  sampleSortPoints.insert(sampleSortPoints.begin(),make_pair(grid_map_start,grid_map_start));
  sampleSortPoints.push_back(make_pair(grid_map_end,grid_map_end));

  vector<pair<int,Vector2i>> testpoints;
  for (size_t i = 0; i < sampleSortPoints.size(); i++)
  {
    for (size_t j = 0; j < origingridPath.size(); j++)
    {
      if(origingridPath[j] == sampleSortPoints[i].first)
      {
        testpoints.push_back(make_pair(j,sampleSortPoints[i].second));
      }
    }
  }
  
  for (size_t i = 0; i < testpoints.size(); i++)
  {
    for (size_t j = 0; j < testpoints.size(); j++)
    {
      if(testpoints[j].first == (int)i)
      {
        samplePoints.push_back(make_pair(0,testpoints[j].second));
        visualOptpoints.push_back(mapToWorld(testpoints[j].second));
      } 
    }
  }

  optpath.push_back(grid_map_start);

  pair<int,Vector2i> nowpoint;
  pair<int,Vector2i> lastpoint;
  for (size_t i = 0; i < samplePoints.size()-1; i++)
  {
    double distance;
    double dis_end1;
    double dis_end2;
    int flag = 0;
    double min_distance = 100000000;
    if( i == 0)
    {
      nowpoint = samplePoints[0];
      samplePoints[0].first = 1;
    }
    pair<int,Vector2i> tempoint;
    for (size_t j = 0; j < samplePoints.size(); j++)
    {
      distance = calPointLength(nowpoint.second,samplePoints[j].second);
      dis_end1 = calPointLength(samplePoints[j].second,grid_map_end);
      dis_end2 = calPointLength(nowpoint.second,grid_map_end);

      bool has_obstacle = CheckObstaclePoints(samplePoints[j].second,lastpoint.second);
      
      if(distance < min_distance && samplePoints[j].first == 0 && j>i && has_obstacle == false && dis_end1<dis_end2)
      {
        min_distance = distance;
        tempoint = samplePoints[j];
        samplePoints[j].first = 1;
        flag = j;
      }
      if(distance < min_distance && samplePoints[j].first == 0 && j>i)
      {
        min_distance = distance;
        tempoint = samplePoints[j];
        samplePoints[j].first = 1;
        flag = j;
      }
    }

    if(flag==(int)samplePoints.size()-1)
    {
      for (int num = 0; num < flag; num++)
      {
        samplePoints[num].first = 1;
      }
    }

    nowpoint = tempoint;
    samplePoints[flag].first = 1;

    optpath.push_back(nowpoint.second);
    lastpoint = nowpoint;
  }

  optpath.push_back(grid_map_end);

  interpolation_path.clear();
  Setlength_Interpolation_Path(0.1,optpath,interpolation_path);

  needivipath.clear();
  Setlength_DividPath(0.1,interpolation_path,needivipath);

  vector<int> collinear_Num = CollinearPosition(needivipath); 

  needoptpath.clear();
  DividPath(needivipath,collinear_Num,needoptpath);

  notoptpath.clear();
  notoptpath = GridPathToWorldPath(optpath);
  
  worldpath.clear();
  worldpath = BezierPathOpt(needoptpath);
  worldpath.insert(worldpath.begin(),mapToWorld(grid_map_start));

  return worldpath;
}

// 获取走廊访问的节点
int Fast_Security::getCorridorSTATE_VISITEDNum(void)
{
  int STATE_VISITED_num = 0;
  for (size_t i = 0; i < search_data.size(); i++)
  {
    if(search_data[i] >= 1)
    {
      STATE_VISITED_num++;
    }
  }
  return STATE_VISITED_num;
}

// 获取最终优化过的路径的长度
double Fast_Security::getOptedPathLength(void)
{
  double length = 0.0;
  for (size_t i = 1; i < optedpath.size(); i++)
  {
    length += calPointLength(optedpath[i],optedpath[i-1]);
  }
  
  return length;
}

void Fast_Security::visual_SamplesNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish, vector<vector<Vector2d>> samplenodes,
float a_set,float r_set,float g_set,float b_set,float k_length)
{
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = "map";
  // ROS 2 时间戳获取
  node_vis.header.stamp = rclcpp::Clock().now();

  node_vis.ns = "fast_security_STATE_VISITED";

  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  
  node_vis.id = 0;
  node_vis.color.a = a_set;
  node_vis.color.r = r_set;
  node_vis.color.g = g_set;
  node_vis.color.b = b_set;

  node_vis.pose.orientation.x = 0.0;
  node_vis.pose.orientation.y = 0.0;
  node_vis.pose.orientation.z = 0.0;
  node_vis.pose.orientation.w = 1.0;

  node_vis.scale.x = resolution * k_length;
  node_vis.scale.y = resolution * k_length;
  node_vis.scale.z = resolution * k_length;

  geometry_msgs::msg::Point pt;
  int sampleNum = samplenodes.size();
  for (int i = 0; i < sampleNum; i++)
  {
    vector<Vector2d> tempoints = samplenodes[i];
    int tempsize = tempoints.size(); 
    for (int j = 0; j < tempsize; j++)
    {
      pt.x = tempoints[j][0];
      pt.y = tempoints[j][1];
      node_vis.points.push_back(pt);
    }
  }

  pathPublish->publish(node_vis);  
}

void Fast_Security::visual_STATE_VISITEDNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish, std::vector<Eigen::Vector2d> visitnodes,
float a_set,float r_set,float g_set,float b_set,float length)
{
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = "map";
  node_vis.header.stamp = rclcpp::Clock().now();

  node_vis.color.a = a_set;
  node_vis.color.r = r_set;
  node_vis.color.g = g_set;
  node_vis.color.b = b_set;
  node_vis.ns = "fast_security_STATE_VISITED";

  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  node_vis.id = 0;

  node_vis.pose.orientation.x = 0.0;
  node_vis.pose.orientation.y = 0.0;
  node_vis.pose.orientation.z = 0.0;
  node_vis.pose.orientation.w = 1.0;

  node_vis.scale.x = resolution*length;
  node_vis.scale.y = resolution*length;
  node_vis.scale.z = resolution*length;

  geometry_msgs::msg::Point pt;
  for (int i = 0; i < int(visitnodes.size()); i++)
  {
    pt.x = visitnodes[i][0];
    pt.y = visitnodes[i][1];
    node_vis.points.push_back(pt);
  }

  pathPublish->publish(node_vis);
}