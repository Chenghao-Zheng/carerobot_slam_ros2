// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from robot_communication:action/DoDishes.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__FUNCTIONS_H_
#define ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "robot_communication/msg/rosidl_generator_c__visibility_control.h"

#include "robot_communication/action/detail/do_dishes__struct.h"

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_Goal
 * )) before or use
 * robot_communication__action__DoDishes_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Goal__init(robot_communication__action__DoDishes_Goal * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Goal__fini(robot_communication__action__DoDishes_Goal * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_Goal *
robot_communication__action__DoDishes_Goal__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Goal__destroy(robot_communication__action__DoDishes_Goal * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Goal__are_equal(const robot_communication__action__DoDishes_Goal * lhs, const robot_communication__action__DoDishes_Goal * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_Goal__copy(
  const robot_communication__action__DoDishes_Goal * input,
  robot_communication__action__DoDishes_Goal * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Goal__Sequence__init(robot_communication__action__DoDishes_Goal__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Goal__Sequence__fini(robot_communication__action__DoDishes_Goal__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_Goal__Sequence *
robot_communication__action__DoDishes_Goal__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Goal__Sequence__destroy(robot_communication__action__DoDishes_Goal__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Goal__Sequence__are_equal(const robot_communication__action__DoDishes_Goal__Sequence * lhs, const robot_communication__action__DoDishes_Goal__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_Goal__Sequence__copy(
  const robot_communication__action__DoDishes_Goal__Sequence * input,
  robot_communication__action__DoDishes_Goal__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_Result
 * )) before or use
 * robot_communication__action__DoDishes_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Result__init(robot_communication__action__DoDishes_Result * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Result__fini(robot_communication__action__DoDishes_Result * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_Result *
robot_communication__action__DoDishes_Result__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Result__destroy(robot_communication__action__DoDishes_Result * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Result__are_equal(const robot_communication__action__DoDishes_Result * lhs, const robot_communication__action__DoDishes_Result * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_Result__copy(
  const robot_communication__action__DoDishes_Result * input,
  robot_communication__action__DoDishes_Result * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Result__Sequence__init(robot_communication__action__DoDishes_Result__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Result__Sequence__fini(robot_communication__action__DoDishes_Result__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_Result__Sequence *
robot_communication__action__DoDishes_Result__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Result__Sequence__destroy(robot_communication__action__DoDishes_Result__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Result__Sequence__are_equal(const robot_communication__action__DoDishes_Result__Sequence * lhs, const robot_communication__action__DoDishes_Result__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_Result__Sequence__copy(
  const robot_communication__action__DoDishes_Result__Sequence * input,
  robot_communication__action__DoDishes_Result__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_Feedback
 * )) before or use
 * robot_communication__action__DoDishes_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Feedback__init(robot_communication__action__DoDishes_Feedback * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Feedback__fini(robot_communication__action__DoDishes_Feedback * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_Feedback *
robot_communication__action__DoDishes_Feedback__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Feedback__destroy(robot_communication__action__DoDishes_Feedback * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Feedback__are_equal(const robot_communication__action__DoDishes_Feedback * lhs, const robot_communication__action__DoDishes_Feedback * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_Feedback__copy(
  const robot_communication__action__DoDishes_Feedback * input,
  robot_communication__action__DoDishes_Feedback * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Feedback__Sequence__init(robot_communication__action__DoDishes_Feedback__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Feedback__Sequence__fini(robot_communication__action__DoDishes_Feedback__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_Feedback__Sequence *
robot_communication__action__DoDishes_Feedback__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_Feedback__Sequence__destroy(robot_communication__action__DoDishes_Feedback__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_Feedback__Sequence__are_equal(const robot_communication__action__DoDishes_Feedback__Sequence * lhs, const robot_communication__action__DoDishes_Feedback__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_Feedback__Sequence__copy(
  const robot_communication__action__DoDishes_Feedback__Sequence * input,
  robot_communication__action__DoDishes_Feedback__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_SendGoal_Request
 * )) before or use
 * robot_communication__action__DoDishes_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Request__init(robot_communication__action__DoDishes_SendGoal_Request * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Request__fini(robot_communication__action__DoDishes_SendGoal_Request * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_SendGoal_Request *
robot_communication__action__DoDishes_SendGoal_Request__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Request__destroy(robot_communication__action__DoDishes_SendGoal_Request * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Request__are_equal(const robot_communication__action__DoDishes_SendGoal_Request * lhs, const robot_communication__action__DoDishes_SendGoal_Request * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_SendGoal_Request__copy(
  const robot_communication__action__DoDishes_SendGoal_Request * input,
  robot_communication__action__DoDishes_SendGoal_Request * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Request__Sequence__init(robot_communication__action__DoDishes_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Request__Sequence__fini(robot_communication__action__DoDishes_SendGoal_Request__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_SendGoal_Request__Sequence *
robot_communication__action__DoDishes_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Request__Sequence__destroy(robot_communication__action__DoDishes_SendGoal_Request__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Request__Sequence__are_equal(const robot_communication__action__DoDishes_SendGoal_Request__Sequence * lhs, const robot_communication__action__DoDishes_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_SendGoal_Request__Sequence__copy(
  const robot_communication__action__DoDishes_SendGoal_Request__Sequence * input,
  robot_communication__action__DoDishes_SendGoal_Request__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_SendGoal_Response
 * )) before or use
 * robot_communication__action__DoDishes_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Response__init(robot_communication__action__DoDishes_SendGoal_Response * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Response__fini(robot_communication__action__DoDishes_SendGoal_Response * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_SendGoal_Response *
robot_communication__action__DoDishes_SendGoal_Response__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Response__destroy(robot_communication__action__DoDishes_SendGoal_Response * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Response__are_equal(const robot_communication__action__DoDishes_SendGoal_Response * lhs, const robot_communication__action__DoDishes_SendGoal_Response * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_SendGoal_Response__copy(
  const robot_communication__action__DoDishes_SendGoal_Response * input,
  robot_communication__action__DoDishes_SendGoal_Response * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Response__Sequence__init(robot_communication__action__DoDishes_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Response__Sequence__fini(robot_communication__action__DoDishes_SendGoal_Response__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_SendGoal_Response__Sequence *
robot_communication__action__DoDishes_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_SendGoal_Response__Sequence__destroy(robot_communication__action__DoDishes_SendGoal_Response__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_SendGoal_Response__Sequence__are_equal(const robot_communication__action__DoDishes_SendGoal_Response__Sequence * lhs, const robot_communication__action__DoDishes_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_SendGoal_Response__Sequence__copy(
  const robot_communication__action__DoDishes_SendGoal_Response__Sequence * input,
  robot_communication__action__DoDishes_SendGoal_Response__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_GetResult_Request
 * )) before or use
 * robot_communication__action__DoDishes_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Request__init(robot_communication__action__DoDishes_GetResult_Request * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Request__fini(robot_communication__action__DoDishes_GetResult_Request * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_GetResult_Request *
robot_communication__action__DoDishes_GetResult_Request__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Request__destroy(robot_communication__action__DoDishes_GetResult_Request * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Request__are_equal(const robot_communication__action__DoDishes_GetResult_Request * lhs, const robot_communication__action__DoDishes_GetResult_Request * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_GetResult_Request__copy(
  const robot_communication__action__DoDishes_GetResult_Request * input,
  robot_communication__action__DoDishes_GetResult_Request * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Request__Sequence__init(robot_communication__action__DoDishes_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Request__Sequence__fini(robot_communication__action__DoDishes_GetResult_Request__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_GetResult_Request__Sequence *
robot_communication__action__DoDishes_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Request__Sequence__destroy(robot_communication__action__DoDishes_GetResult_Request__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Request__Sequence__are_equal(const robot_communication__action__DoDishes_GetResult_Request__Sequence * lhs, const robot_communication__action__DoDishes_GetResult_Request__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_GetResult_Request__Sequence__copy(
  const robot_communication__action__DoDishes_GetResult_Request__Sequence * input,
  robot_communication__action__DoDishes_GetResult_Request__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_GetResult_Response
 * )) before or use
 * robot_communication__action__DoDishes_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Response__init(robot_communication__action__DoDishes_GetResult_Response * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Response__fini(robot_communication__action__DoDishes_GetResult_Response * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_GetResult_Response *
robot_communication__action__DoDishes_GetResult_Response__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Response__destroy(robot_communication__action__DoDishes_GetResult_Response * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Response__are_equal(const robot_communication__action__DoDishes_GetResult_Response * lhs, const robot_communication__action__DoDishes_GetResult_Response * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_GetResult_Response__copy(
  const robot_communication__action__DoDishes_GetResult_Response * input,
  robot_communication__action__DoDishes_GetResult_Response * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Response__Sequence__init(robot_communication__action__DoDishes_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Response__Sequence__fini(robot_communication__action__DoDishes_GetResult_Response__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_GetResult_Response__Sequence *
robot_communication__action__DoDishes_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_GetResult_Response__Sequence__destroy(robot_communication__action__DoDishes_GetResult_Response__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_GetResult_Response__Sequence__are_equal(const robot_communication__action__DoDishes_GetResult_Response__Sequence * lhs, const robot_communication__action__DoDishes_GetResult_Response__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_GetResult_Response__Sequence__copy(
  const robot_communication__action__DoDishes_GetResult_Response__Sequence * input,
  robot_communication__action__DoDishes_GetResult_Response__Sequence * output);

/// Initialize action/DoDishes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robot_communication__action__DoDishes_FeedbackMessage
 * )) before or use
 * robot_communication__action__DoDishes_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_FeedbackMessage__init(robot_communication__action__DoDishes_FeedbackMessage * msg);

/// Finalize action/DoDishes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_FeedbackMessage__fini(robot_communication__action__DoDishes_FeedbackMessage * msg);

/// Create action/DoDishes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robot_communication__action__DoDishes_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_FeedbackMessage *
robot_communication__action__DoDishes_FeedbackMessage__create();

/// Destroy action/DoDishes message.
/**
 * It calls
 * robot_communication__action__DoDishes_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_FeedbackMessage__destroy(robot_communication__action__DoDishes_FeedbackMessage * msg);

/// Check for action/DoDishes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_FeedbackMessage__are_equal(const robot_communication__action__DoDishes_FeedbackMessage * lhs, const robot_communication__action__DoDishes_FeedbackMessage * rhs);

/// Copy a action/DoDishes message.
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
robot_communication__action__DoDishes_FeedbackMessage__copy(
  const robot_communication__action__DoDishes_FeedbackMessage * input,
  robot_communication__action__DoDishes_FeedbackMessage * output);

/// Initialize array of action/DoDishes messages.
/**
 * It allocates the memory for the number of elements and calls
 * robot_communication__action__DoDishes_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_FeedbackMessage__Sequence__init(robot_communication__action__DoDishes_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_FeedbackMessage__Sequence__fini(robot_communication__action__DoDishes_FeedbackMessage__Sequence * array);

/// Create array of action/DoDishes messages.
/**
 * It allocates the memory for the array and calls
 * robot_communication__action__DoDishes_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
robot_communication__action__DoDishes_FeedbackMessage__Sequence *
robot_communication__action__DoDishes_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/DoDishes messages.
/**
 * It calls
 * robot_communication__action__DoDishes_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
void
robot_communication__action__DoDishes_FeedbackMessage__Sequence__destroy(robot_communication__action__DoDishes_FeedbackMessage__Sequence * array);

/// Check for action/DoDishes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robot_communication
bool
robot_communication__action__DoDishes_FeedbackMessage__Sequence__are_equal(const robot_communication__action__DoDishes_FeedbackMessage__Sequence * lhs, const robot_communication__action__DoDishes_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/DoDishes messages.
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
robot_communication__action__DoDishes_FeedbackMessage__Sequence__copy(
  const robot_communication__action__DoDishes_FeedbackMessage__Sequence * input,
  robot_communication__action__DoDishes_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__FUNCTIONS_H_
