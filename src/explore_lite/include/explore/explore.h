#ifndef NAV_EXPLORE_H_
#define NAV_EXPLORE_H_

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <visualization_msgs/msg/marker_array.hpp>

#include <explore/costmap_client.h>
#include <explore/frontier_search.h>

namespace explore
{
class Explore : public rclcpp::Node
{
public:
  Explore();
  ~Explore();

  void start();
  void stop();

  // 公共初始化函数，必须在 spin() 之前调用
  void init();

private:
  void makePlan();
  void visualizeFrontiers(
      const std::vector<frontier_exploration::Frontier>& frontiers);

  bool goalOnBlacklist(const geometry_msgs::msg::Point& goal);

  // 内部初始化实现
  void initCostmapAndSearch();

  rclcpp::Time last_movement_time_;
  double movement_timeout_;
  bool has_ever_moved_;

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_array_publisher_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr goal_pub_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  std::unique_ptr<Costmap2DClient> costmap_client_;
  std::unique_ptr<frontier_exploration::FrontierSearch> search_;
  rclcpp::TimerBase::SharedPtr exploring_timer_;

  std::vector<geometry_msgs::msg::Point> frontier_blacklist_;
  geometry_msgs::msg::Point prev_goal_;
  double prev_distance_;
  rclcpp::Time last_progress_;
  size_t last_markers_count_;

  geometry_msgs::msg::PoseStamped current_goal_;
  double goal_tolerance_;

  double planner_frequency_;
  double potential_scale_, orientation_scale_, gain_scale_;
  double min_frontier_size_;
  rclcpp::Duration progress_timeout_;
  bool visualize_;
};
}  // namespace explore

#endif