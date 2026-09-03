// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:msg/Bspline.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__BUILDER_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/msg/detail/bspline__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace msg
{

namespace builder
{

class Init_Bspline_start_time
{
public:
  explicit Init_Bspline_start_time(::robot_communication::msg::Bspline & msg)
  : msg_(msg)
  {}
  ::robot_communication::msg::Bspline start_time(::robot_communication::msg::Bspline::_start_time_type arg)
  {
    msg_.start_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::msg::Bspline msg_;
};

class Init_Bspline_pts
{
public:
  explicit Init_Bspline_pts(::robot_communication::msg::Bspline & msg)
  : msg_(msg)
  {}
  Init_Bspline_start_time pts(::robot_communication::msg::Bspline::_pts_type arg)
  {
    msg_.pts = std::move(arg);
    return Init_Bspline_start_time(msg_);
  }

private:
  ::robot_communication::msg::Bspline msg_;
};

class Init_Bspline_knots
{
public:
  explicit Init_Bspline_knots(::robot_communication::msg::Bspline & msg)
  : msg_(msg)
  {}
  Init_Bspline_pts knots(::robot_communication::msg::Bspline::_knots_type arg)
  {
    msg_.knots = std::move(arg);
    return Init_Bspline_pts(msg_);
  }

private:
  ::robot_communication::msg::Bspline msg_;
};

class Init_Bspline_traj_id
{
public:
  explicit Init_Bspline_traj_id(::robot_communication::msg::Bspline & msg)
  : msg_(msg)
  {}
  Init_Bspline_knots traj_id(::robot_communication::msg::Bspline::_traj_id_type arg)
  {
    msg_.traj_id = std::move(arg);
    return Init_Bspline_knots(msg_);
  }

private:
  ::robot_communication::msg::Bspline msg_;
};

class Init_Bspline_order
{
public:
  Init_Bspline_order()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bspline_traj_id order(::robot_communication::msg::Bspline::_order_type arg)
  {
    msg_.order = std::move(arg);
    return Init_Bspline_traj_id(msg_);
  }

private:
  ::robot_communication::msg::Bspline msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::msg::Bspline>()
{
  return robot_communication::msg::builder::Init_Bspline_order();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__BUILDER_HPP_
