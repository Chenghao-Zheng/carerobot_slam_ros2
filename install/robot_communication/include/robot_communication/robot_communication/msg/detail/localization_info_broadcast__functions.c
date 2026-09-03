// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/localization_info_broadcast__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robot_communication__msg__LocalizationInfoBroadcast__init(robot_communication__msg__LocalizationInfoBroadcast * msg)
{
  if (!msg) {
    return false;
  }
  // xposition
  // yposition
  // xspeed
  // yspeed
  // xaccel
  // yaccel
  // chassisangle
  // chassisgyro
  // timestamp
  return true;
}

void
robot_communication__msg__LocalizationInfoBroadcast__fini(robot_communication__msg__LocalizationInfoBroadcast * msg)
{
  if (!msg) {
    return;
  }
  // xposition
  // yposition
  // xspeed
  // yspeed
  // xaccel
  // yaccel
  // chassisangle
  // chassisgyro
  // timestamp
}

bool
robot_communication__msg__LocalizationInfoBroadcast__are_equal(const robot_communication__msg__LocalizationInfoBroadcast * lhs, const robot_communication__msg__LocalizationInfoBroadcast * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // xposition
  if (lhs->xposition != rhs->xposition) {
    return false;
  }
  // yposition
  if (lhs->yposition != rhs->yposition) {
    return false;
  }
  // xspeed
  if (lhs->xspeed != rhs->xspeed) {
    return false;
  }
  // yspeed
  if (lhs->yspeed != rhs->yspeed) {
    return false;
  }
  // xaccel
  if (lhs->xaccel != rhs->xaccel) {
    return false;
  }
  // yaccel
  if (lhs->yaccel != rhs->yaccel) {
    return false;
  }
  // chassisangle
  if (lhs->chassisangle != rhs->chassisangle) {
    return false;
  }
  // chassisgyro
  if (lhs->chassisgyro != rhs->chassisgyro) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  return true;
}

bool
robot_communication__msg__LocalizationInfoBroadcast__copy(
  const robot_communication__msg__LocalizationInfoBroadcast * input,
  robot_communication__msg__LocalizationInfoBroadcast * output)
{
  if (!input || !output) {
    return false;
  }
  // xposition
  output->xposition = input->xposition;
  // yposition
  output->yposition = input->yposition;
  // xspeed
  output->xspeed = input->xspeed;
  // yspeed
  output->yspeed = input->yspeed;
  // xaccel
  output->xaccel = input->xaccel;
  // yaccel
  output->yaccel = input->yaccel;
  // chassisangle
  output->chassisangle = input->chassisangle;
  // chassisgyro
  output->chassisgyro = input->chassisgyro;
  // timestamp
  output->timestamp = input->timestamp;
  return true;
}

robot_communication__msg__LocalizationInfoBroadcast *
robot_communication__msg__LocalizationInfoBroadcast__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__LocalizationInfoBroadcast * msg = (robot_communication__msg__LocalizationInfoBroadcast *)allocator.allocate(sizeof(robot_communication__msg__LocalizationInfoBroadcast), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_communication__msg__LocalizationInfoBroadcast));
  bool success = robot_communication__msg__LocalizationInfoBroadcast__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_communication__msg__LocalizationInfoBroadcast__destroy(robot_communication__msg__LocalizationInfoBroadcast * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_communication__msg__LocalizationInfoBroadcast__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_communication__msg__LocalizationInfoBroadcast__Sequence__init(robot_communication__msg__LocalizationInfoBroadcast__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__LocalizationInfoBroadcast * data = NULL;

  if (size) {
    data = (robot_communication__msg__LocalizationInfoBroadcast *)allocator.zero_allocate(size, sizeof(robot_communication__msg__LocalizationInfoBroadcast), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_communication__msg__LocalizationInfoBroadcast__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_communication__msg__LocalizationInfoBroadcast__fini(&data[i - 1]);
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
robot_communication__msg__LocalizationInfoBroadcast__Sequence__fini(robot_communication__msg__LocalizationInfoBroadcast__Sequence * array)
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
      robot_communication__msg__LocalizationInfoBroadcast__fini(&array->data[i]);
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

robot_communication__msg__LocalizationInfoBroadcast__Sequence *
robot_communication__msg__LocalizationInfoBroadcast__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__LocalizationInfoBroadcast__Sequence * array = (robot_communication__msg__LocalizationInfoBroadcast__Sequence *)allocator.allocate(sizeof(robot_communication__msg__LocalizationInfoBroadcast__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_communication__msg__LocalizationInfoBroadcast__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_communication__msg__LocalizationInfoBroadcast__Sequence__destroy(robot_communication__msg__LocalizationInfoBroadcast__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_communication__msg__LocalizationInfoBroadcast__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_communication__msg__LocalizationInfoBroadcast__Sequence__are_equal(const robot_communication__msg__LocalizationInfoBroadcast__Sequence * lhs, const robot_communication__msg__LocalizationInfoBroadcast__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_communication__msg__LocalizationInfoBroadcast__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_communication__msg__LocalizationInfoBroadcast__Sequence__copy(
  const robot_communication__msg__LocalizationInfoBroadcast__Sequence * input,
  robot_communication__msg__LocalizationInfoBroadcast__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_communication__msg__LocalizationInfoBroadcast);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_communication__msg__LocalizationInfoBroadcast * data =
      (robot_communication__msg__LocalizationInfoBroadcast *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_communication__msg__LocalizationInfoBroadcast__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_communication__msg__LocalizationInfoBroadcast__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_communication__msg__LocalizationInfoBroadcast__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
