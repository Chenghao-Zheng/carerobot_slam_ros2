// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_communication:msg/EsdfMap.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/esdf_map__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
robot_communication__msg__EsdfMap__init(robot_communication__msg__EsdfMap * msg)
{
  if (!msg) {
    return false;
  }
  // origin_x
  // origin_y
  // resolution
  // width
  // height
  // data
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->data, 0)) {
    robot_communication__msg__EsdfMap__fini(msg);
    return false;
  }
  return true;
}

void
robot_communication__msg__EsdfMap__fini(robot_communication__msg__EsdfMap * msg)
{
  if (!msg) {
    return;
  }
  // origin_x
  // origin_y
  // resolution
  // width
  // height
  // data
  rosidl_runtime_c__int32__Sequence__fini(&msg->data);
}

bool
robot_communication__msg__EsdfMap__are_equal(const robot_communication__msg__EsdfMap * lhs, const robot_communication__msg__EsdfMap * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // origin_x
  if (lhs->origin_x != rhs->origin_x) {
    return false;
  }
  // origin_y
  if (lhs->origin_y != rhs->origin_y) {
    return false;
  }
  // resolution
  if (lhs->resolution != rhs->resolution) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // data
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
robot_communication__msg__EsdfMap__copy(
  const robot_communication__msg__EsdfMap * input,
  robot_communication__msg__EsdfMap * output)
{
  if (!input || !output) {
    return false;
  }
  // origin_x
  output->origin_x = input->origin_x;
  // origin_y
  output->origin_y = input->origin_y;
  // resolution
  output->resolution = input->resolution;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  // data
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

robot_communication__msg__EsdfMap *
robot_communication__msg__EsdfMap__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__EsdfMap * msg = (robot_communication__msg__EsdfMap *)allocator.allocate(sizeof(robot_communication__msg__EsdfMap), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_communication__msg__EsdfMap));
  bool success = robot_communication__msg__EsdfMap__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_communication__msg__EsdfMap__destroy(robot_communication__msg__EsdfMap * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_communication__msg__EsdfMap__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_communication__msg__EsdfMap__Sequence__init(robot_communication__msg__EsdfMap__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__EsdfMap * data = NULL;

  if (size) {
    data = (robot_communication__msg__EsdfMap *)allocator.zero_allocate(size, sizeof(robot_communication__msg__EsdfMap), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_communication__msg__EsdfMap__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_communication__msg__EsdfMap__fini(&data[i - 1]);
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
robot_communication__msg__EsdfMap__Sequence__fini(robot_communication__msg__EsdfMap__Sequence * array)
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
      robot_communication__msg__EsdfMap__fini(&array->data[i]);
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

robot_communication__msg__EsdfMap__Sequence *
robot_communication__msg__EsdfMap__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__EsdfMap__Sequence * array = (robot_communication__msg__EsdfMap__Sequence *)allocator.allocate(sizeof(robot_communication__msg__EsdfMap__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_communication__msg__EsdfMap__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_communication__msg__EsdfMap__Sequence__destroy(robot_communication__msg__EsdfMap__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_communication__msg__EsdfMap__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_communication__msg__EsdfMap__Sequence__are_equal(const robot_communication__msg__EsdfMap__Sequence * lhs, const robot_communication__msg__EsdfMap__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_communication__msg__EsdfMap__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_communication__msg__EsdfMap__Sequence__copy(
  const robot_communication__msg__EsdfMap__Sequence * input,
  robot_communication__msg__EsdfMap__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_communication__msg__EsdfMap);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_communication__msg__EsdfMap * data =
      (robot_communication__msg__EsdfMap *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_communication__msg__EsdfMap__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_communication__msg__EsdfMap__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_communication__msg__EsdfMap__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
