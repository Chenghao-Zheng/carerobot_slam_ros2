cmake_minimum_required(VERSION 3.8)
project(robot_communication)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(action_msgs REQUIRED)

set(msg_files
  msg/LocalizationInfoBroadcast.msg
  msg/ChassisControl.msg
  msg/SensorData.msg
  msg/Bspline.msg
  msg/EsdfMap.msg
  msg/Goal.msg
)

set(action_files
  action/DoDishes.action
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${action_files}
  DEPENDENCIES std_msgs geometry_msgs nav_msgs builtin_interfaces action_msgs
)

ament_package()