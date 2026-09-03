// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_communication:msg/ChassisControl.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/chassis_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robot_communication__msg__ChassisControl__init(robot_communication__msg__ChassisControl * msg)
{
  if (!msg) {
    return false;
  }
  // xspeed
  // yspeed
  // chassisangle
  // chassisgyro
  // timestamp
  // globalorlocal
  return true;
}

void
robot_communication__msg__ChassisControl__fini(robot_communication__msg__ChassisControl * msg)
{
  if (!msg) {
    return;
  }
  // xspeed
  // yspeed
  // chassisangle
  // chassisgyro
  // timestamp
  // globalorlocal
}

bool
robot_communication__msg__ChassisControl__are_equal(const robot_communication__msg__ChassisControl * lhs, const robot_communication__msg__ChassisControl * rhs)
{
  if (!lhs || !rhs) {
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
  // globalorlocal
  if (lhs->globalorlocal != rhs->globalorlocal) {
    return false;
  }
  return true;
}

bool
robot_communication__msg__ChassisControl__copy(
  const robot_communication__msg__ChassisControl * input,
  robot_communication__msg__ChassisControl * output)
{
  if (!input || !output) {
    return false;
  }
  // xspeed
  output->xspeed = input->xspeed;
  // yspeed
  output->yspeed = input->yspeed;
  // chassisangle
  output->chassisangle = input->chassisangle;
  // chassisgyro
  output->chassisgyro = input->chassisgyro;
  // timestamp
  output->timestamp = input->timestamp;
  // globalorlocal
  output->globalorlocal = input->globalorlocal;
  return true;
}

robot_communication__msg__ChassisControl *
robot_communication__msg__ChassisControl__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__ChassisControl * msg = (robot_communication__msg__ChassisControl *)allocator.allocate(sizeof(robot_communication__msg__ChassisControl), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_communication__msg__ChassisControl));
  bool success = robot_communication__msg__ChassisControl__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_communication__msg__ChassisControl__destroy(robot_communication__msg__ChassisControl * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_communication__msg__ChassisControl__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_communication__msg__ChassisControl__Sequence__init(robot_communication__msg__ChassisControl__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__ChassisControl * data = NULL;

  if (size) {
    data = (robot_communication__msg__ChassisControl *)allocator.zero_allocate(size, sizeof(robot_communication__msg__ChassisControl), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_communication__msg__ChassisControl__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_communication__msg__ChassisControl__fini(&data[i - 1]);
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
robot_communication__msg__ChassisControl__Sequence__fini(robot_communication__msg__ChassisControl__Sequence * array)
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
      robot_communication__msg__ChassisControl__fini(&array->data[i]);
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

robot_communication__msg__ChassisControl__Sequence *
robot_communication__msg__ChassisControl__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__ChassisControl__Sequence * array = (robot_communication__msg__ChassisControl__Sequence *)allocator.allocate(sizeof(robot_communication__msg__ChassisControl__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_communication__msg__ChassisControl__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_communication__msg__ChassisControl__Sequence__destroy(robot_communication__msg__ChassisControl__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_communication__msg__ChassisControl__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_communication__msg__ChassisControl__Sequence__are_equal(const robot_communication__msg__ChassisControl__Sequence * lhs, const robot_communication__msg__ChassisControl__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_communication__msg__ChassisControl__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_communication__msg__ChassisControl__Sequence__copy(
  const robot_communication__msg__ChassisControl__Sequence * input,
  robot_communication__msg__ChassisControl__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_communication__msg__ChassisControl);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_communication__msg__ChassisControl * data =
      (robot_communication__msg__ChassisControl *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_communication__msg__ChassisControl__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_communication__msg__ChassisControl__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_communication__msg__ChassisControl__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
