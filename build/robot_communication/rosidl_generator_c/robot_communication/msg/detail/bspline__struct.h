// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:msg/Bspline.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__STRUCT_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'knots'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'pts'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'start_time'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/Bspline in the package robot_communication.
typedef struct robot_communication__msg__Bspline
{
  int32_t order;
  int64_t traj_id;
  rosidl_runtime_c__double__Sequence knots;
  geometry_msgs__msg__Point__Sequence pts;
  builtin_interfaces__msg__Time start_time;
} robot_communication__msg__Bspline;

// Struct for a sequence of robot_communication__msg__Bspline.
typedef struct robot_communication__msg__Bspline__Sequence
{
  robot_communication__msg__Bspline * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__msg__Bspline__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__STRUCT_H_
