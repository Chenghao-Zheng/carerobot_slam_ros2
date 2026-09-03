// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_communication:msg/Bspline.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/bspline__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `knots`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `pts`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `start_time`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
robot_communication__msg__Bspline__init(robot_communication__msg__Bspline * msg)
{
  if (!msg) {
    return false;
  }
  // order
  // traj_id
  // knots
  if (!rosidl_runtime_c__double__Sequence__init(&msg->knots, 0)) {
    robot_communication__msg__Bspline__fini(msg);
    return false;
  }
  // pts
  if (!geometry_msgs__msg__Point__Sequence__init(&msg->pts, 0)) {
    robot_communication__msg__Bspline__fini(msg);
    return false;
  }
  // start_time
  if (!builtin_interfaces__msg__Time__init(&msg->start_time)) {
    robot_communication__msg__Bspline__fini(msg);
    return false;
  }
  return true;
}

void
robot_communication__msg__Bspline__fini(robot_communication__msg__Bspline * msg)
{
  if (!msg) {
    return;
  }
  // order
  // traj_id
  // knots
  rosidl_runtime_c__double__Sequence__fini(&msg->knots);
  // pts
  geometry_msgs__msg__Point__Sequence__fini(&msg->pts);
  // start_time
  builtin_interfaces__msg__Time__fini(&msg->start_time);
}

bool
robot_communication__msg__Bspline__are_equal(const robot_communication__msg__Bspline * lhs, const robot_communication__msg__Bspline * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // order
  if (lhs->order != rhs->order) {
    return false;
  }
  // traj_id
  if (lhs->traj_id != rhs->traj_id) {
    return false;
  }
  // knots
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->knots), &(rhs->knots)))
  {
    return false;
  }
  // pts
  if (!geometry_msgs__msg__Point__Sequence__are_equal(
      &(lhs->pts), &(rhs->pts)))
  {
    return false;
  }
  // start_time
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->start_time), &(rhs->start_time)))
  {
    return false;
  }
  return true;
}

bool
robot_communication__msg__Bspline__copy(
  const robot_communication__msg__Bspline * input,
  robot_communication__msg__Bspline * output)
{
  if (!input || !output) {
    return false;
  }
  // order
  output->order = input->order;
  // traj_id
  output->traj_id = input->traj_id;
  // knots
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->knots), &(output->knots)))
  {
    return false;
  }
  // pts
  if (!geometry_msgs__msg__Point__Sequence__copy(
      &(input->pts), &(output->pts)))
  {
    return false;
  }
  // start_time
  if (!builtin_interfaces__msg__Time__copy(
      &(input->start_time), &(output->start_time)))
  {
    return false;
  }
  return true;
}

robot_communication__msg__Bspline *
robot_communication__msg__Bspline__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__Bspline * msg = (robot_communication__msg__Bspline *)allocator.allocate(sizeof(robot_communication__msg__Bspline), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_communication__msg__Bspline));
  bool success = robot_communication__msg__Bspline__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_communication__msg__Bspline__destroy(robot_communication__msg__Bspline * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_communication__msg__Bspline__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_communication__msg__Bspline__Sequence__init(robot_communication__msg__Bspline__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__Bspline * data = NULL;

  if (size) {
    data = (robot_communication__msg__Bspline *)allocator.zero_allocate(size, sizeof(robot_communication__msg__Bspline), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_communication__msg__Bspline__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_communication__msg__Bspline__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_communication__msg__Bspline__Sequence__fini(robot_communication__msg__Bspline__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_communication__msg__Bspline__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_communication__msg__Bspline__Sequence *
robot_communication__msg__Bspline__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__Bspline__Sequence * array = (robot_communication__msg__Bspline__Sequence *)allocator.allocate(sizeof(robot_communication__msg__Bspline__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_communication__msg__Bspline__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_communication__msg__Bspline__Sequence__destroy(robot_communication__msg__Bspline__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_communication__msg__Bspline__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_communication__msg__Bspline__Sequence__are_equal(const robot_communication__msg__Bspline__Sequence * lhs, const robot_communication__msg__Bspline__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_communication__msg__Bspline__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_communication__msg__Bspline__Sequence__copy(
  const robot_communication__msg__Bspline__Sequence * input,
  robot_communication__msg__Bspline__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_communication__msg__Bspline);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_communication__msg__Bspline * data =
      (robot_communication__msg__Bspline *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_communication__msg__Bspline__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_communication__msg__Bspline__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_communication__msg__Bspline__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
