# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_communication:msg/ChassisControl.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ChassisControl(type):
    """Metaclass of message 'ChassisControl'."""

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
                'robot_communication.msg.ChassisControl')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__chassis_control
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__chassis_control
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__chassis_control
            cls._TYPE_SUPPORT = module.type_support_msg__msg__chassis_control
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__chassis_control

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ChassisControl(metaclass=Metaclass_ChassisControl):
    """Message class 'ChassisControl'."""

    __slots__ = [
        '_xspeed',
        '_yspeed',
        '_chassisangle',
        '_chassisgyro',
        '_timestamp',
        '_globalorlocal',
    ]

    _fields_and_field_types = {
        'xspeed': 'float',
        'yspeed': 'float',
        'chassisangle': 'float',
        'chassisgyro': 'float',
        'timestamp': 'uint32',
        'globalorlocal': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.xspeed = kwargs.get('xspeed', float())
        self.yspeed = kwargs.get('yspeed', float())
        self.chassisangle = kwargs.get('chassisangle', float())
        self.chassisgyro = kwargs.get('chassisgyro', float())
        self.timestamp = kwargs.get('timestamp', int())
        self.globalorlocal = kwargs.get('globalorlocal', bool())

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
        if self.xspeed != other.xspeed:
            return False
        if self.yspeed != other.yspeed:
            return False
        if self.chassisangle != other.chassisangle:
            return False
        if self.chassisgyro != other.chassisgyro:
            return False
        if self.timestamp != other.timestamp:
            return False
        if self.globalorlocal != other.globalorlocal:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def xspeed(self):
        """Message field 'xspeed'."""
        return self._xspeed

    @xspeed.setter
    def xspeed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'xspeed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'xspeed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._xspeed = value

    @builtins.property
    def yspeed(self):
        """Message field 'yspeed'."""
        return self._yspeed

    @yspeed.setter
    def yspeed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yspeed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'yspeed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._yspeed = value

    @builtins.property
    def chassisangle(self):
        """Message field 'chassisangle'."""
        return self._chassisangle

    @chassisangle.setter
    def chassisangle(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'chassisangle' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'chassisangle' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._chassisangle = value

    @builtins.property
    def chassisgyro(self):
        """Message field 'chassisgyro'."""
        return self._chassisgyro

    @chassisgyro.setter
    def chassisgyro(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'chassisgyro' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'chassisgyro' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._chassisgyro = value

    @builtins.property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestamp' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'timestamp' field must be an unsigned integer in [0, 4294967295]"
        self._timestamp = value

    @builtins.property
    def globalorlocal(self):
        """Message field 'globalorlocal'."""
        return self._globalorlocal

    @globalorlocal.setter
    def globalorlocal(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'globalorlocal' field must be of type 'bool'"
        self._globalorlocal = value
