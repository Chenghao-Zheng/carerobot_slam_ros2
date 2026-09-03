// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__TRAITS_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_communication/msg/detail/chassis_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_communication
{

namespace msg
{

inline void to_flow_style_yaml(
  const ChassisControl & msg,
  std::ostream & out)
{
  out << "{";
  // member: xspeed
  {
    out << "xspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.xspeed, out);
    out << ", ";
  }

  // member: yspeed
  {
    out << "yspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.yspeed, out);
    out << ", ";
  }

  // member: chassisangle
  {
    out << "chassisangle: ";
    rosidl_generator_traits::value_to_yaml(msg.chassisangle, out);
    out << ", ";
  }

  // member: chassisgyro
  {
    out << "chassisgyro: ";
    rosidl_generator_traits::value_to_yaml(msg.chassisgyro, out);
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: globalorlocal
  {
    out << "globalorlocal: ";
    rosidl_generator_traits::value_to_yaml(msg.globalorlocal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChassisControl & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: xspeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.xspeed, out);
    out << "\n";
  }

  // member: yspeed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yspeed: ";
    rosidl_generator_traits::value_to_yaml(msg.yspeed, out);
    out << "\n";
  }

  // member: chassisangle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassisangle: ";
    rosidl_generator_traits::value_to_yaml(msg.chassisangle, out);
    out << "\n";
  }

  // member: chassisgyro
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassisgyro: ";
    rosidl_generator_traits::value_to_yaml(msg.chassisgyro, out);
    out << "\n";
  }

  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << "\n";
  }

  // member: globalorlocal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "globalorlocal: ";
    rosidl_generator_traits::value_to_yaml(msg.globalorlocal, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChassisControl & msg, bool use_flow_style = false)
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
  const robot_communication::msg::ChassisControl & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_communication::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_communication::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_communication::msg::ChassisControl & msg)
{
  return robot_communication::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_communication::msg::ChassisControl>()
{
  return "robot_communication::msg::ChassisControl";
}

template<>
inline const char * name<robot_communication::msg::ChassisControl>()
{
  return "robot_communication/msg/ChassisControl";
}

template<>
struct has_fixed_size<robot_communication::msg::ChassisControl>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_communication::msg::ChassisControl>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_communication::msg::ChassisControl>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__TRAITS_HPP_
