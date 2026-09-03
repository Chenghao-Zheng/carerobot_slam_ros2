#pragma once

#ifndef MAP_DEAL_H_
#define MAP_DEAL_H_

#include <memory>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

// 引入子模块头文件
#include "map_deal/global_map_deal.h"
#include "map_deal/local_map_deal.h"
#include "map_deal/edt_environment.h"

// 引入自定义 ESDF 消息头文件
#include "robot_communication/msg/esdf_map.hpp"

namespace map_deal
{

class deal_all_map : public rclcpp::Node
{
public:
  explicit deal_all_map(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~deal_all_map();

  void InitParams(void);
  void clickCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
  void ScanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan_msg);
  void localizationCallback(const nav_msgs::msg::Odometry::SharedPtr msg);
  void pointCloud2Callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void laser2Cloud2Callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void MapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map);
  void updateEsdfMapCallback();
  void updateLocalMapCallback();

  Eigen::Vector2i worldToMap(const Eigen::Vector2d& worldpt) const
  {
    int mx = static_cast<int>((worldpt[0] - origin_x) * resolution_inv);
    int my = static_cast<int>((worldpt[1] - origin_y) * resolution_inv);
    return Eigen::Vector2i(mx, my);
  }

private:
  // ROS 2 订阅者与发布者
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_subscriber;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr localizationSub;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointCloud2Sub;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr clickSub;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_scan_subscriber_;

  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr global_inflate_map_publiser;
  rclcpp::Publisher<robot_communication::msg::EsdfMap>::SharedPtr global_esdf_map_publisher;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr global_esdf_map_display_publisher;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr global_cost_map_publisher;

  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr local_map_publiser;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr local_map_inflate_publisher;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr local_map_esdf_publisher;
  rclcpp::Publisher<robot_communication::msg::EsdfMap>::SharedPtr local_esdf_map_publisher;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr local_map_cost_publisher;

  rclcpp::TimerBase::SharedPtr update_timer_;

  // 地图及运动状态变量
  double map_x_min{-10.0}, map_x_max{10.0}, map_y_min{-10.0}, map_y_max{10.0};
  double laser_min_theta{-3.14}, laser_max_theta{3.14};
  double resolution{0.05}, resolution_inv{20.0}, inflate{0.1}, virtual_map{1.5};
  bool is_use_sim{true};
  bool assemDirect{false};
  bool has_odom_flag{false};
  bool has_rece_cloud{false};
  bool has_global_map{false};
  bool has_been_inflate{false};

  double robotYaw{0.0};
  double diffx{0.0}, diffy{0.0};
  double origin_x{0.0}, origin_y{0.0};
  int global_map_x{0}, global_map_y{0};
  int actual_map_x{0}, actual_map_y{0};
  int actual_map_startx{0}, actual_map_starty{0};

  Eigen::Vector3d robotPose;
  nav_msgs::msg::Odometry odom_;

  nav_msgs::msg::OccupancyGrid globalmap, globalinflatemap, globalesdfmap, globalcostmap;
  nav_msgs::msg::OccupancyGrid localmap, localinflatemap, localesdfmap, localcostmap;
  robot_communication::msg::EsdfMap globalesdftest, localesdftest;

  std::vector<int8_t> inflate_map_;
  std::vector<int8_t> occupancy_buffer_;
  std::vector<int8_t> esdf_map_display_;
  std::vector<int32_t> esdf_map_buffer_;
  
  // 修改为 Vector2i 类型匹配 local_map_deal
  std::vector<Eigen::Vector2i> obstacleLocal;

  pcl::PointCloud<pcl::PointXYZ> localcloud;
  pcl::PointCloud<pcl::PointXYZ> laser2cloud;

  std::shared_ptr<global_map_deal> global_map_;
  std::shared_ptr<local_map_deal> local_map_;
  std::shared_ptr<EDTEnvironment> edt_environment;
};

} // namespace map_deal

#endif // MAP_DEAL_H_