// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_communication:msg/Goal.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/goal__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robot_communication__msg__Goal__init(robot_communication__msg__Goal * msg)
{
  if (!msg) {
    return false;
  }
  // position_x
  // position_y
  // position_yaw
  return true;
}

void
robot_communication__msg__Goal__fini(robot_communication__msg__Goal * msg)
{
  if (!msg) {
    return;
  }
  // position_x
  // position_y
  // position_yaw
}

bool
robot_communication__msg__Goal__are_equal(const robot_communication__msg__Goal * lhs, const robot_communication__msg__Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position_x
  if (lhs->position_x != rhs->position_x) {
    return false;
  }
  // position_y
  if (lhs->position_y != rhs->position_y) {
    return false;
  }
  // position_yaw
  if (lhs->position_yaw != rhs->position_yaw) {
    return false;
  }
  return true;
}

bool
robot_communication__msg__Goal__copy(
  const robot_communication__msg__Goal * input,
  robot_communication__msg__Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // position_x
  output->position_x = input->position_x;
  // position_y
  output->position_y = input->position_y;
  // position_yaw
  output->position_yaw = input->position_yaw;
  return true;
}

robot_communication__msg__Goal *
robot_communication__msg__Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__Goal * msg = (robot_communication__msg__Goal *)allocator.allocate(sizeof(robot_communication__msg__Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_communication__msg__Goal));
  bool success = robot_communication__msg__Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_communication__msg__Goal__destroy(robot_communication__msg__Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_communication__msg__Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_communication__msg__Goal__Sequence__init(robot_communication__msg__Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__Goal * data = NULL;

  if (size) {
    data = (robot_communication__msg__Goal *)allocator.zero_allocate(size, sizeof(robot_communication__msg__Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_communication__msg__Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_communication__msg__Goal__fini(&data[i - 1]);
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
robot_communication__msg__Goal__Sequence__fini(robot_communication__msg__Goal__Sequence * array)
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
      robot_communication__msg__Goal__fini(&array->data[i]);
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

robot_communication__msg__Goal__Sequence *
robot_communication__msg__Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__Goal__Sequence * array = (robot_communication__msg__Goal__Sequence *)allocator.allocate(sizeof(robot_communication__msg__Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_communication__msg__Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_communication__msg__Goal__Sequence__destroy(robot_communication__msg__Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_communication__msg__Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_communication__msg__Goal__Sequence__are_equal(const robot_communication__msg__Goal__Sequence * lhs, const robot_communication__msg__Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_communication__msg__Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_communication__msg__Goal__Sequence__copy(
  const robot_communication__msg__Goal__Sequence * input,
  robot_communication__msg__Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_communication__msg__Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_communication__msg__Goal * data =
      (robot_communication__msg__Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_communication__msg__Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_communication__msg__Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_communication__msg__Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
