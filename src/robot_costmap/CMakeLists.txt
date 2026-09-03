cmake_minimum_required(VERSION 3.8)
project(robot_costmap)

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# cmake 编译配置
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++17)

# 第三方库配置
set(THIRD_PART_LIBRARIES "")

include(cmake/eigen.cmake)

# ROS 2 依赖包配置
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(PCL REQUIRED) # 查找 PCL 库
find_package(robot_communication REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED) # 【新增】查找 OpenMP 库

# PCL 头文件路径引入
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# 1. 构建底层核心库
add_library(robot_costmap
  src/map_deal/edt_environment.cpp
  src/map_deal/grid_map_2d.cpp 
  src/map_deal/signed_distance_field_2d.cpp
  src/map_deal/global_map_deal.cpp
  src/map_deal/local_map_deal.cpp
)

target_include_directories(robot_costmap PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(robot_costmap
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  tf2
  tf2_ros
  pcl_conversions
  pcl_ros
  robot_communication
)

target_link_libraries(robot_costmap 
  OpenMP::OpenMP_CXX # 【新增】链接 OpenMP 库以解决符号未定义错误
  ${OpenCV_LIBS} 
  ${PCL_LIBRARIES} 
  ${THIRD_PART_LIBRARIES}
)

# 2. 构建可执行节点（精简重复文件）
add_executable(map_deal_node 
  src/nodes/map_deal_node.cpp 
  src/map_deal/map_deal.cpp
)

target_include_directories(map_deal_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

ament_target_dependencies(map_deal_node
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  tf2
  tf2_ros
  pcl_conversions
  pcl_ros
  robot_communication
)

# 直接链接打好的库 robot_costmap
target_link_libraries(map_deal_node 
  robot_costmap 
  ${OpenCV_LIBS} 
  ${PCL_LIBRARIES} 
  ${THIRD_PART_LIBRARIES}
)

# ========== 安装配置（关键修改位置） ==========
# 1. 头文件安装
install(
  DIRECTORY include/
  DESTINATION include
)

# 【新增】安装 launch 文件夹到 share/robot_costmap 目录下
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# 2. 核心库安装（仅对 C++ 库进行 EXPORT 导出）
install(
  TARGETS robot_costmap
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# 3. 可执行节点安装（独立安装，绝不加入 EXPORT）
install(
  TARGETS map_deal_node
  DESTINATION lib/${PROJECT_NAME}
)

# ========== 导出接口 ==========
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_include_directories(include)
ament_export_dependencies(
  rclcpp 
  std_msgs 
  sensor_msgs 
  geometry_msgs 
  nav_msgs 
  tf2 
  tf2_ros 
  pcl_conversions 
  pcl_ros 
  robot_communication
)

ament_package()