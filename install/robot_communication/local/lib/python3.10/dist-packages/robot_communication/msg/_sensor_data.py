# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_communication:msg/SensorData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorData(type):
    """Metaclass of message 'SensorData'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('robot_communication')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'robot_communication.msg.SensorData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensor_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensor_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensor_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensor_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensor_data

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SensorData(metaclass=Metaclass_SensorData):
    """Message class 'SensorData'."""

    __slots__ = [
        '_local_x_veloc',
        '_local_y_veloc',
        '_local_x_accel',
        '_local_y_accel',
        '_yaw',
        '_timestamp_10us',
    ]

    _fields_and_field_types = {
        'local_x_veloc': 'float',
        'local_y_veloc': 'float',
        'local_x_accel': 'float',
        'local_y_accel': 'float',
        'yaw': 'float',
        'timestamp_10us': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.local_x_veloc = kwargs.get('local_x_veloc', float())
        self.local_y_veloc = kwargs.get('local_y_veloc', float())
        self.local_x_accel = kwargs.get('local_x_accel', float())
        self.local_y_accel = kwargs.get('local_y_accel', float())
        self.yaw = kwargs.get('yaw', float())
        self.timestamp_10us = kwargs.get('timestamp_10us', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.local_x_veloc != other.local_x_veloc:
            return False
        if self.local_y_veloc != other.local_y_veloc:
            return False
        if self.local_x_accel != other.local_x_accel:
            return False
        if self.local_y_accel != other.local_y_accel:
            return False
        if self.yaw != other.yaw:
            return False
        if self.timestamp_10us != other.timestamp_10us:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def local_x_veloc(self):
        """Message field 'local_x_veloc'."""
        return self._local_x_veloc

    @local_x_veloc.setter
    def local_x_veloc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'local_x_veloc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'local_x_veloc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._local_x_veloc = value

    @builtins.property
    def local_y_veloc(self):
        """Message field 'local_y_veloc'."""
        return self._local_y_veloc

    @local_y_veloc.setter
    def local_y_veloc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'local_y_veloc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'local_y_veloc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._local_y_veloc = value

    @builtins.property
    def local_x_accel(self):
        """Message field 'local_x_accel'."""
        return self._local_x_accel

    @local_x_accel.setter
    def local_x_accel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'local_x_accel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'local_x_accel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._local_x_accel = value

    @builtins.property
    def local_y_accel(self):
        """Message field 'local_y_accel'."""
        return self._local_y_accel

    @local_y_accel.setter
    def local_y_accel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'local_y_accel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'local_y_accel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._local_y_accel = value

    @builtins.property
    def yaw(self):
        """Message field 'yaw'."""
        return self._yaw

    @yaw.setter
    def yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._yaw = value

    @builtins.property
    def timestamp_10us(self):
        """Message field 'timestamp_10us'."""
        return self._timestamp_10us

    @timestamp_10us.setter
    def timestamp_10us(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestamp_10us' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'timestamp_10us' field must be an unsigned integer in [0, 4294967295]"
        self._timestamp_10us = value
