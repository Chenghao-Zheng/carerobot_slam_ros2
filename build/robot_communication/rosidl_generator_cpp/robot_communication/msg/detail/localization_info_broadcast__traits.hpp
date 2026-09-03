// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__TRAITS_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_communication/msg/detail/localization_info_broadcast__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_communication
{

namespace msg
{

inline void to_flow_style_yaml(
  const LocalizationInfoBroadcast & msg,
  std::ostream & out)
{
  out << "{";
  // member: xposition
  {
    out << "xposition: ";
    rosidl_generator_traits::value_to_yaml(msg.xposition, out);
    out << ", ";
  }

  // member: yposition
  {
    out << "yposition: ";
    rosidl_generator_traits::value_to_yaml(msg.yposition, out);
    out << ", ";
  }

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

  // member: xaccel
  {
    out << "xaccel: ";
    rosidl_generator_traits::value_to_yaml(msg.xaccel, out);
    out << ", ";
  }

  // member: yaccel
  {
    out << "yaccel: ";
    rosidl_generator_traits::value_to_yaml(msg.yaccel, out);
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
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocalizationInfoBroadcast & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: xposition
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xposition: ";
    rosidl_generator_traits::value_to_yaml(msg.xposition, out);
    out << "\n";
  }

  // member: yposition
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yposition: ";
    rosidl_generator_traits::value_to_yaml(msg.yposition, out);
    out << "\n";
  }

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

  // member: xaccel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xaccel: ";
    rosidl_generator_traits::value_to_yaml(msg.xaccel, out);
    out << "\n";
  }

  // member: yaccel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaccel: ";
    rosidl_generator_traits::value_to_yaml(msg.yaccel, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocalizationInfoBroadcast & msg, bool use_flow_style = false)
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
  const robot_communication::msg::LocalizationInfoBroadcast & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_communication::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_communication::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_communication::msg::LocalizationInfoBroadcast & msg)
{
  return robot_communication::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_communication::msg::LocalizationInfoBroadcast>()
{
  return "robot_communication::msg::LocalizationInfoBroadcast";
}

template<>
inline const char * name<robot_communication::msg::LocalizationInfoBroadcast>()
{
  return "robot_communication/msg/LocalizationInfoBroadcast";
}

template<>
struct has_fixed_size<robot_communication::msg::LocalizationInfoBroadcast>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_communication::msg::LocalizationInfoBroadcast>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_communication::msg::LocalizationInfoBroadcast>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__TRAITS_HPP_
