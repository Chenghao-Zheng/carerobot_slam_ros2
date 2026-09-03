# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_communication:msg/EsdfMap.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'data'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_EsdfMap(type):
    """Metaclass of message 'EsdfMap'."""

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
                'robot_communication.msg.EsdfMap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__esdf_map
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__esdf_map
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__esdf_map
            cls._TYPE_SUPPORT = module.type_support_msg__msg__esdf_map
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__esdf_map

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class EsdfMap(metaclass=Metaclass_EsdfMap):
    """Message class 'EsdfMap'."""

    __slots__ = [
        '_origin_x',
        '_origin_y',
        '_resolution',
        '_width',
        '_height',
        '_data',
    ]

    _fields_and_field_types = {
        'origin_x': 'float',
        'origin_y': 'float',
        'resolution': 'float',
        'width': 'float',
        'height': 'float',
        'data': 'sequence<int32>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.origin_x = kwargs.get('origin_x', float())
        self.origin_y = kwargs.get('origin_y', float())
        self.resolution = kwargs.get('resolution', float())
        self.width = kwargs.get('width', float())
        self.height = kwargs.get('height', float())
        self.data = array.array('i', kwargs.get('data', []))

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
        if self.origin_x != other.origin_x:
            return False
        if self.origin_y != other.origin_y:
            return False
        if self.resolution != other.resolution:
            return False
        if self.width != other.width:
            return False
        if self.height != other.height:
            return False
        if self.data != other.data:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def origin_x(self):
        """Message field 'origin_x'."""
        return self._origin_x

    @origin_x.setter
    def origin_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'origin_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'origin_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._origin_x = value

    @builtins.property
    def origin_y(self):
        """Message field 'origin_y'."""
        return self._origin_y

    @origin_y.setter
    def origin_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'origin_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'origin_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._origin_y = value

    @builtins.property
    def resolution(self):
        """Message field 'resolution'."""
        return self._resolution

    @resolution.setter
    def resolution(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'resolution' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'resolution' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._resolution = value

    @builtins.property
    def width(self):
        """Message field 'width'."""
        return self._width

    @width.setter
    def width(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'width' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'width' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._width = value

    @builtins.property
    def height(self):
        """Message field 'height'."""
        return self._height

    @height.setter
    def height(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'height' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'height' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._height = value

    @builtins.property
    def data(self):
        """Message field 'data'."""
        return self._data

    @data.setter
    def data(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'i', \
                "The 'data' array.array() must have the type code of 'i'"
            self._data = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'data' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._data = array.array('i', value)
