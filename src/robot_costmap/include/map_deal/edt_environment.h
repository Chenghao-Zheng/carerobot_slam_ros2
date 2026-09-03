/*
 * @Author: your name
 * @Date: 2023-08-17 20:24:16
 * @LastEditTime: 2026-08-31 17:19:09
 * @LastEditors: your name
 * @Description: EDT Environment adapted for ROS 2
 * @FilePath: /MyFormProject/src/robot_costmap/include/map_deal/edt_environment.h
 */
#ifndef _EDT_ENVIRONMENT_H_
#define _EDT_ENVIRONMENT_H_

#include <Eigen/Eigen>
#include <iostream>
#include <memory>
#include <vector>
#include <list>

// ROS 2 头文件替换
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>

#include "map_deal/global_map_deal.h"

using std::cout;
using std::endl;
using std::list;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;


namespace map_deal
{
class EDTEnvironment
{
private:
  /* data */
  double resolution_inv_;

public:
  EDTEnvironment(/* args */) {}
  ~EDTEnvironment() {}

  global_map_deal::Ptr global_map_;

  // 初始化
  void init();

  void setMap(shared_ptr<global_map_deal> map);

  void evaluateEDTWithGrad(const Eigen::Vector2d &pos, const double &time, double &dist,
                           Eigen::Vector2d &grad);

  double evaluateCoarseEDT(const Eigen::Vector2d &pos, const double &time);

  bool odomValid() { return global_map_->odomValid(); }
  bool mapValid() { return global_map_->mapValid(); }
  // 获取里程计消息
  nav_msgs::msg::Odometry getOdom() { return global_map_->getOdom(); }

  // void getMapRegion(Eigen::Vector3d &ori, Eigen::Vector3d &size) { sdf_map_->getRegion(ori, size); }

  // 智能指针
  typedef shared_ptr<EDTEnvironment> Ptr;
};
}

#endif