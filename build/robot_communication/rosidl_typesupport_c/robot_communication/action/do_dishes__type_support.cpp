// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from robot_communication:action/DoDishes.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "robot_communication/action/detail/do_dishes__struct.h"
#include "robot_communication/action/detail/do_dishes__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_Goal_type_support_ids_t;

static const _DoDishes_Goal_type_support_ids_t _DoDishes_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_Goal_type_support_symbol_names_t _DoDishes_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_Goal)),
  }
};

typedef struct _DoDishes_Goal_type_support_data_t
{
  void * data[2];
} _DoDishes_Goal_type_support_data_t;

static _DoDishes_Goal_type_support_data_t _DoDishes_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_Goal_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_Goal)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_Result_type_support_ids_t;

static const _DoDishes_Result_type_support_ids_t _DoDishes_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_Result_type_support_symbol_names_t _DoDishes_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_Result)),
  }
};

typedef struct _DoDishes_Result_type_support_data_t
{
  void * data[2];
} _DoDishes_Result_type_support_data_t;

static _DoDishes_Result_type_support_data_t _DoDishes_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_Result_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_Result_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_Result_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_Result)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_Feedback_type_support_ids_t;

static const _DoDishes_Feedback_type_support_ids_t _DoDishes_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_Feedback_type_support_symbol_names_t _DoDishes_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_Feedback)),
  }
};

typedef struct _DoDishes_Feedback_type_support_data_t
{
  void * data[2];
} _DoDishes_Feedback_type_support_data_t;

static _DoDishes_Feedback_type_support_data_t _DoDishes_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_Feedback_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_Feedback)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_SendGoal_Request_type_support_ids_t;

static const _DoDishes_SendGoal_Request_type_support_ids_t _DoDishes_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_SendGoal_Request_type_support_symbol_names_t _DoDishes_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_SendGoal_Request)),
  }
};

typedef struct _DoDishes_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _DoDishes_SendGoal_Request_type_support_data_t;

static _DoDishes_SendGoal_Request_type_support_data_t _DoDishes_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_SendGoal_Request_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_SendGoal_Request)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_SendGoal_Response_type_support_ids_t;

static const _DoDishes_SendGoal_Response_type_support_ids_t _DoDishes_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_SendGoal_Response_type_support_symbol_names_t _DoDishes_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_SendGoal_Response)),
  }
};

typedef struct _DoDishes_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _DoDishes_SendGoal_Response_type_support_data_t;

static _DoDishes_SendGoal_Response_type_support_data_t _DoDishes_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_SendGoal_Response_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_SendGoal_Response)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_SendGoal_type_support_ids_t;

static const _DoDishes_SendGoal_type_support_ids_t _DoDishes_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_SendGoal_type_support_symbol_names_t _DoDishes_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_SendGoal)),
  }
};

typedef struct _DoDishes_SendGoal_type_support_data_t
{
  void * data[2];
} _DoDishes_SendGoal_type_support_data_t;

static _DoDishes_SendGoal_type_support_data_t _DoDishes_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_SendGoal_service_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t DoDishes_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_SendGoal)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_GetResult_Request_type_support_ids_t;

static const _DoDishes_GetResult_Request_type_support_ids_t _DoDishes_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_GetResult_Request_type_support_symbol_names_t _DoDishes_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_GetResult_Request)),
  }
};

typedef struct _DoDishes_GetResult_Request_type_support_data_t
{
  void * data[2];
} _DoDishes_GetResult_Request_type_support_data_t;

static _DoDishes_GetResult_Request_type_support_data_t _DoDishes_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_GetResult_Request_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_GetResult_Request)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_GetResult_Response_type_support_ids_t;

static const _DoDishes_GetResult_Response_type_support_ids_t _DoDishes_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_GetResult_Response_type_support_symbol_names_t _DoDishes_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_GetResult_Response)),
  }
};

typedef struct _DoDishes_GetResult_Response_type_support_data_t
{
  void * data[2];
} _DoDishes_GetResult_Response_type_support_data_t;

static _DoDishes_GetResult_Response_type_support_data_t _DoDishes_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_GetResult_Response_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_GetResult_Response)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_GetResult_type_support_ids_t;

static const _DoDishes_GetResult_type_support_ids_t _DoDishes_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_GetResult_type_support_symbol_names_t _DoDishes_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_GetResult)),
  }
};

typedef struct _DoDishes_GetResult_type_support_data_t
{
  void * data[2];
} _DoDishes_GetResult_type_support_data_t;

static _DoDishes_GetResult_type_support_data_t _DoDishes_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_GetResult_service_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t DoDishes_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_GetResult)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_communication
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _DoDishes_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DoDishes_FeedbackMessage_type_support_ids_t;

static const _DoDishes_FeedbackMessage_type_support_ids_t _DoDishes_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _DoDishes_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DoDishes_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DoDishes_FeedbackMessage_type_support_symbol_names_t _DoDishes_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_communication, action, DoDishes_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_communication, action, DoDishes_FeedbackMessage)),
  }
};

typedef struct _DoDishes_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _DoDishes_FeedbackMessage_type_support_data_t;

static _DoDishes_FeedbackMessage_type_support_data_t _DoDishes_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DoDishes_FeedbackMessage_message_typesupport_map = {
  2,
  "robot_communication",
  &_DoDishes_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_DoDishes_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_DoDishes_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DoDishes_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DoDishes_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace robot_communication

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_communication, action, DoDishes_FeedbackMessage)() {
  return &::robot_communication::action::rosidl_typesupport_c::DoDishes_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "robot_communication/action/do_dishes.h"
// already included above
// #include "robot_communication/action/detail/do_dishes__type_support.h"

static rosidl_action_type_support_t _robot_communication__action__DoDishes__typesupport_c;

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, robot_communication, action, DoDishes)()
{
  // Thread-safe by always writing the same values to the static struct
  _robot_communication__action__DoDishes__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, robot_communication, action, DoDishes_SendGoal)();
  _robot_communication__action__DoDishes__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, robot_communication, action, DoDishes_GetResult)();
  _robot_communication__action__DoDishes__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _robot_communication__action__DoDishes__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, robot_communication, action, DoDishes_FeedbackMessage)();
  _robot_communication__action__DoDishes__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_robot_communication__action__DoDishes__typesupport_c;
}

#ifdef __cplusplus
}
#endif
