// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__STRUCT_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/SensorData in the package robot_communication.
/**
  * 接收到下位机发送的消息，轮速计、IMU、时间戳等
  * 局部速度
 */
typedef struct robot_communication__msg__SensorData
{
  float local_x_veloc;
  float local_y_veloc;
  /// 局部加速度
  float local_x_accel;
  float local_y_accel;
  /// yaw轴数值
  float yaw;
  /// 时间戳 10us是时间戳的分辨率
  uint32_t timestamp_10us;
} robot_communication__msg__SensorData;

// Struct for a sequence of robot_communication__msg__SensorData.
typedef struct robot_communication__msg__SensorData__Sequence
{
  robot_communication__msg__SensorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__msg__SensorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__STRUCT_H_
