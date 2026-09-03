// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_communication:msg/Goal.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__STRUCT_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_communication__msg__Goal __attribute__((deprecated))
#else
# define DEPRECATED__robot_communication__msg__Goal __declspec(deprecated)
#endif

namespace robot_communication
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Goal_
{
  using Type = Goal_<ContainerAllocator>;

  explicit Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->position_x = 0.0f;
      this->position_y = 0.0f;
      this->position_yaw = 0.0f;
    }
  }

  explicit Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->position_x = 0.0f;
      this->position_y = 0.0f;
      this->position_yaw = 0.0f;
    }
  }

  // field types and members
  using _position_x_type =
    float;
  _position_x_type position_x;
  using _position_y_type =
    float;
  _position_y_type position_y;
  using _position_yaw_type =
    float;
  _position_yaw_type position_yaw;

  // setters for named parameter idiom
  Type & set__position_x(
    const float & _arg)
  {
    this->position_x = _arg;
    return *this;
  }
  Type & set__position_y(
    const float & _arg)
  {
    this->position_y = _arg;
    return *this;
  }
  Type & set__position_yaw(
    const float & _arg)
  {
    this->position_yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_communication::msg::Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_communication::msg::Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_communication::msg::Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_communication::msg::Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_communication::msg::Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_communication::msg::Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_communication__msg__Goal
    std::shared_ptr<robot_communication::msg::Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_communication__msg__Goal
    std::shared_ptr<robot_communication::msg::Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Goal_ & other) const
  {
    if (this->position_x != other.position_x) {
      return false;
    }
    if (this->position_y != other.position_y) {
      return false;
    }
    if (this->position_yaw != other.position_yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Goal_

// alias to use template instance with default allocator
using Goal =
  robot_communication::msg::Goal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__GOAL__STRUCT_HPP_
