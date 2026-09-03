// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robot_communication:msg/Bspline.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robot_communication/msg/detail/bspline__rosidl_typesupport_introspection_c.h"
#include "robot_communication/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robot_communication/msg/detail/bspline__functions.h"
#include "robot_communication/msg/detail/bspline__struct.h"


// Include directives for member types
// Member `knots`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `pts`
#include "geometry_msgs/msg/point.h"
// Member `pts`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `start_time`
#include "builtin_interfaces/msg/time.h"
// Member `start_time`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_communication__msg__Bspline__init(message_memory);
}

void robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_fini_function(void * message_memory)
{
  robot_communication__msg__Bspline__fini(message_memory);
}

size_t robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__size_function__Bspline__knots(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_const_function__Bspline__knots(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_function__Bspline__knots(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__fetch_function__Bspline__knots(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_const_function__Bspline__knots(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__assign_function__Bspline__knots(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_function__Bspline__knots(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__resize_function__Bspline__knots(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__size_function__Bspline__pts(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_const_function__Bspline__pts(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_function__Bspline__pts(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__fetch_function__Bspline__pts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_const_function__Bspline__pts(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__assign_function__Bspline__pts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_function__Bspline__pts(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__resize_function__Bspline__pts(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_member_array[5] = {
  {
    "order",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__Bspline, order),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "traj_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__Bspline, traj_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "knots",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__Bspline, knots),  // bytes offset in struct
    NULL,  // default value
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__size_function__Bspline__knots,  // size() function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_const_function__Bspline__knots,  // get_const(index) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_function__Bspline__knots,  // get(index) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__fetch_function__Bspline__knots,  // fetch(index, &value) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__assign_function__Bspline__knots,  // assign(index, value) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__resize_function__Bspline__knots  // resize(index) function pointer
  },
  {
    "pts",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__Bspline, pts),  // bytes offset in struct
    NULL,  // default value
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__size_function__Bspline__pts,  // size() function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_const_function__Bspline__pts,  // get_const(index) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__get_function__Bspline__pts,  // get(index) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__fetch_function__Bspline__pts,  // fetch(index, &value) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__assign_function__Bspline__pts,  // assign(index, value) function pointer
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__resize_function__Bspline__pts  // resize(index) function pointer
  },
  {
    "start_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__Bspline, start_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_members = {
  "robot_communication__msg",  // message namespace
  "Bspline",  // message name
  5,  // number of fields
  sizeof(robot_communication__msg__Bspline),
  robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_member_array,  // message members
  robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_init_function,  // function to initialize message memory (memory has to be allocated)
  robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_type_support_handle = {
  0,
  &robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_communication
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, msg, Bspline)() {
  robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_type_support_handle.typesupport_identifier) {
    robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robot_communication__msg__Bspline__rosidl_typesupport_introspection_c__Bspline_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
