// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__BUILDER_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/msg/detail/chassis_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace msg
{

namespace builder
{

class Init_ChassisControl_globalorlocal
{
public:
  explicit Init_ChassisControl_globalorlocal(::robot_communication::msg::ChassisControl & msg)
  : msg_(msg)
  {}
  ::robot_communication::msg::ChassisControl globalorlocal(::robot_communication::msg::ChassisControl::_globalorlocal_type arg)
  {
    msg_.globalorlocal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::msg::ChassisControl msg_;
};

class Init_ChassisControl_timestamp
{
public:
  explicit Init_ChassisControl_timestamp(::robot_communication::msg::ChassisControl & msg)
  : msg_(msg)
  {}
  Init_ChassisControl_globalorlocal timestamp(::robot_communication::msg::ChassisControl::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_ChassisControl_globalorlocal(msg_);
  }

private:
  ::robot_communication::msg::ChassisControl msg_;
};

class Init_ChassisControl_chassisgyro
{
public:
  explicit Init_ChassisControl_chassisgyro(::robot_communication::msg::ChassisControl & msg)
  : msg_(msg)
  {}
  Init_ChassisControl_timestamp chassisgyro(::robot_communication::msg::ChassisControl::_chassisgyro_type arg)
  {
    msg_.chassisgyro = std::move(arg);
    return Init_ChassisControl_timestamp(msg_);
  }

private:
  ::robot_communication::msg::ChassisControl msg_;
};

class Init_ChassisControl_chassisangle
{
public:
  explicit Init_ChassisControl_chassisangle(::robot_communication::msg::ChassisControl & msg)
  : msg_(msg)
  {}
  Init_ChassisControl_chassisgyro chassisangle(::robot_communication::msg::ChassisControl::_chassisangle_type arg)
  {
    msg_.chassisangle = std::move(arg);
    return Init_ChassisControl_chassisgyro(msg_);
  }

private:
  ::robot_communication::msg::ChassisControl msg_;
};

class Init_ChassisControl_yspeed
{
public:
  explicit Init_ChassisControl_yspeed(::robot_communication::msg::ChassisControl & msg)
  : msg_(msg)
  {}
  Init_ChassisControl_chassisangle yspeed(::robot_communication::msg::ChassisControl::_yspeed_type arg)
  {
    msg_.yspeed = std::move(arg);
    return Init_ChassisControl_chassisangle(msg_);
  }

private:
  ::robot_communication::msg::ChassisControl msg_;
};

class Init_ChassisControl_xspeed
{
public:
  Init_ChassisControl_xspeed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChassisControl_yspeed xspeed(::robot_communication::msg::ChassisControl::_xspeed_type arg)
  {
    msg_.xspeed = std::move(arg);
    return Init_ChassisControl_yspeed(msg_);
  }

private:
  ::robot_communication::msg::ChassisControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::msg::ChassisControl>()
{
  return robot_communication::msg::builder::Init_ChassisControl_xspeed();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__BUILDER_HPP_
