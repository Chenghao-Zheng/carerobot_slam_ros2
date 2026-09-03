// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:msg/Goal.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__BUILDER_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/msg/detail/goal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace msg
{

namespace builder
{

class Init_Goal_position_yaw
{
public:
  explicit Init_Goal_position_yaw(::robot_communication::msg::Goal & msg)
  : msg_(msg)
  {}
  ::robot_communication::msg::Goal position_yaw(::robot_communication::msg::Goal::_position_yaw_type arg)
  {
    msg_.position_yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::msg::Goal msg_;
};

class Init_Goal_position_y
{
public:
  explicit Init_Goal_position_y(::robot_communication::msg::Goal & msg)
  : msg_(msg)
  {}
  Init_Goal_position_yaw position_y(::robot_communication::msg::Goal::_position_y_type arg)
  {
    msg_.position_y = std::move(arg);
    return Init_Goal_position_yaw(msg_);
  }

private:
  ::robot_communication::msg::Goal msg_;
};

class Init_Goal_position_x
{
public:
  Init_Goal_position_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Goal_position_y position_x(::robot_communication::msg::Goal::_position_x_type arg)
  {
    msg_.position_x = std::move(arg);
    return Init_Goal_position_y(msg_);
  }

private:
  ::robot_communication::msg::Goal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::msg::Goal>()
{
  return robot_communication::msg::builder::Init_Goal_position_x();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__BUILDER_HPP_
