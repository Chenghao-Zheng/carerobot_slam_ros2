// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_communication:msg/SensorData.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__STRUCT_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_communication__msg__SensorData __attribute__((deprecated))
#else
# define DEPRECATED__robot_communication__msg__SensorData __declspec(deprecated)
#endif

namespace robot_communication
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorData_
{
  using Type = SensorData_<ContainerAllocator>;

  explicit SensorData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->local_x_veloc = 0.0f;
      this->local_y_veloc = 0.0f;
      this->local_x_accel = 0.0f;
      this->local_y_accel = 0.0f;
      this->yaw = 0.0f;
      this->timestamp_10us = 0ul;
    }
  }

  explicit SensorData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->local_x_veloc = 0.0f;
      this->local_y_veloc = 0.0f;
      this->local_x_accel = 0.0f;
      this->local_y_accel = 0.0f;
      this->yaw = 0.0f;
      this->timestamp_10us = 0ul;
    }
  }

  // field types and members
  using _local_x_veloc_type =
    float;
  _local_x_veloc_type local_x_veloc;
  using _local_y_veloc_type =
    float;
  _local_y_veloc_type local_y_veloc;
  using _local_x_accel_type =
    float;
  _local_x_accel_type local_x_accel;
  using _local_y_accel_type =
    float;
  _local_y_accel_type local_y_accel;
  using _yaw_type =
    float;
  _yaw_type yaw;
  using _timestamp_10us_type =
    uint32_t;
  _timestamp_10us_type timestamp_10us;

  // setters for named parameter idiom
  Type & set__local_x_veloc(
    const float & _arg)
  {
    this->local_x_veloc = _arg;
    return *this;
  }
  Type & set__local_y_veloc(
    const float & _arg)
  {
    this->local_y_veloc = _arg;
    return *this;
  }
  Type & set__local_x_accel(
    const float & _arg)
  {
    this->local_x_accel = _arg;
    return *this;
  }
  Type & set__local_y_accel(
    const float & _arg)
  {
    this->local_y_accel = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__timestamp_10us(
    const uint32_t & _arg)
  {
    this->timestamp_10us = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_communication::msg::SensorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_communication::msg::SensorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_communication::msg::SensorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_communication::msg::SensorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::SensorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::SensorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::SensorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::SensorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_communication::msg::SensorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_communication::msg::SensorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_communication__msg__SensorData
    std::shared_ptr<robot_communication::msg::SensorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_communication__msg__SensorData
    std::shared_ptr<robot_communication::msg::SensorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorData_ & other) const
  {
    if (this->local_x_veloc != other.local_x_veloc) {
      return false;
    }
    if (this->local_y_veloc != other.local_y_veloc) {
      return false;
    }
    if (this->local_x_accel != other.local_x_accel) {
      return false;
    }
    if (this->local_y_accel != other.local_y_accel) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->timestamp_10us != other.timestamp_10us) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorData_

// alias to use template instance with default allocator
using SensorData =
  robot_communication::msg::SensorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__SENSOR_DATA__STRUCT_HPP_
