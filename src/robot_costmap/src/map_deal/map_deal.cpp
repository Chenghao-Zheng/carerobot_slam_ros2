#include "map_deal/map_deal.h"

#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;
using namespace Eigen;

namespace map_deal
{

deal_all_map::deal_all_map(const rclcpp::NodeOptions & options) : Node("deal_all_map_node", options)
{
  // 基础参数初始化
  InitParams();

  // 1. 设置匹配 map_server 的 QoS 策略 (TransientLocal + Reliable)
  auto map_qos = rclcpp::QoS(rclcpp::KeepLast(1)).transient_local().reliable();

  // 2. 订阅地图话题消息 (修复 QoS 不匹配导致的接收不到地图问题)
  map_subscriber = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
      "/map", map_qos, std::bind(&deal_all_map::MapCallback, this, std::placeholders::_1));
      
  if(is_use_sim)
  {
    localizationSub = this->create_subscription<nav_msgs::msg::Odometry>(
        "/odom", 1, std::bind(&deal_all_map::localizationCallback, this, std::placeholders::_1));
    pointCloud2Sub = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/cloud_map", 10, std::bind(&deal_all_map::pointCloud2Callback, this, std::placeholders::_1));
    clickSub = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        "/goal_pose", 10, std::bind(&deal_all_map::clickCallback, this, std::placeholders::_1));
  }
  else
  {
    localizationSub = this->create_subscription<nav_msgs::msg::Odometry>(
        "/carto_odom", 1, std::bind(&deal_all_map::localizationCallback, this, std::placeholders::_1));
    pointCloud2Sub = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/cloud_map", 10, std::bind(&deal_all_map::pointCloud2Callback, this, std::placeholders::_1));

    clickSub = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        "/goal_pose", 10, std::bind(&deal_all_map::clickCallback, this, std::placeholders::_1));
  }

  global_inflate_map_publiser = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/global_map_inflate", rclcpp::QoS(10).transient_local());
  global_esdf_map_publisher = this->create_publisher<robot_communication::msg::EsdfMap>("/global_esdf_map", rclcpp::QoS(10).transient_local());
  global_esdf_map_display_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/global_map_esdf_display", rclcpp::QoS(10).transient_local());
  global_cost_map_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/global_cost_map", rclcpp::QoS(10).transient_local());

  local_map_publiser = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/local_map", 10);
  local_map_inflate_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/local_map_inflate", 10);
  local_map_esdf_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/local_map_esdf", 10);
  local_esdf_map_publisher = this->create_publisher<robot_communication::msg::EsdfMap>("/local_esdf_map", 10);
  local_map_cost_publisher = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/local_map_cost", 10);

  update_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(50), std::bind(&deal_all_map::updateLocalMapCallback, this));

  laser_scan_subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/scan", 1, std::bind(&deal_all_map::ScanCallback, this, std::placeholders::_1));
}

deal_all_map::~deal_all_map()
{
}

