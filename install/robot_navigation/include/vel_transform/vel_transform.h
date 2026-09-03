#ifndef VEL_TRANSFORM_VEL_TRANSFORM_H_
#define VEL_TRANSFORM_VEL_TRANSFORM_H_

#include <Eigen/Dense>

#include <cmath>
#include <vector>
#include <chrono>

#define LIMIT(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))

struct Odom_data
{
  double yaw{0.0};   // 偏航角
  double pitch{0.0}; // 俯仰角
  double roll{0.0};  // 横滚角度

  double gyroYaw{0.0}; // 角速度

  double Vx{0.0}; // x轴方向上的速度
  double Vy{0.0}; // y轴方向上的速度

  double Accx{0.0}; // x轴方向上的加速度
  double Accy{0.0}; // y轴方向上的加速度

  double theta{0.0}; // arctan(Vy/Vx) 速度矢量合成角度
};

using Odom_data_define = struct Odom_data;

namespace vel_transform
{
  // 局部速度转全局速度
  void LocalVelocityToGlobal(Odom_data_define *localVelocity, Odom_data_define *globalVelocity);
  
  // 局部加速度转全局加速度
  void LocalAcceleraToGlobal(Odom_data_define *localVelocity, Odom_data_define *globalVelocity);
  
  // 全局速度转局部速度
  void GlobalVelocityToLocal(Odom_data_define *localVelocity, Odom_data_define *globalVelocity);
  void GlobalVelocityToLocalVelocity(Odom_data_define *localVelocity, Odom_data_define *globalVelocity);
  void GlobalVelocityToLocalVector(Odom_data_define *localVelocity, Odom_data_define *globalVelocity);
  
  // 几何计算辅助函数
  double calPointLength(Eigen::Vector2d vector1, Eigen::Vector2d vector2);
  double calVectorAngle(Eigen::Vector2d vector1, Eigen::Vector2d vector2);
  Eigen::Vector2d calUnitvector(Eigen::Vector2d unitv);

} // namespace vel_transform

#endif // VEL_TRANSFORM_VEL_TRANSFORM_H_