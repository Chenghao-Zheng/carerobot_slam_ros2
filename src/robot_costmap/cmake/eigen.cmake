# 直接查找 Eigen3（ROS 2 中无需 cmake_modules）
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
add_definitions(${EIGEN_DEFINITIONS})