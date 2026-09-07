cmake_minimum_required(VERSION 3.8)
project(keyboard_control)

if(NOT CMAKE_COMPILER_IS_GNUCXX AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(include)

# 编译 C++ 可执行文件
add_executable(keyboard_control src/keyboard_control.cpp)
ament_target_dependencies(keyboard_control
  rclcpp
  geometry_msgs
)

# 安装可执行文件到 lib/keyboard_control 路径
install(TARGETS keyboard_control
  DESTINATION lib/${PROJECT_NAME}
)

# 安装 launch 文件夹
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()