// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__STRUCT_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ChassisControl in the package robot_communication.
/**
  *  导航发布的消息
  * 全局x轴线速度
 */
typedef struct robot_communication__msg__ChassisControl
{
  float xspeed;
  /// 全局y轴线速度
  float yspeed;
  /// 底盘角度
  float chassisangle;
  /// 底盘角速度
  float chassisgyro;
  /// 时间戳
  uint32_t timestamp;
  /// 标志位局部控制还是全局控制
  bool globalorlocal;
} robot_communication__msg__ChassisControl;

// Struct for a sequence of robot_communication__msg__ChassisControl.
typedef struct robot_communication__msg__ChassisControl__Sequence
{
  robot_communication__msg__ChassisControl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__msg__ChassisControl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__STRUCT_H_
