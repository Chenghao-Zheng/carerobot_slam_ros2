// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__STRUCT_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_communication__msg__LocalizationInfoBroadcast __attribute__((deprecated))
#else
# define DEPRECATED__robot_communication__msg__LocalizationInfoBroadcast __declspec(deprecated)
#endif

namespace robot_communication
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LocalizationInfoBroadcast_
{
  using Type = LocalizationInfoBroadcast_<ContainerAllocator>;

  explicit LocalizationInfoBroadcast_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xposition = 0.0f;
      this->yposition = 0.0f;
      this->xspeed = 0.0f;
      this->yspeed = 0.0f;
      this->xaccel = 0.0f;
      this->yaccel = 0.0f;
      this->chassisangle = 0.0f;
      this->chassisgyro = 0.0f;
      this->timestamp = 0ul;
    }
  }

  explicit LocalizationInfoBroadcast_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xposition = 0.0f;
      this->yposition = 0.0f;
      this->xspeed = 0.0f;
      this->yspeed = 0.0f;
      this->xaccel = 0.0f;
      this->yaccel = 0.0f;
      this->chassisangle = 0.0f;
      this->chassisgyro = 0.0f;
      this->timestamp = 0ul;
    }
  }

  // field types and members
  using _xposition_type =
    float;
  _xposition_type xposition;
  using _yposition_type =
    float;
  _yposition_type yposition;
  using _xspeed_type =
    float;
  _xspeed_type xspeed;
  using _yspeed_type =
    float;
  _yspeed_type yspeed;
  using _xaccel_type =
    float;
  _xaccel_type xaccel;
  using _yaccel_type =
    float;
  _yaccel_type yaccel;
  using _chassisangle_type =
    float;
  _chassisangle_type chassisangle;
  using _chassisgyro_type =
    float;
  _chassisgyro_type chassisgyro;
  using _timestamp_type =
    uint32_t;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__xposition(
    const float & _arg)
  {
    this->xposition = _arg;
    return *this;
  }
  Type & set__yposition(
    const float & _arg)
  {
    this->yposition = _arg;
    return *this;
  }
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
  Type & set__xaccel(
    const float & _arg)
  {
    this->xaccel = _arg;
    return *this;
  }
  Type & set__yaccel(
    const float & _arg)
  {
    this->yaccel = _arg;
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

  // constant declarations

  // pointer types
  using RawPtr =
    robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_communication__msg__LocalizationInfoBroadcast
    std::shared_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_communication__msg__LocalizationInfoBroadcast
    std::shared_ptr<robot_communication::msg::LocalizationInfoBroadcast_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalizationInfoBroadcast_ & other) const
  {
    if (this->xposition != other.xposition) {
      return false;
    }
    if (this->yposition != other.yposition) {
      return false;
    }
    if (this->xspeed != other.xspeed) {
      return false;
    }
    if (this->yspeed != other.yspeed) {
      return false;
    }
    if (this->xaccel != other.xaccel) {
      return false;
    }
    if (this->yaccel != other.yaccel) {
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
    return true;
  }
  bool operator!=(const LocalizationInfoBroadcast_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalizationInfoBroadcast_

// alias to use template instance with default allocator
using LocalizationInfoBroadcast =
  robot_communication::msg::LocalizationInfoBroadcast_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__STRUCT_HPP_
