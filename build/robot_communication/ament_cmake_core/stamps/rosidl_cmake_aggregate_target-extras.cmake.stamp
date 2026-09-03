# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target robot_communication::robot_communication
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${robot_communication_TARGETS}.
if(robot_communication_TARGETS AND NOT TARGET robot_communication::robot_communication)
  add_library(robot_communication::robot_communication INTERFACE IMPORTED)
  set_target_properties(robot_communication::robot_communication PROPERTIES
    INTERFACE_LINK_LIBRARIES "${robot_communication_TARGETS}")
endif()
