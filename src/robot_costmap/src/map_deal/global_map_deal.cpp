/*
 * @Author: your name
 * @Date: 2023-08-11 13:17:38
 * @LastEditTime: 2026-08-31
 * @LastEditors: your name
 * @Description: Converted to ROS 2
 * @FilePath: /MyFormProject/src/robot_costmap/src/map_deal/global_map_deal.cpp
 * 可以输入预定的版权声明、个性签名、空行等
 */
#include "map_deal/global_map_deal.h"


namespace map_deal
{

global_map_deal::global_map_deal(/* args */) : Node("global_map_deal_node")
{
  resolution = 0.05;
  resolution_inv = 1.0/resolution;

  inflate = 0.5;
}

global_map_deal::~global_map_deal()
{
}

void global_map_deal::init()
{
  have_odom_ = false;
  map_valid_ = false;

  // 传参地图膨胀半径
  this->declare_parameter<double>("global_map/inflate", 0.5);
  this->get_parameter("global_map/inflate", inflate);

  Set_CostMaparams();

  // 订阅全局地图消息
  map_subscriber = this->create_subscription<nav_msgs::msg::OccupancyGrid>("/map", 1, std::bind(&global_map_deal::MapCallback, this, std::placeholders::_1));
  // 订阅里程计消息
  localizationSub = this->create_subscription<nav_msgs::msg::Odometry>("/carto_odom", 1, std::bind(&global_map_deal::localizationCallback, this, std::placeholders::_1));

  // 发布全局地图消息
  global_inflate_map_publiser = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/global_map_inflate", rclcpp::QoS(10).transient_local());
  // 发布全局距离场地图消息
  global_esdf_map_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/global_esdf_map", rclcpp::QoS(10).transient_local());
}

void global_map_deal::Set_CostMaparams()
{
  // 设定全局代价地图上下阈值
  this->declare_parameter<int>("global_cost_map/costdownvalue", 40);
  this->get_parameter("global_cost_map/costdownvalue", costdownvalue);
  this->declare_parameter<int>("global_cost_map/costupvalue", 54);
  this->get_parameter("global_cost_map/costupvalue", costupvalue);

  // 设定全局代价地图上下阈值系数 , 这两个系数与上下阈值的乘积不能超过100
  this->declare_parameter<double>("global_cost_map/costdownk", 0.0);
  this->get_parameter("global_cost_map/costdownk", costdownk);
  this->declare_parameter<double>("global_cost_map/costupk", 1.5);
  this->get_parameter("global_cost_map/costupk", costupk);

  // 设定人工势场宽度
  this->declare_parameter<int>("global_cost_map/esdfwidth", 2);
  this->get_parameter("global_cost_map/esdfwidth", esdfwidth);

  cout<<"up k"<<costupk<<endl;
  cout<<"down k"<<costdownk<<endl;

  cout<<"up value"<<costupvalue<<endl;
  cout<<"down value"<<costdownvalue<<endl;

}

void global_map_deal::localizationCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  odom_ = *msg;
  odom_.header.frame_id = "base_link";
  // 获取到里程计
  have_odom_ = true;
}

