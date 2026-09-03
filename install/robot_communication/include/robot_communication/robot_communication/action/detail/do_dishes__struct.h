// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_communication:action/DoDishes.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__STRUCT_H_
#define ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_Goal
{
  /// Specify which dishwasher we want to use
  uint32_t dishwasher_id;
} robot_communication__action__DoDishes_Goal;

// Struct for a sequence of robot_communication__action__DoDishes_Goal.
typedef struct robot_communication__action__DoDishes_Goal__Sequence
{
  robot_communication__action__DoDishes_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_Result
{
  uint32_t total_dishes_cleaned;
} robot_communication__action__DoDishes_Result;

// Struct for a sequence of robot_communication__action__DoDishes_Result.
typedef struct robot_communication__action__DoDishes_Result__Sequence
{
  robot_communication__action__DoDishes_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_Feedback
{
  float percent_complete;
} robot_communication__action__DoDishes_Feedback;

// Struct for a sequence of robot_communication__action__DoDishes_Feedback.
typedef struct robot_communication__action__DoDishes_Feedback__Sequence
{
  robot_communication__action__DoDishes_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "robot_communication/action/detail/do_dishes__struct.h"

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_communication__action__DoDishes_Goal goal;
} robot_communication__action__DoDishes_SendGoal_Request;

// Struct for a sequence of robot_communication__action__DoDishes_SendGoal_Request.
typedef struct robot_communication__action__DoDishes_SendGoal_Request__Sequence
{
  robot_communication__action__DoDishes_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} robot_communication__action__DoDishes_SendGoal_Response;

// Struct for a sequence of robot_communication__action__DoDishes_SendGoal_Response.
typedef struct robot_communication__action__DoDishes_SendGoal_Response__Sequence
{
  robot_communication__action__DoDishes_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} robot_communication__action__DoDishes_GetResult_Request;

// Struct for a sequence of robot_communication__action__DoDishes_GetResult_Request.
typedef struct robot_communication__action__DoDishes_GetResult_Request__Sequence
{
  robot_communication__action__DoDishes_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_GetResult_Response
{
  int8_t status;
  robot_communication__action__DoDishes_Result result;
} robot_communication__action__DoDishes_GetResult_Response;

// Struct for a sequence of robot_communication__action__DoDishes_GetResult_Response.
typedef struct robot_communication__action__DoDishes_GetResult_Response__Sequence
{
  robot_communication__action__DoDishes_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "robot_communication/action/detail/do_dishes__struct.h"

/// Struct defined in action/DoDishes in the package robot_communication.
typedef struct robot_communication__action__DoDishes_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_communication__action__DoDishes_Feedback feedback;
} robot_communication__action__DoDishes_FeedbackMessage;

// Struct for a sequence of robot_communication__action__DoDishes_FeedbackMessage.
typedef struct robot_communication__action__DoDishes_FeedbackMessage__Sequence
{
  robot_communication__action__DoDishes_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_communication__action__DoDishes_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__STRUCT_H_
