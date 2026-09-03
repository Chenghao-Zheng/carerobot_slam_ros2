// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robot_communication:msg/SensorData.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/sensor_data__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robot_communication/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robot_communication/msg/detail/sensor_data__struct.h"
#include "robot_communication/msg/detail/sensor_data__functions.h"
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


using _SensorData__ros_msg_type = robot_communication__msg__SensorData;

static bool _SensorData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SensorData__ros_msg_type * ros_message = static_cast<const _SensorData__ros_msg_type *>(untyped_ros_message);
  // Field name: local_x_veloc
  {
    cdr << ros_message->local_x_veloc;
  }

  // Field name: local_y_veloc
  {
    cdr << ros_message->local_y_veloc;
  }

  // Field name: local_x_accel
  {
    cdr << ros_message->local_x_accel;
  }

  // Field name: local_y_accel
  {
    cdr << ros_message->local_y_accel;
  }

  // Field name: yaw
  {
    cdr << ros_message->yaw;
  }

  // Field name: timestamp_10us
  {
    cdr << ros_message->timestamp_10us;
  }

  return true;
}

static bool _SensorData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SensorData__ros_msg_type * ros_message = static_cast<_SensorData__ros_msg_type *>(untyped_ros_message);
  // Field name: local_x_veloc
  {
    cdr >> ros_message->local_x_veloc;
  }

  // Field name: local_y_veloc
  {
    cdr >> ros_message->local_y_veloc;
  }

  // Field name: local_x_accel
  {
    cdr >> ros_message->local_x_accel;
  }

  // Field name: local_y_accel
  {
    cdr >> ros_message->local_y_accel;
  }

  // Field name: yaw
  {
    cdr >> ros_message->yaw;
  }

  // Field name: timestamp_10us
  {
    cdr >> ros_message->timestamp_10us;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_communication
size_t get_serialized_size_robot_communication__msg__SensorData(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SensorData__ros_msg_type * ros_message = static_cast<const _SensorData__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name local_x_veloc
  {
    size_t item_size = sizeof(ros_message->local_x_veloc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_y_veloc
  {
    size_t item_size = sizeof(ros_message->local_y_veloc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_x_accel
  {
    size_t item_size = sizeof(ros_message->local_x_accel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name local_y_accel
  {
    size_t item_size = sizeof(ros_message->local_y_accel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name yaw
  {
    size_t item_size = sizeof(ros_message->yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name timestamp_10us
  {
    size_t item_size = sizeof(ros_message->timestamp_10us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SensorData__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robot_communication__msg__SensorData(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_communication
size_t max_serialized_size_robot_communication__msg__SensorData(
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

  // member: local_x_veloc
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: local_y_veloc
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: local_x_accel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: local_y_accel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: yaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: timestamp_10us
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
    using DataType = robot_communication__msg__SensorData;
    is_plain =
      (
      offsetof(DataType, timestamp_10us) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SensorData__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robot_communication__msg__SensorData(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SensorData = {
  "robot_communication::msg",
  "SensorData",
  _SensorData__cdr_serialize,
  _SensorData__cdr_deserialize,
  _SensorData__get_serialized_size,
  _SensorData__max_serialized_size
};

static rosidl_message_type_support_t _SensorData__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SensorData,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, msg, SensorData)() {
  return &_SensorData__type_support;
}

#if defined(__cplusplus)
}
#endif