void deal_all_map::InitParams(void)
{
  // ---------- 声明并读取原有参数 ----------
  if (!this->has_parameter("local_map/xmin")) this->declare_parameter("local_map/xmin", -10.0);
  if (!this->has_parameter("local_map/ymin")) this->declare_parameter("local_map/ymin", -10.0);
  if (!this->has_parameter("local_map/xmax")) this->declare_parameter("local_map/xmax", 10.0);
  if (!this->has_parameter("local_map/ymax")) this->declare_parameter("local_map/ymax", 10.0);
  if (!this->has_parameter("local_map/laser_min_theta")) this->declare_parameter("local_map/laser_min_theta", -3.14);
  if (!this->has_parameter("local_map/laser_max_theta")) this->declare_parameter("local_map/laser_max_theta", 3.14);
  if (!this->has_parameter("local_map/resolution")) this->declare_parameter("local_map/resolution", 0.05);
  if (!this->has_parameter("local_map/inflate")) this->declare_parameter("local_map/inflate", 0.1);
  if (!this->has_parameter("local_map/virtual_map")) this->declare_parameter("local_map/virtual_map", 1.5);
  if (!this->has_parameter("local_map/is_use_sim")) this->declare_parameter("local_map/is_use_sim", true);

  this->get_parameter_or("local_map/xmin", map_x_min, -10.0);
  this->get_parameter_or("local_map/ymin", map_y_min, -10.0);
  this->get_parameter_or("local_map/xmax", map_x_max, 10.0);
  this->get_parameter_or("local_map/ymax", map_y_max, 10.0);
  this->get_parameter_or("local_map/laser_min_theta", laser_min_theta, -3.14);
  this->get_parameter_or("local_map/laser_max_theta", laser_max_theta, 3.14);
  this->get_parameter_or("local_map/resolution", resolution, 0.05);
  resolution_inv = 1.0 / resolution;
  this->get_parameter_or("local_map/inflate", inflate, 0.1);
  this->get_parameter_or("local_map/virtual_map", virtual_map, 1.5);
  this->get_parameter_or("local_map/is_use_sim", is_use_sim, true);

  // ---------- 新增：读取局部代价地图参数 ----------
  if (!this->has_parameter("local_cost_map/costdownvalue"))
      this->declare_parameter<int>("local_cost_map/costdownvalue", 40);
  if (!this->has_parameter("local_cost_map/costupvalue"))
      this->declare_parameter<int>("local_cost_map/costupvalue", 54);
  if (!this->has_parameter("local_cost_map/costdownk"))
      this->declare_parameter<double>("local_cost_map/costdownk", 0.0);
  if (!this->has_parameter("local_cost_map/costupk"))
      this->declare_parameter<double>("local_cost_map/costupk", 1.5);

  int local_costdownvalue, local_costupvalue;
  double local_costdownk, local_costupk;
  this->get_parameter("local_cost_map/costdownvalue", local_costdownvalue);
  this->get_parameter("local_cost_map/costupvalue", local_costupvalue);
  this->get_parameter("local_cost_map/costdownk", local_costdownk);
  this->get_parameter("local_cost_map/costupk", local_costupk);

  // ---------- 初始化各个地图处理器 ----------
  global_map_.reset(new global_map_deal);
  local_map_.reset(new local_map_deal);
  edt_environment.reset(new EDTEnvironment);

  // 全局代价地图参数
  global_map_->Set_CostMaparams();

  // 局部代价地图参数传递
  local_map_->Set_CostMaparams(local_costdownvalue, local_costupvalue, local_costdownk, local_costupk);

  // 其余初始化
  local_map_->Set_Maparams(resolution, inflate, true);
  localmap.info.width = (map_x_max - map_x_min) * resolution_inv;
  localmap.info.height = (map_y_max - map_y_min) * resolution_inv;
  localmap.info.resolution = resolution;
  localmap.data.resize(localmap.info.width * localmap.info.height);
}

void deal_all_map::clickCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  Vector2i gridpoint = worldToMap(Vector2d(msg->pose.position.x, msg->pose.position.y));
  cout << "grid value is" << (int)esdf_map_display_[gridpoint(0) + gridpoint(1) * global_map_x] << endl;
}

void deal_all_map::ScanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan_msg)
{
  assemDirect = false;

  if(assemDirect)
  {
    laser_max_theta = scan_msg->angle_max;
    laser_min_theta = scan_msg->angle_min;
  }
  else
  {
    laser_max_theta = scan_msg->angle_min;
    laser_min_theta = scan_msg->angle_max;
  }
}

void deal_all_map::localizationCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
  odom_ = *msg;
  odom_.header.frame_id = "base_link";

  double roll, pitch, yaw;
  tf2::Quaternion quat(
                        msg->pose.pose.orientation.x,
                        msg->pose.pose.orientation.y,
                        msg->pose.pose.orientation.z,
                        msg->pose.pose.orientation.w
                       );
  tf2::Matrix3x3(quat).getRPY(roll, pitch, yaw);

  robotYaw = yaw; 
  if(!is_use_sim)
  {
    static int time = 0;
    time++;
    if(has_odom_flag == false)
    {
      diffx = odom_.pose.pose.position.x;
      diffy = odom_.pose.pose.position.y;
    }

    if(time >= 200)
    {
      time = 0;
      has_odom_flag = true;
    }
  }
  else{
    has_odom_flag = true;
  }
}

