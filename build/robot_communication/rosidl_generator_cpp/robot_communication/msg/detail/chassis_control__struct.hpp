// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__STRUCT_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_communication__msg__ChassisControl __attribute__((deprecated))
#else
# define DEPRECATED__robot_communication__msg__ChassisControl __declspec(deprecated)
#endif

namespace robot_communication
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ChassisControl_
{
  using Type = ChassisControl_<ContainerAllocator>;

  explicit ChassisControl_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xspeed = 0.0f;
      this->yspeed = 0.0f;
      this->chassisangle = 0.0f;
      this->chassisgyro = 0.0f;
      this->timestamp = 0ul;
      this->globalorlocal = false;
    }
  }

  explicit ChassisControl_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xspeed = 0.0f;
      this->yspeed = 0.0f;
      this->chassisangle = 0.0f;
      this->chassisgyro = 0.0f;
      this->timestamp = 0ul;
      this->globalorlocal = false;
    }
  }

  // field types and members
  using _xspeed_type =
    float;
  _xspeed_type xspeed;
  using _yspeed_type =
    float;
  _yspeed_type yspeed;
  using _chassisangle_type =
    float;
  _chassisangle_type chassisangle;
  using _chassisgyro_type =
    float;
  _chassisgyro_type chassisgyro;
  using _timestamp_type =
    uint32_t;
  _timestamp_type timestamp;
  using _globalorlocal_type =
    bool;
  _globalorlocal_type globalorlocal;

  // setters for named parameter idiom
  Type & set__xspeed(
    const float & _arg)
  {
    this->xspeed = _arg;
    return *this;
  }
  Type & set__yspeed(
    const float & _arg)
  {
    this->yspeed = _arg;
    return *this;
  }
  Type & set__chassisangle(
    const float & _arg)
  {
    this->chassisangle = _arg;
    return *this;
  }
  Type & set__chassisgyro(
    const float & _arg)
  {
    this->chassisgyro = _arg;
    return *this;
  }
  Type & set__timestamp(
    const uint32_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__globalorlocal(
    const bool & _arg)
  {
    this->globalorlocal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_communication::msg::ChassisControl_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_communication::msg::ChassisControl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::ChassisControl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::ChassisControl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_communication__msg__ChassisControl
    std::shared_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_communication__msg__ChassisControl
    std::shared_ptr<robot_communication::msg::ChassisControl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChassisControl_ & other) const
  {
    if (this->xspeed != other.xspeed) {
      return false;
    }
    if (this->yspeed != other.yspeed) {
      return false;
    }
    if (this->chassisangle != other.chassisangle) {
      return false;
    }
    if (this->chassisgyro != other.chassisgyro) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->globalorlocal != other.globalorlocal) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChassisControl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChassisControl_

// alias to use template instance with default allocator
using ChassisControl =
  robot_communication::msg::ChassisControl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__CHASSIS_CONTROL__STRUCT_HPP_
