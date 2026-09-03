// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_communication:msg/EsdfMap.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__STRUCT_HPP_
#define ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_communication__msg__EsdfMap __attribute__((deprecated))
#else
# define DEPRECATED__robot_communication__msg__EsdfMap __declspec(deprecated)
#endif

namespace robot_communication
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EsdfMap_
{
  using Type = EsdfMap_<ContainerAllocator>;

  explicit EsdfMap_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->origin_x = 0.0f;
      this->origin_y = 0.0f;
      this->resolution = 0.0f;
      this->width = 0.0f;
      this->height = 0.0f;
    }
  }

  explicit EsdfMap_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->origin_x = 0.0f;
      this->origin_y = 0.0f;
      this->resolution = 0.0f;
      this->width = 0.0f;
      this->height = 0.0f;
    }
  }

  // field types and members
  using _origin_x_type =
    float;
  _origin_x_type origin_x;
  using _origin_y_type =
    float;
  _origin_y_type origin_y;
  using _resolution_type =
    float;
  _resolution_type resolution;
  using _width_type =
    float;
  _width_type width;
  using _height_type =
    float;
  _height_type height;
  using _data_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__origin_x(
    const float & _arg)
  {
    this->origin_x = _arg;
    return *this;
  }
  Type & set__origin_y(
    const float & _arg)
  {
    this->origin_y = _arg;
    return *this;
  }
  Type & set__resolution(
    const float & _arg)
  {
    this->resolution = _arg;
    return *this;
  }
  Type & set__width(
    const float & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const float & _arg)
  {
    this->height = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_communication::msg::EsdfMap_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_communication::msg::EsdfMap_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::EsdfMap_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_communication::msg::EsdfMap_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_communication__msg__EsdfMap
    std::shared_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_communication__msg__EsdfMap
    std::shared_ptr<robot_communication::msg::EsdfMap_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EsdfMap_ & other) const
  {
    if (this->origin_x != other.origin_x) {
      return false;
    }
    if (this->origin_y != other.origin_y) {
      return false;
    }
    if (this->resolution != other.resolution) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const EsdfMap_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EsdfMap_

// alias to use template instance with default allocator
using EsdfMap =
  robot_communication::msg::EsdfMap_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__ESDF_MAP__STRUCT_HPP_
