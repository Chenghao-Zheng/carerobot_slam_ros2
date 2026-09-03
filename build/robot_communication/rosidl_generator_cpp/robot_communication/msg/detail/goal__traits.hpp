// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_communication:msg/Goal.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__TRAITS_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_communication/msg/detail/goal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_communication
{

namespace msg
{

inline void to_flow_style_yaml(
  const Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: position_x
  {
    out << "position_x: ";
    rosidl_generator_traits::value_to_yaml(msg.position_x, out);
    out << ", ";
  }

  // member: position_y
  {
    out << "position_y: ";
    rosidl_generator_traits::value_to_yaml(msg.position_y, out);
    out << ", ";
  }

  // member: position_yaw
  {
    out << "position_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.position_yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: position_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_x: ";
    rosidl_generator_traits::value_to_yaml(msg.position_x, out);
    out << "\n";
  }

  // member: position_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_y: ";
    rosidl_generator_traits::value_to_yaml(msg.position_y, out);
    out << "\n";
  }

  // member: position_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.position_yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robot_communication

namespace rosidl_generator_traits
{

[[deprecated("use robot_communication::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_communication::msg::Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_communication::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_communication::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_communication::msg::Goal & msg)
{
  return robot_communication::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_communication::msg::Goal>()
{
  return "robot_communication::msg::Goal";
}

template<>
inline const char * name<robot_communication::msg::Goal>()
{
  return "robot_communication/msg/Goal";
}

template<>
struct has_fixed_size<robot_communication::msg::Goal>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_communication::msg::Goal>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_communication::msg::Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__TRAITS_HPP_
