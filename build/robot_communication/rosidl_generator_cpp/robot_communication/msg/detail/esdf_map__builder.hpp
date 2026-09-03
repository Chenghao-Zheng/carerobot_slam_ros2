// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:msg/EsdfMap.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__BUILDER_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/msg/detail/esdf_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace msg
{

namespace builder
{

class Init_EsdfMap_data
{
public:
  explicit Init_EsdfMap_data(::robot_communication::msg::EsdfMap & msg)
  : msg_(msg)
  {}
  ::robot_communication::msg::EsdfMap data(::robot_communication::msg::EsdfMap::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::msg::EsdfMap msg_;
};

class Init_EsdfMap_height
{
public:
  explicit Init_EsdfMap_height(::robot_communication::msg::EsdfMap & msg)
  : msg_(msg)
  {}
  Init_EsdfMap_data height(::robot_communication::msg::EsdfMap::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_EsdfMap_data(msg_);
  }

private:
  ::robot_communication::msg::EsdfMap msg_;
};

class Init_EsdfMap_width
{
public:
  explicit Init_EsdfMap_width(::robot_communication::msg::EsdfMap & msg)
  : msg_(msg)
  {}
  Init_EsdfMap_height width(::robot_communication::msg::EsdfMap::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_EsdfMap_height(msg_);
  }

private:
  ::robot_communication::msg::EsdfMap msg_;
};

class Init_EsdfMap_resolution
{
public:
  explicit Init_EsdfMap_resolution(::robot_communication::msg::EsdfMap & msg)
  : msg_(msg)
  {}
  Init_EsdfMap_width resolution(::robot_communication::msg::EsdfMap::_resolution_type arg)
  {
    msg_.resolution = std::move(arg);
    return Init_EsdfMap_width(msg_);
  }

private:
  ::robot_communication::msg::EsdfMap msg_;
};

class Init_EsdfMap_origin_y
{
public:
  explicit Init_EsdfMap_origin_y(::robot_communication::msg::EsdfMap & msg)
  : msg_(msg)
  {}
  Init_EsdfMap_resolution origin_y(::robot_communication::msg::EsdfMap::_origin_y_type arg)
  {
    msg_.origin_y = std::move(arg);
    return Init_EsdfMap_resolution(msg_);
  }

private:
  ::robot_communication::msg::EsdfMap msg_;
};

class Init_EsdfMap_origin_x
{
public:
  Init_EsdfMap_origin_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EsdfMap_origin_y origin_x(::robot_communication::msg::EsdfMap::_origin_x_type arg)
  {
    msg_.origin_x = std::move(arg);
    return Init_EsdfMap_origin_y(msg_);
  }

private:
  ::robot_communication::msg::EsdfMap msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::msg::EsdfMap>()
{
  return robot_communication::msg::builder::Init_EsdfMap_origin_x();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__BUILDER_HPP_