void deal_all_map::pointCloud2Callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  pcl::fromROSMsg(*msg, localcloud);

  sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x");
  sensor_msgs::PointCloud2ConstIterator<float> iter_y(*msg, "y");

  float min_angle = std::numeric_limits<float>::max();
  float max_angle = std::numeric_limits<float>::lowest();

  for (; iter_x != iter_x.end(); ++iter_x, ++iter_y) {
    float x = *iter_x;
    float y = *iter_y;

    float angle = std::atan2(y, x);

    min_angle = std::min(min_angle, angle);
    max_angle = std::max(max_angle, angle);
  }

  local_map_->laser_max_theta = max_angle;
  local_map_->laser_min_theta = min_angle;

  has_rece_cloud = true;
}

void deal_all_map::laser2Cloud2Callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  pcl::fromROSMsg(*msg, laser2cloud);
}

void deal_all_map::MapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map)
{
  RCLCPP_INFO(this->get_logger(), "\033[1;32m ***********map message**********\033[0m");
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_x: %f  \033[0m", map->info.origin.position.x);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_y: %f  \033[0m", map->info.origin.position.y);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m resolution: %f  \033[0m", map->info.resolution);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m width: %d  \033[0m", map->info.width);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m height: %d  \033[0m", map->info.height);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m *********************************\033[0m");

  origin_x = map->info.origin.position.x;
  origin_y = map->info.origin.position.y;

  globalmap = *map;
  globalinflatemap = *map;

  global_map_x = globalinflatemap.info.width;
  global_map_y = globalinflatemap.info.height;

  global_map_->Set_Maparams(resolution, inflate, origin_x, origin_y, global_map_x, global_map_y);

  Vector2i actual_map_size, actual_map_start;
  global_map_->Infalte_Global_Map(
              Vector2i(global_map_x, global_map_y),
              &actual_map_size,
              &actual_map_start,
              globalinflatemap.data,
              inflate_map_);
              
  actual_map_x = actual_map_size[0];
  actual_map_y = actual_map_size[1];
  actual_map_startx = actual_map_start[0];
  actual_map_starty = actual_map_start[1];

  globalinflatemap.data = inflate_map_;
  global_inflate_map_publiser->publish(globalinflatemap);

  global_map_->Get_ActualMap
                (Vector2i(global_map_x, global_map_y),
                Vector2i(actual_map_x, actual_map_y),
                Vector2i(actual_map_startx, actual_map_starty),
                globalinflatemap.data,
                occupancy_buffer_);

  global_map_->Get_ESDFMap
              (Vector2i(global_map_x, global_map_y),
              Vector2i(actual_map_x, actual_map_y),
              Vector2i(actual_map_startx, actual_map_starty),
              occupancy_buffer_,
              esdf_map_display_);

  globalesdfmap = globalinflatemap;
  globalesdfmap.data = esdf_map_display_;

  global_esdf_map_display_publisher->publish(globalesdfmap);

  globalesdftest.origin_x = globalinflatemap.info.origin.position.x;
  globalesdftest.origin_y = globalinflatemap.info.origin.position.y;
  globalesdftest.width = globalinflatemap.info.width;
  globalesdftest.height = globalinflatemap.info.height;
  globalesdftest.resolution = globalinflatemap.info.resolution;

  global_map_->ESDF_Map(globalinflatemap.data, esdf_map_buffer_);
  globalesdftest.data = esdf_map_buffer_;
  global_esdf_map_publisher->publish(globalesdftest);

  globalcostmap = globalinflatemap;
  global_map_->Set_Cost_Map(Vector2i(globalinflatemap.info.width, globalinflatemap.info.height),
                            globalinflatemap.data,
                            globalcostmap.data);
  global_cost_map_publisher->publish(globalcostmap);

  has_global_map = true;
  has_been_inflate = true;
}

void deal_all_map::updateEsdfMapCallback()
{
  if(!has_been_inflate) return;

  Eigen::Vector2d center(odom_.pose.pose.position.x, odom_.pose.pose.position.y);
  Eigen::Vector2d disp(map_x_max - map_x_min, map_y_max - map_y_min);
}

