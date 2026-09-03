#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "robot_costmap::robot_costmap" for configuration "Debug"
set_property(TARGET robot_costmap::robot_costmap APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(robot_costmap::robot_costmap PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/librobot_costmap.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS robot_costmap::robot_costmap )
list(APPEND _IMPORT_CHECK_FILES_FOR_robot_costmap::robot_costmap "${_IMPORT_PREFIX}/lib/librobot_costmap.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