void global_map_deal::MapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map)
{
  RCLCPP_INFO(this->get_logger(), "\033[1;32m ***********map message**********\033[0m");
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_x: %f  \033[0m",
           map->info.origin.position.x);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_y: %f  \033[0m",
           map->info.origin.position.y);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m resolution: %f  \033[0m",
           map->info.resolution);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m width: %d  \033[0m",
           map->info.width);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m height: %d  \033[0m",
           map->info.height);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m *********************************\033[0m");

  origin_x = map->info.origin.position.x;
  origin_y = map->info.origin.position.y;

  globalinflatemap = *map;

  // 参数初始化
  Set_Maparams(resolution,inflate,
  globalinflatemap.info.origin.position.x,globalinflatemap.info.origin.position.y,
  globalinflatemap.info.width,globalinflatemap.info.height);

  Vector2i actual_map_size,actual_map_start;
  // 膨胀地图
  Infalte_Global_Map(
              Vector2i(grid_map_x,grid_map_y),
              &actual_map_size,
              &actual_map_start,
              globalinflatemap.data,
              inflate_map_);
              
  actual_map_x = actual_map_size[0];
  actual_map_y = actual_map_size[1];
  actual_map_startx = actual_map_start[0];
  actual_map_starty = actual_map_start[1];

  has_been_inflate = true;

  // 传递膨胀地图参数
  globalinflatemap.data = inflate_map_;
  // 发布膨胀地图
  global_inflate_map_publiser->publish(globalinflatemap);

  // 提取有效地图
  Get_ActualMap(Vector2i(grid_map_x,grid_map_y),
                Vector2i(actual_map_x,actual_map_y),
                Vector2i(actual_map_startx,actual_map_starty),
                globalinflatemap.data,
                occupancy_buffer_);
  
  // 获取全局ESDF地图
  Get_ESDFMap(Vector2i(grid_map_x,grid_map_y),
              Vector2i(actual_map_x,actual_map_y),
              Vector2i(actual_map_startx,actual_map_starty),
              occupancy_buffer_,
              esdf_map_buffer_);

  // 传参
  globalesdfmap = globalinflatemap;
  // 对esdf地图赋值
  globalesdfmap.data = esdf_map_buffer_;

  // cout<<"esdf_map_buffer_size  "<<esdf_map_buffer_.size()<<endl;
  // 发布势场地图
  global_esdf_map_publisher->publish(globalesdfmap);

  // 地图有效
  map_valid_ = true;

}

// 获取障碍物地图
void global_map_deal::Infalte_Map(vector<int8_t> mapdata,vector<int8_t> &inflatemap)
{
  vector<Vector2i> obs;
  // 清空
  obs.clear();

  // 从栅格地图中获取障碍物点的信息
  for(int x = 0;x<grid_map_x;x++)
  {
    for(int y = 0;y<grid_map_y;y++)
    {
      // 当其中为障碍物的时候
      if(mapdata[x+grid_map_x*y] == 100)
      {
        obs.push_back(Vector2i(x,y));
      }
    }
  }

  // 计算膨胀多少格
  const int ifnlocal = ceil(inflate * resolution_inv);

  // 初始化容器大小
  inflatemap.resize(grid_map_x*grid_map_y);

  for(size_t i=0;i<obs.size();i++)
  {
    // 膨胀地图
    for (int x = -ifnlocal; x <= ifnlocal; ++x)
    {
      for (int y = -ifnlocal; y <= ifnlocal; ++y)
      {
        if((obs[i][0]+x)+(obs[i][1]+y)*grid_map_x < 0 ||
            (obs[i][0]+x) < 0 ||
            (obs[i][1]+y) < 0 ||
            (obs[i][0]+x) > grid_map_x ||
            (obs[i][1]+y) > grid_map_y ||
            (obs[i][0]+x)+(obs[i][1]+y)*grid_map_x >= grid_map_x*grid_map_y)
            {
              continue;
            }
        else
        {
          inflatemap[(obs[i][0]+x)+(obs[i][1]+y)*grid_map_x] = 100;
        }
      }
    }    
  }
}

// 全局代价地图
// mapSize地图尺寸参数
// inflatemap膨胀地图
// costmap代价地图
void global_map_deal::Set_Cost_Map(Vector2i mapSize, vector<int8_t> inflatemap, vector<int8_t> &costmap)
{
  int x_size = mapSize[0];
  int y_size = mapSize[1];

  costmap.resize(x_size * y_size);
  costmap.assign(x_size * y_size, 0);

  // 获取障碍物（膨胀地图值为100）
  vector<Vector2i> obstacle;
  for (int x = 0; x < x_size; x++) {
    for (int y = 0; y < y_size; y++) {
      if (inflatemap[x + y * x_size] == 100) {
        obstacle.push_back(Vector2i(x, y));
      }
    }
  }

  // 初始化代价地图为膨胀地图（100为障碍）
  costmap = inflatemap;

  // ---- 第一层膨胀，代价设为95（紧邻障碍物） ----
  for (size_t i = 0; i < obstacle.size(); i++) {
    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        int nx = obstacle[i][0] + x;
        int ny = obstacle[i][1] + y;
        if (nx < 0 || nx >= x_size || ny < 0 || ny >= y_size) continue;
        int idx = nx + ny * x_size;
        if (costmap[idx] == 100) continue;
        costmap[idx] = 90;
      }
    }
  }

  // ---- 第二层膨胀，代价设为85 ----
  vector<Vector2i> cost95;
  for (int x = 0; x < x_size; x++) {
    for (int y = 0; y < y_size; y++) {
      if (costmap[x + y * x_size] == 95) {
        cost95.push_back(Vector2i(x, y));
      }
    }
  }
  for (size_t i = 0; i < cost95.size(); i++) {
    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        int nx = cost95[i][0] + x;
        int ny = cost95[i][1] + y;
        if (nx < 0 || nx >= x_size || ny < 0 || ny >= y_size) continue;
        int idx = nx + ny * x_size;
        if (costmap[idx] == 100 || costmap[idx] == 95) continue;
        costmap[idx] = 80;
      }
    }
  }

  // ---- 第三层膨胀，代价设为70 ----
  vector<Vector2i> cost85;
  for (int x = 0; x < x_size; x++) {
    for (int y = 0; y < y_size; y++) {
      if (costmap[x + y * x_size] == 85) {
        cost85.push_back(Vector2i(x, y));
      }
    }
  }
  for (size_t i = 0; i < cost85.size(); i++) {
    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        int nx = cost85[i][0] + x;
        int ny = cost85[i][1] + y;
        if (nx < 0 || nx >= x_size || ny < 0 || ny >= y_size) continue;
        int idx = nx + ny * x_size;
        if (costmap[idx] == 100 || costmap[idx] == 95 || costmap[idx] == 85) continue;
        costmap[idx] = 70;
      }
    }
  }

  // ---- 第四层膨胀，代价设为50 ----
  vector<Vector2i> cost70;
  for (int x = 0; x < x_size; x++) {
    for (int y = 0; y < y_size; y++) {
      if (costmap[x + y * x_size] == 70) {
        cost70.push_back(Vector2i(x, y));
      }
    }
  }
  for (size_t i = 0; i < cost70.size(); i++) {
    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        int nx = cost70[i][0] + x;
        int ny = cost70[i][1] + y;
        if (nx < 0 || nx >= x_size || ny < 0 || ny >= y_size) continue;
        int idx = nx + ny * x_size;
        if (costmap[idx] == 100 || costmap[idx] == 95 || costmap[idx] == 85 || costmap[idx] == 70) continue;
        costmap[idx] = 50;
      }
    }
  }

  // ---- 第五层膨胀，代价设为30（可选，使梯度更平滑） ----
  vector<Vector2i> cost50;
  for (int x = 0; x < x_size; x++) {
    for (int y = 0; y < y_size; y++) {
      if (costmap[x + y * x_size] == 50) {
        cost50.push_back(Vector2i(x, y));
      }
    }
  }
  for (size_t i = 0; i < cost50.size(); i++) {
    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        int nx = cost50[i][0] + x;
        int ny = cost50[i][1] + y;
        if (nx < 0 || nx >= x_size || ny < 0 || ny >= y_size) continue;
        int idx = nx + ny * x_size;
        if (costmap[idx] == 100 || costmap[idx] == 95 || costmap[idx] == 85 || costmap[idx] == 70 || costmap[idx] == 50) continue;
        costmap[idx] = 30;
      }
    }
  }
}

