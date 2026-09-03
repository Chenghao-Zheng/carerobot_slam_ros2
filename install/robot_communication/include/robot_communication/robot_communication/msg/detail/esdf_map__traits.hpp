// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_communication:msg/EsdfMap.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__TRAITS_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_communication/msg/detail/esdf_map__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_communication
{

namespace msg
{

inline void to_flow_style_yaml(
  const EsdfMap & msg,
  std::ostream & out)
{
  out << "{";
  // member: origin_x
  {
    out << "origin_x: ";
    rosidl_generator_traits::value_to_yaml(msg.origin_x, out);
    out << ", ";
  }

  // member: origin_y
  {
    out << "origin_y: ";
    rosidl_generator_traits::value_to_yaml(msg.origin_y, out);
    out << ", ";
  }

  // member: resolution
  {
    out << "resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.resolution, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EsdfMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: origin_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "origin_x: ";
    rosidl_generator_traits::value_to_yaml(msg.origin_x, out);
    out << "\n";
  }

  // member: origin_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "origin_y: ";
    rosidl_generator_traits::value_to_yaml(msg.origin_y, out);
    out << "\n";
  }

  // member: resolution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resolution: ";
    rosidl_generator_traits::value_to_yaml(msg.resolution, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EsdfMap & msg, bool use_flow_style = false)
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
  const robot_communication::msg::EsdfMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_communication::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_communication::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_communication::msg::EsdfMap & msg)
{
  return robot_communication::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_communication::msg::EsdfMap>()
{
  return "robot_communication::msg::EsdfMap";
}

template<>
inline const char * name<robot_communication::msg::EsdfMap>()
{
  return "robot_communication/msg/EsdfMap";
}

template<>
struct has_fixed_size<robot_communication::msg::EsdfMap>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_communication::msg::EsdfMap>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_communication::msg::EsdfMap>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__TRAITS_HPP_
