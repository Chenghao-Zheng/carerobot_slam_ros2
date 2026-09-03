// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_communication:msg/Bspline.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__TRAITS_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_communication/msg/detail/bspline__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pts'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'start_time'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace robot_communication
{

namespace msg
{

inline void to_flow_style_yaml(
  const Bspline & msg,
  std::ostream & out)
{
  out << "{";
  // member: order
  {
    out << "order: ";
    rosidl_generator_traits::value_to_yaml(msg.order, out);
    out << ", ";
  }

  // member: traj_id
  {
    out << "traj_id: ";
    rosidl_generator_traits::value_to_yaml(msg.traj_id, out);
    out << ", ";
  }

  // member: knots
  {
    if (msg.knots.size() == 0) {
      out << "knots: []";
    } else {
      out << "knots: [";
      size_t pending_items = msg.knots.size();
      for (auto item : msg.knots) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: pts
  {
    if (msg.pts.size() == 0) {
      out << "pts: []";
    } else {
      out << "pts: [";
      size_t pending_items = msg.pts.size();
      for (auto item : msg.pts) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: start_time
  {
    out << "start_time: ";
    to_flow_style_yaml(msg.start_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Bspline & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: order
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "order: ";
    rosidl_generator_traits::value_to_yaml(msg.order, out);
    out << "\n";
  }

  // member: traj_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "traj_id: ";
    rosidl_generator_traits::value_to_yaml(msg.traj_id, out);
    out << "\n";
  }

  // member: knots
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.knots.size() == 0) {
      out << "knots: []\n";
    } else {
      out << "knots:\n";
      for (auto item : msg.knots) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: pts
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pts.size() == 0) {
      out << "pts: []\n";
    } else {
      out << "pts:\n";
      for (auto item : msg.pts) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: start_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_time:\n";
    to_block_style_yaml(msg.start_time, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Bspline & msg, bool use_flow_style = false)
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
  const robot_communication::msg::Bspline & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_communication::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_communication::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_communication::msg::Bspline & msg)
{
  return robot_communication::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_communication::msg::Bspline>()
{
  return "robot_communication::msg::Bspline";
}

template<>
inline const char * name<robot_communication::msg::Bspline>()
{
  return "robot_communication/msg/Bspline";
}

template<>
struct has_fixed_size<robot_communication::msg::Bspline>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_communication::msg::Bspline>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_communication::msg::Bspline>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__TRAITS_HPP_