void deal_all_map::updateLocalMapCallback()
{
  if(!has_rece_cloud){return;}
  if(!has_odom_flag) return;

  Eigen::Vector3d center(odom_.pose.pose.position.x, odom_.pose.pose.position.y, 0);
  
  if (isnan(center(0)) || isnan(center(1)) || isnan(center(2)))
    return;

  Eigen::Vector3d disp(map_x_max - map_x_min, map_y_max - map_y_min, 0);

  const int ifn = ceil(inflate * resolution_inv);
  
  Vector2d lower_x_y_world = Vector2d((center[0] - disp[0] / 2), (center[1] - disp[1] / 2));
  Vector2d upper_x_y_world = Vector2d((center[0] + disp[0] / 2), (center[1] + disp[1] / 2));

  Vector2i lower_x_y_map = worldToMap(lower_x_y_world);
  Vector2i upper_x_y_map = worldToMap(upper_x_y_world);
  int x_length = disp[0] * resolution_inv;
  int y_length = disp[1] * resolution_inv;

  localmap.header.frame_id = "odom";
  localmap.info.origin.position.x = lower_x_y_world[0];
  localmap.info.origin.position.y = lower_x_y_world[1];
  localmap.info.origin.position.z = 0;

  localmap.info.origin.orientation.x = 0;
  localmap.info.origin.orientation.y = 0;
  localmap.info.origin.orientation.z = 0;
  localmap.info.origin.orientation.w = 1;

  localmap.data.assign(localmap.info.width * localmap.info.height, 0);

  robotPose = Vector3d(odom_.pose.pose.position.x, odom_.pose.pose.position.y, robotYaw);

  obstacleLocal.clear();
  localmap.data = local_map_->Local_Tran_Global_Map(lower_x_y_world,
                                        Vector2i(localmap.info.width, localmap.info.height),
                                        robotPose,
                                        (localcloud + laser2cloud),
                                        obstacleLocal,
                                        Vector2d(diffx, diffy));

  localmap.header.stamp = this->now();
  local_map_publiser->publish(localmap);

  localinflatemap = localmap;
  local_map_->Infalte_Local_Map(Vector2i(localinflatemap.info.width, localinflatemap.info.height),
                    obstacleLocal,
                    localinflatemap.data);

  local_map_inflate_publisher->publish(localinflatemap);

  localcostmap = localinflatemap;
  
  local_map_->Set_Cost_Map(Vector2i(localinflatemap.info.width, localinflatemap.info.height),
                          localinflatemap.data,
                          localcostmap.data);

  local_map_cost_publisher->publish(localcostmap);

  rclcpp::Time start = this->now();

  vector<int8_t> tempesdf;
  
  localesdfmap = localinflatemap;
  local_map_->Get_ESDF_Local_Map(Vector2i(localmap.info.width, localmap.info.height),
                                  localinflatemap.data,
                                  tempesdf);

  // 安全修复：地图宽高、起点与数组越界检查
  int src_w = localmap.info.width;
  int src_h = localmap.info.height;

  int dst_w = std::ceil(virtual_map * src_w);
  int dst_h = std::ceil(virtual_map * src_h);

  localesdfmap.info.width = dst_w;
  localesdfmap.info.height = dst_h;
  localesdfmap.info.origin.position.x = localinflatemap.info.origin.position.x - (dst_w - src_w) * resolution / 2.0;
  localesdfmap.info.origin.position.y = localinflatemap.info.origin.position.y - (dst_h - src_h) * resolution / 2.0;

  localesdfmap.data.assign(dst_w * dst_h, 0);

  int offset_x = (dst_w - src_w) / 2;
  int offset_y = (dst_h - src_h) / 2;

  for (int y = 0; y < src_h; ++y)
  {
    for (int x = 0; x < src_w; ++x)
    {
      int src_idx = x + y * src_w;
      int dst_x = x + offset_x;
      int dst_y = y + offset_y;

      if (dst_x >= 0 && dst_x < dst_w && dst_y >= 0 && dst_y < dst_h)
      {
        int dst_idx = dst_x + dst_y * dst_w;
        if (src_idx >= 0 && src_idx < static_cast<int>(tempesdf.size()) &&
            dst_idx >= 0 && dst_idx < static_cast<int>(localesdfmap.data.size()))
        {
          localesdfmap.data[dst_idx] = tempesdf[src_idx];
        }
      }
    }
  }

  rclcpp::Time end = this->now();

  local_map_esdf_publisher->publish(localesdfmap);

  localesdftest.origin_x = localesdfmap.info.origin.position.x;
  localesdftest.origin_y = localesdfmap.info.origin.position.y;
  localesdftest.width = localesdfmap.info.width;
  localesdftest.height = localesdfmap.info.height;
  localesdftest.resolution = localesdfmap.info.resolution;

  local_esdf_map_publisher->publish(localesdftest);
}

} // namespace map_dealyy