// occupancy_map膨胀地图
// esdfmap 人工势场地图
void global_map_deal::ESDF_Map(vector<int8_t> occupancy_map,vector<int32_t> &esdfmap)
{
  // 获得膨胀地图
  std::array<int, 2> size{grid_map_x,grid_map_y};
  GridMap2D<uint8_t> grid_map2;

  // 设定地图图片大小
  grid_map2.set_cell_number(size);
  // 设定图片起点
  grid_map2.set_origin(std::array<double, 2>{0.0, 0.0});
  // 设定分辨率
  grid_map2.set_resolution(std::array<double, 2>{resolution,resolution});

  for(int x=0;x<grid_map_x;x++)
  {
    for(int y=0;y<grid_map_y;y++)
    {
      // 对地图取反赋值，在opencv中白色是255 黑色是0，但是rviz中习惯0是白色可通过，黑色是不可通过
      if(occupancy_map[x+y*grid_map_x] == 100)
      {
        grid_map2.SetValue(x,y,0);
      }
      else
      {
        grid_map2.SetValue(x,y,1);
      }
    }
  }

  // 构建带符号人工距离场
  SignedDistanceField2D sdf2(std::move(grid_map2));
  auto t0 = chrono::high_resolution_clock::now();

  // 更新人工距离场
  sdf2.UpdateSDF();

  auto t1 = chrono::high_resolution_clock::now();
  double total_ms =
      chrono::duration_cast<chrono::microseconds>(t1 - t0).count() / 1000.0;

  cout << "time for sdf: " << total_ms << " ms" << endl;
  
  // 获取势场的极大值极小值
  Vector2d min_max = sdf2.esdf().getESDFMax_and_Min();

  vector<double> local_esdf_buffer;
  // 获取人工势场地图
  // 重构esdf的大小
  local_esdf_buffer.resize(grid_map_x*grid_map_y);
  // 获取地图
  local_esdf_buffer = sdf2.esdf().map_data_;

  // 定义rviz可以显示发布的人工势场地图
  esdfmap.resize(grid_map_x*grid_map_y);
  // 填充esdf地图
  fill(esdfmap.begin(),esdfmap.end(),-1);

  // 定义rviz可以显示发布的人工势场地图
  esdf_map_test.resize(grid_map_x*grid_map_y);
  // 填充esdf地图
  fill(esdf_map_test.begin(),esdf_map_test.end(),-1);

  const int damageNum = esdfwidth;

  // 赋值
  for(int x=0;x<grid_map_x;x++)
  {
    for(int y=0;y<grid_map_y;y++)
    {
      if(local_esdf_buffer[x+y*grid_map_x] > 0)
      {
        // rviz中障碍物是100
        esdfmap[x+y*grid_map_x] = 1000000;
        esdf_map_test[x+y*grid_map_x] = 10000;
      }
      else
      {
        // 小于0的距离是到障碍物的距离，但是如果使用的是ros自带的地图信息太少了，按照ros的地图范围是
        // -128--127 0-100代表正常地图范围，100是障碍物，严重降低了势场地图可用性
        // 不如代价地图好用
        if((int)local_esdf_buffer[x+y*grid_map_x] >= -damageNum)
        {
          esdfmap[x+y*grid_map_x] = pow(10,damageNum+(int)local_esdf_buffer[x+y*grid_map_x]);
        }
        else
        {
          esdfmap[x+y*grid_map_x] = 0;
        }
      }
      // 对势场地图赋值
      esdf_map_test[x+y*grid_map_x] = 100+(int)local_esdf_buffer[x+y*grid_map_x];
    }
  } 
}

