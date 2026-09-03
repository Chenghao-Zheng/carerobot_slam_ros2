// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_communication:msg/SensorData.idl
// generated code does not contain a copyright notice
#include "robot_communication/msg/detail/sensor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
robot_communication__msg__SensorData__init(robot_communication__msg__SensorData * msg)
{
  if (!msg) {
    return false;
  }
  // local_x_veloc
  // local_y_veloc
  // local_x_accel
  // local_y_accel
  // yaw
  // timestamp_10us
  return true;
}

void
robot_communication__msg__SensorData__fini(robot_communication__msg__SensorData * msg)
{
  if (!msg) {
    return;
  }
  // local_x_veloc
  // local_y_veloc
  // local_x_accel
  // local_y_accel
  // yaw
  // timestamp_10us
}

bool
robot_communication__msg__SensorData__are_equal(const robot_communication__msg__SensorData * lhs, const robot_communication__msg__SensorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // local_x_veloc
  if (lhs->local_x_veloc != rhs->local_x_veloc) {
    return false;
  }
  // local_y_veloc
  if (lhs->local_y_veloc != rhs->local_y_veloc) {
    return false;
  }
  // local_x_accel
  if (lhs->local_x_accel != rhs->local_x_accel) {
    return false;
  }
  // local_y_accel
  if (lhs->local_y_accel != rhs->local_y_accel) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // timestamp_10us
  if (lhs->timestamp_10us != rhs->timestamp_10us) {
    return false;
  }
  return true;
}

bool
robot_communication__msg__SensorData__copy(
  const robot_communication__msg__SensorData * input,
  robot_communication__msg__SensorData * output)
{
  if (!input || !output) {
    return false;
  }
  // local_x_veloc
  output->local_x_veloc = input->local_x_veloc;
  // local_y_veloc
  output->local_y_veloc = input->local_y_veloc;
  // local_x_accel
  output->local_x_accel = input->local_x_accel;
  // local_y_accel
  output->local_y_accel = input->local_y_accel;
  // yaw
  output->yaw = input->yaw;
  // timestamp_10us
  output->timestamp_10us = input->timestamp_10us;
  return true;
}

robot_communication__msg__SensorData *
robot_communication__msg__SensorData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__SensorData * msg = (robot_communication__msg__SensorData *)allocator.allocate(sizeof(robot_communication__msg__SensorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_communication__msg__SensorData));
  bool success = robot_communication__msg__SensorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_communication__msg__SensorData__destroy(robot_communication__msg__SensorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_communication__msg__SensorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_communication__msg__SensorData__Sequence__init(robot_communication__msg__SensorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__SensorData * data = NULL;

  if (size) {
    data = (robot_communication__msg__SensorData *)allocator.zero_allocate(size, sizeof(robot_communication__msg__SensorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_communication__msg__SensorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_communication__msg__SensorData__fini(&data[i - 1]);
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
robot_communication__msg__SensorData__Sequence__fini(robot_communication__msg__SensorData__Sequence * array)
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
      robot_communication__msg__SensorData__fini(&array->data[i]);
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

robot_communication__msg__SensorData__Sequence *
robot_communication__msg__SensorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_communication__msg__SensorData__Sequence * array = (robot_communication__msg__SensorData__Sequence *)allocator.allocate(sizeof(robot_communication__msg__SensorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_communication__msg__SensorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_communication__msg__SensorData__Sequence__destroy(robot_communication__msg__SensorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_communication__msg__SensorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_communication__msg__SensorData__Sequence__are_equal(const robot_communication__msg__SensorData__Sequence * lhs, const robot_communication__msg__SensorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_communication__msg__SensorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_communication__msg__SensorData__Sequence__copy(
  const robot_communication__msg__SensorData__Sequence * input,
  robot_communication__msg__SensorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_communication__msg__SensorData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_communication__msg__SensorData * data =
      (robot_communication__msg__SensorData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_communication__msg__SensorData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_communication__msg__SensorData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_communication__msg__SensorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
