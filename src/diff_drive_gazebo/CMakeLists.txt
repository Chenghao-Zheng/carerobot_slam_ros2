cmake_minimum_required(VERSION 3.8)
project(diff_drive_gazebo)

if(NOT CMAKE_COMPILER_IS_GNUCXX AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(urdf REQUIRED)
find_package(xacro REQUIRED)

# 导出安装路径（Launch, URDF, Mesh, World 等静态文件）
install(DIRECTORY
  launch
  urdf
  meshes
  worlds
  map
  rviz
  DESTINATION share/${PROJECT_NAME}
)

ament_package()