void global_map_deal::Set_Maparams(double resolution_,double inflate_,double origin_x_,double origin_y_,double map_x_size,double map_y_size)
{
  resolution = resolution_;
  resolution_inv = 1.0/resolution;

  inflate = inflate_;

  // 获得地图起点
  origin_x = origin_x_;
  origin_y = origin_y_;

  // 获得栅格地图尺寸
  grid_map_x = map_x_size;
  grid_map_y = map_y_size;

  mapover_x = grid_map_x*resolution;
  mapover_y = grid_map_y*resolution;

  cout<<"origin x:"<<origin_x<<endl;
  cout<<"origin y:"<<origin_y<<endl;

  cout<<"grid_map x:"<<grid_map_x<<endl;
  cout<<"grid_map y:"<<grid_map_y<<endl;

  cout<<"resolution:"<<resolution<<endl;

  cout<<"inflate:"<<inflate<<endl;
}

// 获取ESDF地图是可以从rviz中显示的地图
// actualmapSize真实地图尺寸
// occupancy_map膨胀地图
// esdfmap最终的人工势场地图可以用rviz显示
void global_map_deal::Get_ESDFMap(Vector2i mapSize,Vector2i actualmapSize,Vector2i actualmapStart,
vector<int8_t> occupancy_map,vector<int8_t> &esdfmap)
{
  int x_size = mapSize[0];
  int y_size = mapSize[1];

  // 获取真实地图的尺寸
  int actual_x_size = actualmapSize[0];
  int actual_y_size = actualmapSize[1];

  int actual_map_startx,actual_map_starty;

  actual_map_startx = actualmapStart[0];
  actual_map_starty = actualmapStart[1];

  // 获得膨胀地图
  std::array<int, 2> size{actual_x_size,actual_y_size};
  GridMap2D<uint8_t> grid_map;

  grid_map.set_cell_number(size);
  grid_map.set_origin(std::array<double, 2>{0.0, 0.0});
  grid_map.set_resolution(std::array<double, 2>{resolution,resolution});

  for(int x=0;x<actual_x_size;x++)
  {
    for(int y=0;y<actual_y_size;y++)
    {
      // 对地图取反赋值，在opencv中白色是255 黑色是0，但是rviz中习惯0是白色可通过，黑色是不可通过
      grid_map.SetValue(x,y,!occupancy_map[x+y*actual_x_size]);
    }
  }

  // 构建带符号人工距离场
  SignedDistanceField2D sdf(std::move(grid_map));
  auto t0 = chrono::high_resolution_clock::now();

  // 更新人工距离场
  sdf.UpdateSDF();

  auto t1 = chrono::high_resolution_clock::now();
  double total_ms =
      chrono::duration_cast<chrono::microseconds>(t1 - t0).count() / 1000.0;

  cout << "time for sdf: " << total_ms << " ms" << endl;

  // 获取势场的极大值极小值
  Vector2d min_max = sdf.esdf().getESDFMax_and_Min();

  // 求取分辨率
  double scale = 100.0/abs(min_max[1]-min_max[0]);

  // 获取人工势场地图
  // 重构esdf的大小
  esdf_buffer_.resize(actual_x_size*actual_y_size);
  // 获取地图
  esdf_buffer_ = sdf.esdf().map_data_;

  // 重构地图大小
  esdfmap.resize(x_size*y_size);
  // 填充esdf地图
  fill(esdfmap.begin(),esdfmap.end(),-1);

  // 对全局esdf地图赋值
  global_esdf_buffer_.resize(x_size*y_size);
  // 填充esdf地图
  fill(global_esdf_buffer_.begin(),global_esdf_buffer_.end(),10000);

  // 赋值
  for(int x=0;x<actual_x_size;x++)
  {
    for(int y=0;y<actual_y_size;y++)
    {
      if(sdf.esdf().GetValue(x,y) > 0)
      {
        // rviz中障碍物是100
        esdfmap[(x+actual_map_startx)+(y+actual_map_starty)*x_size] = 100;
      }
      else
      {
        esdfmap[(x+actual_map_startx)+(y+actual_map_starty)*x_size] =
        int((esdf_buffer_[x+y*actual_x_size]-min_max[0])*scale*1.5);
      }

      global_esdf_buffer_[(x+actual_map_startx)+(y+actual_map_starty)*x_size] =
        esdf_buffer_[x+y*actual_x_size];
    }
  }
}

