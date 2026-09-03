// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:msg/EsdfMap.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__STRUCT_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/EsdfMap in the package robot_communication.
/**
  * 栅格地图的原点x值(相对世界坐标系),单位为m
 */
typedef struct robot_communication__msg__EsdfMap
{
  float origin_x;
  /// 栅格地图的原点y值(相对世界坐标系),单位为m
  float origin_y;
  /// 栅格地图的分辨率
  float resolution;
  /// 栅格地图的宽
  float width;
  /// 栅格地图的高
  float height;
  /// 一维数组，数组内的数据表示为对应栅格的占用概率。
  /// 栅格地图中每一个小格的坐标对应一维数组中的一个数据。
  /// 栅格数据大小代表当前点到障碍物的距离数值
  /// -值表示未知区域
  rosidl_runtime_c__int32__Sequence data;
} robot_communication__msg__EsdfMap;

// Struct for a sequence of robot_communication__msg__EsdfMap.
typedef struct robot_communication__msg__EsdfMap__Sequence
{
  robot_communication__msg__EsdfMap * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__msg__EsdfMap__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__STRUCT_H_
