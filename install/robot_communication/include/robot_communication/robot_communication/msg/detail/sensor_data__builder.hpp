// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/msg/detail/sensor_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace msg
{

namespace builder
{

class Init_SensorData_timestamp_10us
{
public:
  explicit Init_SensorData_timestamp_10us(::robot_communication::msg::SensorData & msg)
  : msg_(msg)
  {}
  ::robot_communication::msg::SensorData timestamp_10us(::robot_communication::msg::SensorData::_timestamp_10us_type arg)
  {
    msg_.timestamp_10us = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::msg::SensorData msg_;
};

class Init_SensorData_yaw
{
public:
  explicit Init_SensorData_yaw(::robot_communication::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_timestamp_10us yaw(::robot_communication::msg::SensorData::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_SensorData_timestamp_10us(msg_);
  }

private:
  ::robot_communication::msg::SensorData msg_;
};

class Init_SensorData_local_y_accel
{
public:
  explicit Init_SensorData_local_y_accel(::robot_communication::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_yaw local_y_accel(::robot_communication::msg::SensorData::_local_y_accel_type arg)
  {
    msg_.local_y_accel = std::move(arg);
    return Init_SensorData_yaw(msg_);
  }

private:
  ::robot_communication::msg::SensorData msg_;
};

class Init_SensorData_local_x_accel
{
public:
  explicit Init_SensorData_local_x_accel(::robot_communication::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_local_y_accel local_x_accel(::robot_communication::msg::SensorData::_local_x_accel_type arg)
  {
    msg_.local_x_accel = std::move(arg);
    return Init_SensorData_local_y_accel(msg_);
  }

private:
  ::robot_communication::msg::SensorData msg_;
};

class Init_SensorData_local_y_veloc
{
public:
  explicit Init_SensorData_local_y_veloc(::robot_communication::msg::SensorData & msg)
  : msg_(msg)
  {}
  Init_SensorData_local_x_accel local_y_veloc(::robot_communication::msg::SensorData::_local_y_veloc_type arg)
  {
    msg_.local_y_veloc = std::move(arg);
    return Init_SensorData_local_x_accel(msg_);
  }

private:
  ::robot_communication::msg::SensorData msg_;
};

class Init_SensorData_local_x_veloc
{
public:
  Init_SensorData_local_x_veloc()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorData_local_y_veloc local_x_veloc(::robot_communication::msg::SensorData::_local_x_veloc_type arg)
  {
    msg_.local_x_veloc = std::move(arg);
    return Init_SensorData_local_y_veloc(msg_);
  }

private:
  ::robot_communication::msg::SensorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::msg::SensorData>()
{
  return robot_communication::msg::builder::Init_SensorData_local_x_veloc();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__BUILDER_HPP_