// 全局地图膨胀
// mapSize地图尺寸参数
// actualmapSize 实际地图的尺寸
// actualmapStart 实际地图的起点和终点
// oldmap原本的地图参数
// inflatemap膨胀地图
void global_map_deal::Infalte_Global_Map(Vector2i mapSize,Vector2i *actualmapSize,Vector2i *actualmapStart,vector<int8_t> oldmap,vector<int8_t> &inflatemap)
{
  // 实际地图尺寸归0
  int actual_map_x_size = 0;
  int actual_map_y_size = 0;

  // 实际地图起点归0 x y
  int actual_map_start_x = 0;
  int actual_map_start_y = 0;

  // map的x y尺寸
  int x_size = mapSize[0],y_size = mapSize[1];

  map_array_define *deal_img_data;

  // // 重构地图处理数组大小
  deal_img_data = new map_array_define[x_size*y_size];

  // 遍历全局地图并发布全局膨胀地图
  for(int x=0;x<x_size;x++)
  {
    bool actual_map_flag = false;

    for(int y=0;y<y_size;y++)
    {
      // 无障碍物区域
      if((int)oldmap[x+y*x_size] != -1)
      {
        // 障碍物的status赋值为1
        if((int)oldmap[x+y*x_size] == 100)
        {
          deal_img_data[x+y*x_size].status = 1;
        }
        else
        {
          deal_img_data[x+y*x_size].status = 0;
        }
        actual_map_flag = true;

        // 为膨胀状态
        deal_img_data[x+y*x_size].infla_flag = false;       
      }
      else  // -1不在地图考虑范围之内
      {
        deal_img_data[x+y*x_size].status = -1;
        // -1默认已经膨胀完毕
        deal_img_data[x+y*x_size].infla_flag = true;
      }
      // 赋值
      deal_img_data[x+y*x_size].num = oldmap[x+y*x_size];
    }
    
    // 用来获取实际的有用部分的地图x轴方向的大小
    if(actual_map_flag == true)
    {
      actual_map_x_size++;
      // 记录x轴起点位置
      if(actual_map_x_size == 1)
      {
        actual_map_start_x = x;
        // 一般情况下地图的x 和 y是相同的
        actual_map_start_y = actual_map_start_x;
      }
    }
  }

  // 遍历全局地图并发布全局膨胀地图
  for(int y=0;y<y_size;y++)
  {
    bool actual_map_flag = false;

    for(int x=0;x<x_size;x++)
    {
      // 无障碍物区域
      if((int)oldmap[x*y_size+y] != -1)
      {
        actual_map_flag = true;
      }
    }
    // 用来获取实际的有用部分的地图y轴方向的大小
    if(actual_map_flag == true)
    {
      actual_map_y_size++;
      // 记录x轴起点位置
      if(actual_map_y_size == 1)
      {
        actual_map_start_y = y;
      }
    }
  }

  // 定义膨胀多少格
  const int ifn = ceil(inflate * resolution_inv);
  // const int ifn = ceil(0.38 * 20);

  // 开始膨胀
  for(int x=0;x<x_size;x++)
  {
    for(int y=0;y<y_size;y++)
    {
      // 只考虑障碍物附近开始膨胀num = 100是障碍物 num = 0是可通过区域 status = 0代表没膨胀过
      if(deal_img_data[x+y*x_size].num == 100 && deal_img_data[x+y*x_size].status == 1)
      {
        for(int infx = -ifn;infx<ifn;infx++)
        {
          for(int infy = -ifn;infy<ifn;infy++)
          {
            // 之前不是障碍物但是被膨胀过了就不处理了，提高效率
            if(deal_img_data[(x+infx)+(y+infy)*x_size].infla_flag == true &&
               deal_img_data[(x+infx)+(y+infy)*x_size].status == 0 )
               {
                continue;
               }
            else if(x+infx < 0 || x+infx >= x_size || y+infy < 0 || y+infy >= y_size)
            {
              continue;
            }
            else
            {
              deal_img_data[(x+infx)+(y+infy)*x_size].num = 100;
              deal_img_data[(x+infx)+(y+infy)*x_size].infla_flag = true;
              deal_img_data[x+y*x_size].infla_flag = true;    //当前中心点已经被膨胀过
            }
          }
        }
      }
    }
  }

  inflatemap.resize(x_size*y_size);

  // 把膨胀地图传参发布
  for(int x=0;x<x_size;x++)
  {
    for(int y=0;y<y_size;y++)
    {
      inflatemap[x+y*x_size] = deal_img_data[x+y*x_size].num;
    }
  }

  delete[] deal_img_data;

  // 传递参数
  (*actualmapSize)[0] = actual_map_x_size;
  (*actualmapSize)[1] = actual_map_y_size;

  // 传递参数
  (*actualmapStart)[0] = actual_map_start_x;
  (*actualmapStart)[1] = actual_map_start_y;

  cout<<"end"<<endl;
}

