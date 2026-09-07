#include <explore/costmap_client.h>

#include <array>
#include <functional>
#include <mutex>
#include <string>

#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace explore
{
// static translation table to speed things up
std::array<unsigned char, 256> init_translation_table();
static const std::array<unsigned char, 256> cost_translation_table__ =
    init_translation_table();

Costmap2DClient::Costmap2DClient(rclcpp::Node::SharedPtr node,
                                 const tf2_ros::Buffer* tf_buffer)
  : node_(node), tf_buffer_(tf_buffer)
{
  std::string costmap_topic;
  std::string costmap_updates_topic;

  node_->declare_parameter<std::string>("costmap_topic", "map");
  node_->declare_parameter<std::string>("costmap_updates_topic", "map_updates");
  node_->declare_parameter<std::string>("robot_base_frame", "base_link");
  node_->declare_parameter<double>("transform_tolerance", 0.3);

  node_->get_parameter("costmap_topic", costmap_topic);
  node_->get_parameter("costmap_updates_topic", costmap_updates_topic);
  node_->get_parameter("robot_base_frame", robot_base_frame_);
  node_->get_parameter("transform_tolerance", transform_tolerance_);

  /* initialize costmap subscription */
  costmap_sub_ = node_->create_subscription<nav_msgs::msg::OccupancyGrid>(
      costmap_topic, rclcpp::QoS(10).transient_local(),
      [this](const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
        updateFullMap(msg);
      });

  RCLCPP_INFO(node_->get_logger(), "Waiting for costmap to become available, topic: %s",
              costmap_topic.c_str());

  /* subscribe to map updates */
  costmap_updates_sub_ =
      node_->create_subscription<map_msgs::msg::OccupancyGridUpdate>(
          costmap_updates_topic, 10,
          [this](const map_msgs::msg::OccupancyGridUpdate::SharedPtr msg) {
            updatePartialMap(msg);
          });

  /* verify transform readiness */
  rclcpp::Time last_error = node_->now();
  std::string tf_error;
  while (rclcpp::ok() && global_frame_.empty()) {
    rclcpp::spin_some(node_);
    rclcpp::sleep_for(std::chrono::milliseconds(100));
    if (node_->now() - last_error > rclcpp::Duration::from_seconds(5.0)) {
      RCLCPP_WARN(
          node_->get_logger(),
          "Waiting for initial costmap message on topic %s...", costmap_topic.c_str());
      last_error = node_->now();
    }
  }
}

void Costmap2DClient::updateFullMap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
{
  global_frame_ = msg->header.frame_id;

  unsigned int size_in_cells_x = msg->info.width;
  unsigned int size_in_cells_y = msg->info.height;
  double resolution = msg->info.resolution;
  double origin_x = msg->info.origin.position.x;
  double origin_y = msg->info.origin.position.y;

  RCLCPP_DEBUG(node_->get_logger(), "received full new map, resizing to: %d, %d", size_in_cells_x,
               size_in_cells_y);
  costmap_.resizeMap(size_in_cells_x, size_in_cells_y, resolution, origin_x,
                     origin_y);

  // lock as we are accessing raw underlying map
  auto* mutex = costmap_.getMutex();
  std::lock_guard<nav2_costmap_2d::Costmap2D::mutex_t> lock(*mutex);

  // fill map with data
  unsigned char* costmap_data = costmap_.getCharMap();
  size_t costmap_size = costmap_.getSizeInCellsX() * costmap_.getSizeInCellsY();
  RCLCPP_DEBUG(node_->get_logger(), "full map update, %lu values", costmap_size);
  for (size_t i = 0; i < costmap_size && i < msg->data.size(); ++i) {
    unsigned char cell_cost = static_cast<unsigned char>(msg->data[i]);
    costmap_data[i] = cost_translation_table__[cell_cost];
  }
  RCLCPP_DEBUG(node_->get_logger(), "map updated, written %lu values", costmap_size);
}

void Costmap2DClient::updatePartialMap(
    const map_msgs::msg::OccupancyGridUpdate::SharedPtr msg)
{
  RCLCPP_DEBUG(node_->get_logger(), "received partial map update");
  global_frame_ = msg->header.frame_id;

  if (msg->x < 0 || msg->y < 0) {
    RCLCPP_ERROR(node_->get_logger(), "negative coordinates, invalid update. x: %d, y: %d", msg->x,
                 msg->y);
    return;
  }

  size_t x0 = static_cast<size_t>(msg->x);
  size_t y0 = static_cast<size_t>(msg->y);
  size_t xn = msg->width + x0;
  size_t yn = msg->height + y0;

  // lock as we are accessing raw underlying map
  auto* mutex = costmap_.getMutex();
  std::lock_guard<nav2_costmap_2d::Costmap2D::mutex_t> lock(*mutex);

  size_t costmap_xn = costmap_.getSizeInCellsX();
  size_t costmap_yn = costmap_.getSizeInCellsY();

  if (xn > costmap_xn || x0 > costmap_xn || yn > costmap_yn ||
      y0 > costmap_yn) {
    RCLCPP_WARN(node_->get_logger(),
                "received update doesn't fully fit into existing map, "
                "only part will be copied. received: [%lu, %lu], [%lu, %lu] "
                "map is: [0, %lu], [0, %lu]",
                x0, xn, y0, yn, costmap_xn, costmap_yn);
  }

  // update map with data
  unsigned char* costmap_data = costmap_.getCharMap();
  size_t i = 0;
  for (size_t y = y0; y < yn && y < costmap_yn; ++y) {
    for (size_t x = x0; x < xn && x < costmap_xn; ++x) {
      size_t idx = costmap_.getIndex(x, y);
      unsigned char cell_cost = static_cast<unsigned char>(msg->data[i]);
      costmap_data[idx] = cost_translation_table__[cell_cost];
      ++i;
    }
  }
}

geometry_msgs::msg::Pose Costmap2DClient::getRobotPose() const
{
  geometry_msgs::msg::PoseStamped global_pose;
  geometry_msgs::msg::PoseStamped robot_pose;
  robot_pose.header.frame_id = robot_base_frame_;
  robot_pose.header.stamp = node_->now();

  rclcpp::Time current_time = node_->now();

  try {
    auto transform = tf_buffer_->lookupTransform(
        global_frame_, robot_base_frame_, tf2::TimePointZero);
    tf2::doTransform(robot_pose, global_pose, transform);
  } catch (const tf2::TransformException& ex) {
    RCLCPP_ERROR_THROTTLE(node_->get_logger(), *node_->get_clock(), 1000,
                          "Error looking up robot pose from %s to %s: %s\n",
                          robot_base_frame_.c_str(), global_frame_.c_str(), ex.what());
    return geometry_msgs::msg::Pose();
  }

  // check global_pose timeout
  double pose_stamp = rclcpp::Time(global_pose.header.stamp).seconds();
  if (current_time.seconds() - pose_stamp > transform_tolerance_) {
    RCLCPP_WARN_THROTTLE(node_->get_logger(), *node_->get_clock(), 1000,
                         "Costmap2DClient transform timeout. Current time: "
                         "%.4f, global_pose stamp: %.4f, tolerance: %.4f",
                         current_time.seconds(), pose_stamp, transform_tolerance_);
    return geometry_msgs::msg::Pose();
  }

  return global_pose.pose;
}

std::array<unsigned char, 256> init_translation_table()
{
  std::array<unsigned char, 256> cost_translation_table;

  // linearly mapped from [0..100] to [0..255]
  for (size_t i = 0; i < 256; ++i) {
    cost_translation_table[i] =
        static_cast<unsigned char>(1 + (251 * (i - 1)) / 97);
  }

  // special values:
  cost_translation_table[0] = 0;      // NO obstacle
  cost_translation_table[99] = 253;   // INSCRIBED obstacle
  cost_translation_table[100] = 254;  // LETHAL obstacle
  cost_translation_table[static_cast<unsigned char>(-1)] = 255;  // UNKNOWN

  return cost_translation_table;
}

}  // namespace explore