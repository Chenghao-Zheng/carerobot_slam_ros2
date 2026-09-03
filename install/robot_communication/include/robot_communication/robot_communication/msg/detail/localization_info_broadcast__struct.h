// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__STRUCT_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/LocalizationInfoBroadcast in the package robot_communication.
/**
  * 定位消息广播需要数据
  * 全局x位置
 */
typedef struct robot_communication__msg__LocalizationInfoBroadcast
{
  float xposition;
  /// 全局y位置
  float yposition;
  /// 全局x轴线速度
  float xspeed;
  /// 全局y轴线速度
  float yspeed;
  /// 车体x加速度
  float xaccel;
  /// 车体y加速度
  float yaccel;
  /// 底盘角度
  float chassisangle;
  /// 底盘角速度
  float chassisgyro;
  /// 时间戳
  uint32_t timestamp;
} robot_communication__msg__LocalizationInfoBroadcast;

// Struct for a sequence of robot_communication__msg__LocalizationInfoBroadcast.
typedef struct robot_communication__msg__LocalizationInfoBroadcast__Sequence
{
  robot_communication__msg__LocalizationInfoBroadcast * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__msg__LocalizationInfoBroadcast__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__STRUCT_H_