// 获取实际地图并把地图参数转换为0 1方便后续生成人工势场
// 必须在Infalte_Global_Map之后使用
// mapSize原来地图尺寸
// actualmapSize真实地图尺寸
// actualStart真实地图的起点
// oldmap原本的地图参数
// actualmap真正的地图
void global_map_deal::Get_ActualMap(Vector2i mapSize,Vector2i actualmapSize,Vector2i actualStart,vector<int8_t> oldmap,vector<int8_t> &actualmap)
{
  int x_size = mapSize[0];
  int y_size = mapSize[1];

  int actual_x_size = actualmapSize[0];
  int actual_y_size = actualmapSize[1];

  int actual_startx = actualStart[0];
  int actual_starty = actualStart[1];

  // 构建真实地图尺寸大小
  actualmap.resize(actual_x_size*actual_y_size);

  for(int x=0;x<actual_x_size;x++)
  {
    for(int y=0;y<actual_y_size;y++)
    {
      if(oldmap[(x+actual_startx)+(y+actual_starty)*x_size] != 0)
      {
        actualmap[x+y*actual_x_size] = 1;
      }
      else
      {
        actualmap[x+y*actual_x_size] = 0;
      }
    }
  }  
}

// 返回当前坐标的距离值
double global_map_deal::getDistance(Eigen::Vector2d pos)
{
  if (!isInMap(pos))
      return -1;

  Eigen::Vector2i id;
  id = worldToMap(pos);

  // 返回距离场 获取当前距离值
  return -global_esdf_buffer_[id(0)+id(1)*grid_map_x];
}

