cmake_minimum_required(VERSION 3.8)
project(read_laser_data)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找 ROS 2 依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(laser_geometry REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED COMPONENTS common filters)
find_package(Eigen3 REQUIRED)

# 包含头文件路径
include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

# 编译 C++ 节点 executable
add_executable(merger_node src/laser_scan_merge.cpp)

# 链接依赖库
target_link_libraries(merger_node
  ${PCL_LIBRARIES}
)

# 声明 ROS 2 接口依赖
ament_target_dependencies(merger_node
  rclcpp
  sensor_msgs
  laser_geometry
  pcl_conversions
)

# 安装可执行文件到 lib/read_laser_data
install(TARGETS
  merger_node
  DESTINATION lib/${PROJECT_NAME}
)

# 安装 launch 文件
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()