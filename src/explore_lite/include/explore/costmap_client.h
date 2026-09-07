#ifndef COSTMAP_CLIENT_
#define COSTMAP_CLIENT_

#include <memory>
#include <string>

#include <geometry_msgs/msg/pose.hpp>
#include <map_msgs/msg/occupancy_grid_update.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

namespace explore
{
class Costmap2DClient
{
public:
  Costmap2DClient(rclcpp::Node::SharedPtr node,
                  const tf2_ros::Buffer* tf_buffer);

  geometry_msgs::msg::Pose getRobotPose() const;

  nav2_costmap_2d::Costmap2D* getCostmap()
  {
    return &costmap_;
  }

  const nav2_costmap_2d::Costmap2D* getCostmap() const
  {
    return &costmap_;
  }

  const std::string& getGlobalFrameID() const
  {
    return global_frame_;
  }

  const std::string& getBaseFrameID() const
  {
    return robot_base_frame_;
  }

protected:
  void updateFullMap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);
  void updatePartialMap(const map_msgs::msg::OccupancyGridUpdate::SharedPtr msg);

  nav2_costmap_2d::Costmap2D costmap_;
  rclcpp::Node::SharedPtr node_;

  const tf2_ros::Buffer* const tf_buffer_;
  std::string global_frame_;
  std::string robot_base_frame_;
  double transform_tolerance_;

private:
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr costmap_sub_;
  rclcpp::Subscription<map_msgs::msg::OccupancyGridUpdate>::SharedPtr costmap_updates_sub_;
};

}  // namespace explore

#endif