// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robot_communication/msg/detail/chassis_control__rosidl_typesupport_introspection_c.h"
#include "robot_communication/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robot_communication/msg/detail/chassis_control__functions.h"
#include "robot_communication/msg/detail/chassis_control__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_communication__msg__ChassisControl__init(message_memory);
}

void robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_fini_function(void * message_memory)
{
  robot_communication__msg__ChassisControl__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_member_array[6] = {
  {
    "xspeed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__ChassisControl, xspeed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yspeed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__ChassisControl, yspeed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "chassisangle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__ChassisControl, chassisangle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "chassisgyro",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__ChassisControl, chassisgyro),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__ChassisControl, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "globalorlocal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_communication__msg__ChassisControl, globalorlocal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_members = {
  "robot_communication__msg",  // message namespace
  "ChassisControl",  // message name
  6,  // number of fields
  sizeof(robot_communication__msg__ChassisControl),
  robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_member_array,  // message members
  robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_init_function,  // function to initialize message memory (memory has to be allocated)
  robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_type_support_handle = {
  0,
  &robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_communication
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, msg, ChassisControl)() {
  if (!robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_type_support_handle.typesupport_identifier) {
    robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robot_communication__msg__ChassisControl__rosidl_typesupport_introspection_c__ChassisControl_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
