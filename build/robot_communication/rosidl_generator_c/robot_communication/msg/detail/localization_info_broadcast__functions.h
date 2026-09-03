// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__FUNCTIONS_H_
#define ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "robot_communication/msg/rosidl_generator_c__visibility_control.h"

#include "robot_communication/msg/detail/localization_info_broadcast__struct.h"

/// Initialize msg/LocalizationInfoBroadcast message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__msg__LocalizationInfoBroadcast
 * )) before or use
 * robot_communication__msg__LocalizationInfoBroadcast__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__msg__LocalizationInfoBroadcast__init(robot_communication__msg__LocalizationInfoBroadcast * msg);

/// Finalize msg/LocalizationInfoBroadcast message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__msg__LocalizationInfoBroadcast__fini(robot_communication__msg__LocalizationInfoBroadcast * msg);

/// Create msg/LocalizationInfoBroadcast message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__msg__LocalizationInfoBroadcast__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__msg__LocalizationInfoBroadcast *
robot_communication__msg__LocalizationInfoBroadcast__create();

/// Destroy msg/LocalizationInfoBroadcast message.
/**
 * It calls
 * robot_communication__msg__LocalizationInfoBroadcast__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__msg__LocalizationInfoBroadcast__destroy(robot_communication__msg__LocalizationInfoBroadcast * msg);

/// Check for msg/LocalizationInfoBroadcast message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__msg__LocalizationInfoBroadcast__are_equal(const robot_communication__msg__LocalizationInfoBroadcast * lhs, const robot_communication__msg__LocalizationInfoBroadcast * rhs);

/// Copy a msg/LocalizationInfoBroadcast message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__msg__LocalizationInfoBroadcast__copy(
  const robot_communication__msg__LocalizationInfoBroadcast * input,
  robot_communication__msg__LocalizationInfoBroadcast * output);

/// Initialize array of msg/LocalizationInfoBroadcast messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__msg__LocalizationInfoBroadcast__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__msg__LocalizationInfoBroadcast__Sequence__init(robot_communication__msg__LocalizationInfoBroadcast__Sequence * array, size_t size);

/// Finalize array of msg/LocalizationInfoBroadcast messages.
/**
 * It calls
 * robot_communication__msg__LocalizationInfoBroadcast__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__msg__LocalizationInfoBroadcast__Sequence__fini(robot_communication__msg__LocalizationInfoBroadcast__Sequence * array);

/// Create array of msg/LocalizationInfoBroadcast messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__msg__LocalizationInfoBroadcast__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__msg__LocalizationInfoBroadcast__Sequence *
robot_communication__msg__LocalizationInfoBroadcast__Sequence__create(size_t size);

/// Destroy array of msg/LocalizationInfoBroadcast messages.
/**
 * It calls
 * robot_communication__msg__LocalizationInfoBroadcast__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__msg__LocalizationInfoBroadcast__Sequence__destroy(robot_communication__msg__LocalizationInfoBroadcast__Sequence * array);

/// Check for msg/LocalizationInfoBroadcast message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__msg__LocalizationInfoBroadcast__Sequence__are_equal(const robot_communication__msg__LocalizationInfoBroadcast__Sequence * lhs, const robot_communication__msg__LocalizationInfoBroadcast__Sequence * rhs);

/// Copy an array of msg/LocalizationInfoBroadcast messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__msg__LocalizationInfoBroadcast__Sequence__copy(
  const robot_communication__msg__LocalizationInfoBroadcast__Sequence * input,
  robot_communication__msg__LocalizationInfoBroadcast__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__MSG__DETAIL__LOCALIZATION_INFO_BROADCAST__FUNCTIONS_H_
