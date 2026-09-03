/*
 * ROS 2 motionPlan Node Entry Point (Fixed bad_weak_ptr)
 */
#include "motionPlan/motionPlan.h"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char **argv)
{
  // 1. 初始化 ROS 2 上下文
  rclcpp::init(argc, argv);

  // 2. 实例化 ROS 2 节点 (此时 shared_ptr 成功创建完毕)
  auto motionTest = std::make_shared<motionPlan>();

  // 3. 在 shared_ptr 建立后显式调用初始化函数！
  motionTest->motionInit();

  // 4. 开启单线程事件循环处理回调函数
  rclcpp::spin(motionTest);

  // 5. 关闭 ROS 2 节点
  rclcpp::shutdown();

  return 0;
}