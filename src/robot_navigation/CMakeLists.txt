cmake_minimum_required(VERSION 3.8)
project(robot_navigation)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ========== 编译选项 ==========
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========== ROS 2 & 系统依赖 ==========
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(glog REQUIRED)
find_package(OsqpEigen REQUIRED)
find_package(angles REQUIRED)
find_package(nav2_costmap_2d REQUIRED)
find_package(OpenMP REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(NLOPT REQUIRED nlopt)

# 自定义功能包依赖
find_package(robot_communication REQUIRED)
find_package(robot_costmap REQUIRED)

# ========== 包含目录 ==========
include_directories(
  include
  ${EIGEN3_INCLUDE_DIR}
  ${robot_costmap_INCLUDE_DIRS}
  ${robot_communication_INCLUDE_DIRS}
  ${NLOPT_INCLUDE_DIRS}
  /usr/local/include/OsqpEigen
  /usr/local/include/osqp
)

# ========== 获取源文件列表 ==========
file(GLOB_RECURSE ALL_SRCS "src/*.cpp")
file(GLOB_RECURSE NODE_SRCS "src/nodes/*_node.cpp")
if(NODE_SRCS)
  list(REMOVE_ITEM ALL_SRCS ${NODE_SRCS})
endif()

# ========== 编译节点 (motionPlan_node) ==========
add_executable(motionPlan_node 
  src/nodes/motionPlan_node.cpp 
  ${ALL_SRCS}
)
ament_target_dependencies(motionPlan_node
  rclcpp
  geometry_msgs
  nav_msgs
  sensor_msgs
  std_msgs
  visualization_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  tf2_sensor_msgs
  pcl_conversions
  angles
  nav2_costmap_2d
  robot_communication
  robot_costmap
)
target_link_libraries(motionPlan_node
  ${OpenCV_LIBS}
  ${NLOPT_LIBRARIES}
  tf2_geometry_msgs::tf2_geometry_msgs
  glog::glog
  OsqpEigen::OsqpEigen
  osqp
)

# ========== 编译节点 (Differential_DWA_node) ==========
add_executable(Differential_DWA_node 
  src/nodes/differential_DWA_node.cpp 
  ${ALL_SRCS}
)
ament_target_dependencies(Differential_DWA_node
  rclcpp
  geometry_msgs
  nav_msgs
  sensor_msgs
  std_msgs
  visualization_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  tf2_sensor_msgs
  pcl_conversions
  angles
  nav2_costmap_2d
  robot_communication
  robot_costmap
)
target_link_libraries(Differential_DWA_node
  ${OpenCV_LIBS}
  ${NLOPT_LIBRARIES}
  tf2_geometry_msgs::tf2_geometry_msgs
  glog::glog
  OsqpEigen::OsqpEigen
  osqp
)

# ========== 安装规则 ==========
install(TARGETS
  motionPlan_node
  Differential_DWA_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include/
  DESTINATION include/
)

install(DIRECTORY
  config launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()