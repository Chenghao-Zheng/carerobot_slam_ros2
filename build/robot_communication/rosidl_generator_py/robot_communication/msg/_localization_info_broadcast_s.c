// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from robot_communication:msg/LocalizationInfoBroadcast.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "robot_communication/msg/detail/localization_info_broadcast__struct.h"
#include "robot_communication/msg/detail/localization_info_broadcast__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool robot_communication__msg__localization_info_broadcast__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[79];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("robot_communication.msg._localization_info_broadcast.LocalizationInfoBroadcast", full_classname_dest, 78) == 0);
  }
  robot_communication__msg__LocalizationInfoBroadcast * ros_message = _ros_message;
  {  // xposition
    PyObject * field = PyObject_GetAttrString(_pymsg, "xposition");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->xposition = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yposition
    PyObject * field = PyObject_GetAttrString(_pymsg, "yposition");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yposition = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // xspeed
    PyObject * field = PyObject_GetAttrString(_pymsg, "xspeed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->xspeed = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yspeed
    PyObject * field = PyObject_GetAttrString(_pymsg, "yspeed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yspeed = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // xaccel
    PyObject * field = PyObject_GetAttrString(_pymsg, "xaccel");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->xaccel = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yaccel
    PyObject * field = PyObject_GetAttrString(_pymsg, "yaccel");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yaccel = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // chassisangle
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassisangle");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->chassisangle = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // chassisgyro
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassisgyro");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->chassisgyro = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // timestamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestamp = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * robot_communication__msg__localization_info_broadcast__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of LocalizationInfoBroadcast */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("robot_communication.msg._localization_info_broadcast");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "LocalizationInfoBroadcast");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  robot_communication__msg__LocalizationInfoBroadcast * ros_message = (robot_communication__msg__LocalizationInfoBroadcast *)raw_ros_message;
  {  // xposition
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->xposition);
    {
      int rc = PyObject_SetAttrString(_pymessage, "xposition", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yposition
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yposition);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yposition", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // xspeed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->xspeed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "xspeed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yspeed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yspeed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yspeed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // xaccel
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->xaccel);
    {
      int rc = PyObject_SetAttrString(_pymessage, "xaccel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yaccel
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yaccel);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yaccel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassisangle
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->chassisangle);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassisangle", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassisgyro
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->chassisgyro);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassisgyro", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timestamp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->timestamp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
