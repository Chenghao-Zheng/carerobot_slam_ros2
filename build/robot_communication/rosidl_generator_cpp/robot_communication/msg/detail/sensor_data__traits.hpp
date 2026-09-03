// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_communication:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_communication/msg/detail/sensor_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_communication
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorData & msg,
  std::ostream & out)
{
  out << "{";
  // member: local_x_veloc
  {
    out << "local_x_veloc: ";
    rosidl_generator_traits::value_to_yaml(msg.local_x_veloc, out);
    out << ", ";
  }

  // member: local_y_veloc
  {
    out << "local_y_veloc: ";
    rosidl_generator_traits::value_to_yaml(msg.local_y_veloc, out);
    out << ", ";
  }

  // member: local_x_accel
  {
    out << "local_x_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.local_x_accel, out);
    out << ", ";
  }

  // member: local_y_accel
  {
    out << "local_y_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.local_y_accel, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: timestamp_10us
  {
    out << "timestamp_10us: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_10us, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: local_x_veloc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "local_x_veloc: ";
    rosidl_generator_traits::value_to_yaml(msg.local_x_veloc, out);
    out << "\n";
  }

  // member: local_y_veloc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "local_y_veloc: ";
    rosidl_generator_traits::value_to_yaml(msg.local_y_veloc, out);
    out << "\n";
  }

  // member: local_x_accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "local_x_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.local_x_accel, out);
    out << "\n";
  }

  // member: local_y_accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "local_y_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.local_y_accel, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: timestamp_10us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp_10us: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_10us, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorData & msg, bool use_flow_style = false)
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
  const robot_communication::msg::SensorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_communication::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_communication::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_communication::msg::SensorData & msg)
{
  return robot_communication::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_communication::msg::SensorData>()
{
  return "robot_communication::msg::SensorData";
}

template<>
inline const char * name<robot_communication::msg::SensorData>()
{
  return "robot_communication/msg/SensorData";
}

template<>
struct has_fixed_size<robot_communication::msg::SensorData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_communication::msg::SensorData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_communication::msg::SensorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__TRAITS_HPP_
