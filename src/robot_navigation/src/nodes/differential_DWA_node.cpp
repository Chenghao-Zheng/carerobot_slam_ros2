#include <rclcpp/rclcpp.hpp>
#include "local_plan/differential_dwa.h"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Differential_DWAPlanner>();
  node->process();
  rclcpp::shutdown();
  return 0;
}