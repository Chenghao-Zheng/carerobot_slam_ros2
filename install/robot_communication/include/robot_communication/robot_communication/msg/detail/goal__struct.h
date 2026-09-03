// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:msg/Goal.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__STRUCT_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Goal in the package robot_communication.
/**
  * 目标点信息
  * x位置信息
 */
typedef struct robot_communication__msg__Goal
{
  float position_x;
  /// y位置信息
  float position_y;
  /// yaw轴角度信息
  float position_yaw;
} robot_communication__msg__Goal;

// Struct for a sequence of robot_communication__msg__Goal.
typedef struct robot_communication__msg__Goal__Sequence
{
  robot_communication__msg__Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__msg__Goal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__STRUCT_H_