double global_map_deal::getDistance(Eigen::Vector2i id)
{
  id(0) = max(min(id(0), grid_map_x - 1), 0);
  id(1) = max(min(id(1), grid_map_y - 1), 0);

  // 返回距离场 获取当前距离值
  return -global_esdf_buffer_[id(0)+id(1)*grid_map_x];
}

// 在ESDF地图的基础上获取代价地图，即忽略代价地图某一代价值以下的地图
// 必须在获取代价地图之后使用
vector<int8_t> global_map_deal::Get_CostMap(vector<int8_t> esdf_map)
{
  vector<int8_t> map;

  map.resize(grid_map_x*grid_map_y);
  // 填充代价地图
  for (int x = 0; x < grid_map_x; x++)
  {
    for(int y=0;y < grid_map_y;y++)
    {
      //  80以下全按照80处理
      if(esdf_map[x+y*grid_map_x] >= 0 && esdf_map[x+y*grid_map_x] <= costdownvalue)
      {
        map[x+y*grid_map_x] = 0;
      }
      else if(esdf_map[x+y*grid_map_x] > costdownvalue && esdf_map[x+y*grid_map_x] <= costupvalue)
      {
        map[x+y*grid_map_x] = (int)(costdownk*esdf_map[x+y*grid_map_x]);
      }
      else if(esdf_map[x+y*grid_map_x] > costupvalue && esdf_map[x+y*grid_map_x] < 100)
      {
        map[x+y*grid_map_x] = (int)(costupk*esdf_map[x+y*grid_map_x]);
      }
      else
      {
        map[x+y*grid_map_x] = (int)esdf_map[x+y*grid_map_x];
      }
    }
  }
  
  return map;
}

void global_map_deal::getInterpolationData(const Eigen::Vector2d &pos, vector<Eigen::Vector2d> &pos_vec, Eigen::Vector2d &diff)
{
  if (!isInMap(pos))
  {
      // cout << "pos invalid for interpolation." << endl;
  }

  /* interpolation position */
  Eigen::Vector2d pos_m = pos - 0.5 * resolution * Eigen::Vector2d::Ones();

  Eigen::Vector2i idx;
  idx = worldToMap(pos_m);

  Eigen::Vector2d idx_pos;
  idx_pos = mapToWorld(idx);

  diff = (pos - idx_pos) * resolution_inv; // (x - x0) / (x1 - x0)

  pos_vec.clear();

  // cout<<"pos_m: "<<pos_m(0)<<"  "<<pos_m(1)<<endl;

  // 计算待求点(x, y)周围的4个点的pos(xi, yi)
  for (int x = 0; x < 2; x++)
    for (int y = 0; y < 2; y++)
    {
      Eigen::Vector2i current_idx = idx + Eigen::Vector2i(x, y);
      Eigen::Vector2d current_pos;
      // 将栅格地图转换为世界地图
      current_pos = mapToWorld(current_idx);
      // cout<<"current_pos "<<current_pos(0)<<"  "<<current_pos(1)<<"  "<<endl;
      pos_vec.push_back(current_pos); // C000, C001, C010, C011, C100, C101, C110, C111
    }
}


} // namespace map_deal