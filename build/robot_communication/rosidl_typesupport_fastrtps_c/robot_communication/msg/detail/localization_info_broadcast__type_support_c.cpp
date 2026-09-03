// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/localization_info_broadcast__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robot_communication/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robot_communication/msg/detail/localization_info_broadcast__struct.h"
#include "robot_communication/msg/detail/localization_info_broadcast__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _LocalizationInfoBroadcast__ros_msg_type = robot_communication__msg__LocalizationInfoBroadcast;

static bool _LocalizationInfoBroadcast__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _LocalizationInfoBroadcast__ros_msg_type * ros_message = static_cast<const _LocalizationInfoBroadcast__ros_msg_type *>(untyped_ros_message);
  // Field name: xposition
  {
    cdr << ros_message->xposition;
  }

  // Field name: yposition
  {
    cdr << ros_message->yposition;
  }

  // Field name: xspeed
  {
    cdr << ros_message->xspeed;
  }

  // Field name: yspeed
  {
    cdr << ros_message->yspeed;
  }

  // Field name: xaccel
  {
    cdr << ros_message->xaccel;
  }

  // Field name: yaccel
  {
    cdr << ros_message->yaccel;
  }

  // Field name: chassisangle
  {
    cdr << ros_message->chassisangle;
  }

  // Field name: chassisgyro
  {
    cdr << ros_message->chassisgyro;
  }

  // Field name: timestamp
  {
    cdr << ros_message->timestamp;
  }

  return true;
}

static bool _LocalizationInfoBroadcast__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _LocalizationInfoBroadcast__ros_msg_type * ros_message = static_cast<_LocalizationInfoBroadcast__ros_msg_type *>(untyped_ros_message);
  // Field name: xposition
  {
    cdr >> ros_message->xposition;
  }

  // Field name: yposition
  {
    cdr >> ros_message->yposition;
  }

  // Field name: xspeed
  {
    cdr >> ros_message->xspeed;
  }

  // Field name: yspeed
  {
    cdr >> ros_message->yspeed;
  }

  // Field name: xaccel
  {
    cdr >> ros_message->xaccel;
  }

  // Field name: yaccel
  {
    cdr >> ros_message->yaccel;
  }

  // Field name: chassisangle
  {
    cdr >> ros_message->chassisangle;
  }

  // Field name: chassisgyro
  {
    cdr >> ros_message->chassisgyro;
  }

  // Field name: timestamp
  {
    cdr >> ros_message->timestamp;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_communication
size_t get_serialized_size_robot_communication__msg__LocalizationInfoBroadcast(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _LocalizationInfoBroadcast__ros_msg_type * ros_message = static_cast<const _LocalizationInfoBroadcast__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name xposition
  {
    size_t item_size = sizeof(ros_message->xposition);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name yposition
  {
    size_t item_size = sizeof(ros_message->yposition);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name xspeed
  {
    size_t item_size = sizeof(ros_message->xspeed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name yspeed
  {
    size_t item_size = sizeof(ros_message->yspeed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name xaccel
  {
    size_t item_size = sizeof(ros_message->xaccel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name yaccel
  {
    size_t item_size = sizeof(ros_message->yaccel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassisangle
  {
    size_t item_size = sizeof(ros_message->chassisangle);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name chassisgyro
  {
    size_t item_size = sizeof(ros_message->chassisgyro);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name timestamp
  {
    size_t item_size = sizeof(ros_message->timestamp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _LocalizationInfoBroadcast__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robot_communication__msg__LocalizationInfoBroadcast(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_communication
size_t max_serialized_size_robot_communication__msg__LocalizationInfoBroadcast(
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

  // member: xposition
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: yposition
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: xspeed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: yspeed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: xaccel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: yaccel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: chassisangle
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: chassisgyro
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: timestamp
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_communication__msg__LocalizationInfoBroadcast;
    is_plain =
      (
      offsetof(DataType, timestamp) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _LocalizationInfoBroadcast__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robot_communication__msg__LocalizationInfoBroadcast(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_LocalizationInfoBroadcast = {
  "robot_communication::msg",
  "LocalizationInfoBroadcast",
  _LocalizationInfoBroadcast__cdr_serialize,
  _LocalizationInfoBroadcast__cdr_deserialize,
  _LocalizationInfoBroadcast__get_serialized_size,
  _LocalizationInfoBroadcast__max_serialized_size
};

static rosidl_message_type_support_t _LocalizationInfoBroadcast__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_LocalizationInfoBroadcast,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, msg, LocalizationInfoBroadcast)() {
  return &_LocalizationInfoBroadcast__type_support;
}

#if defined(__cplusplus)
}
#endif
