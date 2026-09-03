// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__BUILDER_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/msg/detail/localization_info_broadcast__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace msg
{

namespace builder
{

class Init_LocalizationInfoBroadcast_timestamp
{
public:
  explicit Init_LocalizationInfoBroadcast_timestamp(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  ::robot_communication::msg::LocalizationInfoBroadcast timestamp(::robot_communication::msg::LocalizationInfoBroadcast::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_chassisgyro
{
public:
  explicit Init_LocalizationInfoBroadcast_chassisgyro(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_timestamp chassisgyro(::robot_communication::msg::LocalizationInfoBroadcast::_chassisgyro_type arg)
  {
    msg_.chassisgyro = std::move(arg);
    return Init_LocalizationInfoBroadcast_timestamp(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_chassisangle
{
public:
  explicit Init_LocalizationInfoBroadcast_chassisangle(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_chassisgyro chassisangle(::robot_communication::msg::LocalizationInfoBroadcast::_chassisangle_type arg)
  {
    msg_.chassisangle = std::move(arg);
    return Init_LocalizationInfoBroadcast_chassisgyro(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_yaccel
{
public:
  explicit Init_LocalizationInfoBroadcast_yaccel(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_chassisangle yaccel(::robot_communication::msg::LocalizationInfoBroadcast::_yaccel_type arg)
  {
    msg_.yaccel = std::move(arg);
    return Init_LocalizationInfoBroadcast_chassisangle(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_xaccel
{
public:
  explicit Init_LocalizationInfoBroadcast_xaccel(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_yaccel xaccel(::robot_communication::msg::LocalizationInfoBroadcast::_xaccel_type arg)
  {
    msg_.xaccel = std::move(arg);
    return Init_LocalizationInfoBroadcast_yaccel(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_yspeed
{
public:
  explicit Init_LocalizationInfoBroadcast_yspeed(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_xaccel yspeed(::robot_communication::msg::LocalizationInfoBroadcast::_yspeed_type arg)
  {
    msg_.yspeed = std::move(arg);
    return Init_LocalizationInfoBroadcast_xaccel(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_xspeed
{
public:
  explicit Init_LocalizationInfoBroadcast_xspeed(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_yspeed xspeed(::robot_communication::msg::LocalizationInfoBroadcast::_xspeed_type arg)
  {
    msg_.xspeed = std::move(arg);
    return Init_LocalizationInfoBroadcast_yspeed(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_yposition
{
public:
  explicit Init_LocalizationInfoBroadcast_yposition(::robot_communication::msg::LocalizationInfoBroadcast & msg)
  : msg_(msg)
  {}
  Init_LocalizationInfoBroadcast_xspeed yposition(::robot_communication::msg::LocalizationInfoBroadcast::_yposition_type arg)
  {
    msg_.yposition = std::move(arg);
    return Init_LocalizationInfoBroadcast_xspeed(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

class Init_LocalizationInfoBroadcast_xposition
{
public:
  Init_LocalizationInfoBroadcast_xposition()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocalizationInfoBroadcast_yposition xposition(::robot_communication::msg::LocalizationInfoBroadcast::_xposition_type arg)
  {
    msg_.xposition = std::move(arg);
    return Init_LocalizationInfoBroadcast_yposition(msg_);
  }

private:
  ::robot_communication::msg::LocalizationInfoBroadcast msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::msg::LocalizationInfoBroadcast>()
{
  return robot_communication::msg::builder::Init_LocalizationInfoBroadcast_xposition();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__BUILDER_HPP_
