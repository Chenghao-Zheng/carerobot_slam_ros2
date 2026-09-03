// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_communication:msg/Bspline.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__STRUCT_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pts'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'start_time'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robot_communication__msg__Bspline __attribute__((deprecated))
#else
# define DEPRECATED__robot_communication__msg__Bspline __declspec(deprecated)
#endif

namespace robot_communication
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Bspline_
{
  using Type = Bspline_<ContainerAllocator>;

  explicit Bspline_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : start_time(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->order = 0l;
      this->traj_id = 0ll;
    }
  }

  explicit Bspline_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : start_time(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->order = 0l;
      this->traj_id = 0ll;
    }
  }

  // field types and members
  using _order_type =
    int32_t;
  _order_type order;
  using _traj_id_type =
    int64_t;
  _traj_id_type traj_id;
  using _knots_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _knots_type knots;
  using _pts_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _pts_type pts;
  using _start_time_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _start_time_type start_time;

  // setters for named parameter idiom
  Type & set__order(
    const int32_t & _arg)
  {
    this->order = _arg;
    return *this;
  }
  Type & set__traj_id(
    const int64_t & _arg)
  {
    this->traj_id = _arg;
    return *this;
  }
  Type & set__knots(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->knots = _arg;
    return *this;
  }
  Type & set__pts(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->pts = _arg;
    return *this;
  }
  Type & set__start_time(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->start_time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_communication::msg::Bspline_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_communication::msg::Bspline_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_communication::msg::Bspline_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_communication::msg::Bspline_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::Bspline_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::Bspline_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::Bspline_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::Bspline_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_communication::msg::Bspline_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_communication::msg::Bspline_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_communication__msg__Bspline
    std::shared_ptr<robot_communication::msg::Bspline_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_communication__msg__Bspline
    std::shared_ptr<robot_communication::msg::Bspline_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Bspline_ & other) const
  {
    if (this->order != other.order) {
      return false;
    }
    if (this->traj_id != other.traj_id) {
      return false;
    }
    if (this->knots != other.knots) {
      return false;
    }
    if (this->pts != other.pts) {
      return false;
    }
    if (this->start_time != other.start_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const Bspline_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Bspline_

// alias to use template instance with default allocator
using Bspline =
  robot_communication::msg::Bspline_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__BSPLINE__STRUCT_HPP_
