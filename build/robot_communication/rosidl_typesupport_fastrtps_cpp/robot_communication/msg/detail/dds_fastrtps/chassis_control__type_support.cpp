// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/chassis_control__rosidl_typesupport_fastrtps_cpp.hpp"
#include "robot_communication/msg/detail/chassis_control__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace robot_communication
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_communication
cdr_serialize(
  const robot_communication::msg::ChassisControl & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: xspeed
  cdr << ros_message.xspeed;
  // Member: yspeed
  cdr << ros_message.yspeed;
  // Member: chassisangle
  cdr << ros_message.chassisangle;
  // Member: chassisgyro
  cdr << ros_message.chassisgyro;
  // Member: timestamp
  cdr << ros_message.timestamp;
  // Member: globalorlocal
  cdr << (ros_message.globalorlocal ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_communication
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  robot_communication::msg::ChassisControl & ros_message)
{
  // Member: xspeed
  cdr >> ros_message.xspeed;

  // Member: yspeed
  cdr >> ros_message.yspeed;

  // Member: chassisangle
  cdr >> ros_message.chassisangle;

  // Member: chassisgyro
  cdr >> ros_message.chassisgyro;

  // Member: timestamp
  cdr >> ros_message.timestamp;

  // Member: globalorlocal
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.globalorlocal = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_communication
get_serialized_size(
  const robot_communication::msg::ChassisControl & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: xspeed
  {
    size_t item_size = sizeof(ros_message.xspeed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: yspeed
  {
    size_t item_size = sizeof(ros_message.yspeed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassisangle
  {
    size_t item_size = sizeof(ros_message.chassisangle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: chassisgyro
  {
    size_t item_size = sizeof(ros_message.chassisgyro);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: timestamp
  {
    size_t item_size = sizeof(ros_message.timestamp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: globalorlocal
  {
    size_t item_size = sizeof(ros_message.globalorlocal);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_communication
max_serialized_size_ChassisControl(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: xspeed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: yspeed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: chassisangle
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: chassisgyro
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: timestamp
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: globalorlocal
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_communication::msg::ChassisControl;
    is_plain =
      (
      offsetof(DataType, globalorlocal) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ChassisControl__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const robot_communication::msg::ChassisControl *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ChassisControl__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<robot_communication::msg::ChassisControl *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ChassisControl__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const robot_communication::msg::ChassisControl *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ChassisControl__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ChassisControl(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ChassisControl__callbacks = {
  "robot_communication::msg",
  "ChassisControl",
  _ChassisControl__cdr_serialize,
  _ChassisControl__cdr_deserialize,
  _ChassisControl__get_serialized_size,
  _ChassisControl__max_serialized_size
};

static rosidl_message_type_support_t _ChassisControl__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ChassisControl__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace robot_communication

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_robot_communication
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_communication::msg::ChassisControl>()
{
  return &robot_communication::msg::typesupport_fastrtps_cpp::_ChassisControl__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_communication, msg, ChassisControl)() {
  return &robot_communication::msg::typesupport_fastrtps_cpp::_ChassisControl__handle;
}

#ifdef __cplusplus
}
#endif
