#include <explore/explore.h>

#include <algorithm>
#include <cmath>

namespace explore
{
Explore::Explore()
  : Node("explore")
  , prev_distance_(-1.0)
  , last_markers_count_(0)
  , progress_timeout_(rclcpp::Duration::from_seconds(30.0))
{
  double timeout;

  declare_parameter<double>("planner_frequency", 0.33);
  declare_parameter<double>("progress_timeout", 30.0);
  declare_parameter<double>("movement_timeout", 10.0);
  declare_parameter<bool>("visualize", false);
  declare_parameter<double>("potential_scale", 1e-3);
  declare_parameter<double>("orientation_scale", 0.0);
  declare_parameter<double>("gain_scale", 1.0);
  declare_parameter<double>("min_frontier_size", 0.3);
  declare_parameter<std::string>("goal_topic", "/goal_pose");
  declare_parameter<double>("goal_tolerance", 0.3);

  get_parameter("planner_frequency", planner_frequency_);
  get_parameter("progress_timeout", timeout);
  progress_timeout_ = rclcpp::Duration::from_seconds(timeout);
  get_parameter("movement_timeout", movement_timeout_);
  get_parameter("visualize", visualize_);
  get_parameter("potential_scale", potential_scale_);
  get_parameter("orientation_scale", orientation_scale_);
  get_parameter("gain_scale", gain_scale_);
  get_parameter("min_frontier_size", min_frontier_size_);

  std::string goal_topic;
  get_parameter("goal_topic", goal_topic);
  get_parameter("goal_tolerance", goal_tolerance_);

  goal_pub_ = create_publisher<geometry_msgs::msg::PoseStamped>(goal_topic, 10);

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  // 不在这里创建 costmap_client_ 和 search_

  if (visualize_) {
    marker_array_publisher_ =
        create_publisher<visualization_msgs::msg::MarkerArray>("frontiers", 10);
  } else {
    marker_array_publisher_ = nullptr;
  }

  last_progress_ = now();
  last_movement_time_ = now();
  has_ever_moved_ = false;

  auto period = std::chrono::duration<double>(1.0 / std::max(0.1, planner_frequency_));
  exploring_timer_ = create_wall_timer(
      std::chrono::duration_cast<std::chrono::nanoseconds>(period),
      std::bind(&Explore::makePlan, this));
}

Explore::~Explore()
{
  stop();
}

// 公共 init() 供外部调用
void Explore::init()
{
  initCostmapAndSearch();
}

void Explore::initCostmapAndSearch()
{
  if (costmap_client_) return;  // 防止重复初始化

  // 此时节点已被 shared_ptr 管理，但尚未加入执行器，安全
  costmap_client_ = std::make_unique<Costmap2DClient>(
      shared_from_this(), tf_buffer_.get());

  search_ = std::make_unique<frontier_exploration::FrontierSearch>(
      costmap_client_->getCostmap(),
      potential_scale_, gain_scale_,
      min_frontier_size_);
}

void Explore::visualizeFrontiers(
    const std::vector<frontier_exploration::Frontier>& frontiers)
{
  if (!marker_array_publisher_ || !costmap_client_) return;

  std_msgs::msg::ColorRGBA blue;
  blue.r = 0; blue.g = 0; blue.b = 1.0; blue.a = 1.0;

  std_msgs::msg::ColorRGBA red;
  red.r = 1.0; red.g = 0; red.b = 0; red.a = 1.0;

  std_msgs::msg::ColorRGBA green;
  green.r = 0; green.g = 1.0; green.b = 0; green.a = 1.0;

  visualization_msgs::msg::MarkerArray markers_msg;
  std::vector<visualization_msgs::msg::Marker>& markers = markers_msg.markers;
  visualization_msgs::msg::Marker m;

  m.header.frame_id = costmap_client_->getGlobalFrameID();
  m.header.stamp = now();
  m.ns = "frontiers";
  m.scale.x = 1.0; m.scale.y = 1.0; m.scale.z = 1.0;
  m.lifetime = rclcpp::Duration::from_seconds(0);
  m.frame_locked = true;

  double min_cost = frontiers.empty() ? 0. : frontiers.front().cost;

  m.action = visualization_msgs::msg::Marker::ADD;
  size_t id = 0;
  for (auto& frontier : frontiers) {
    m.type = visualization_msgs::msg::Marker::POINTS;
    m.id = static_cast<int>(id);
    m.pose.position = geometry_msgs::msg::Point();
    m.scale.x = 0.1; m.scale.y = 0.1; m.scale.z = 0.1;
    m.points = frontier.points;
    if (goalOnBlacklist(frontier.centroid)) {
      m.color = red;
    } else {
      m.color = blue;
    }
    markers.push_back(m);
    ++id;

    m.type = visualization_msgs::msg::Marker::SPHERE;
    m.id = static_cast<int>(id);
    m.pose.position = frontier.initial;
    double scale = std::min(std::abs(min_cost * 0.4 / (frontier.cost + 1e-5)), 0.5);
    m.scale.x = scale; m.scale.y = scale; m.scale.z = scale;
    m.points = {};
    m.color = green;
    markers.push_back(m);
    ++id;
  }
  size_t current_markers_count = markers.size();

  m.action = visualization_msgs::msg::Marker::DELETE;
  for (; id < last_markers_count_; ++id) {
    m.id = static_cast<int>(id);
    markers.push_back(m);
  }

  last_markers_count_ = current_markers_count;
  marker_array_publisher_->publish(markers_msg);
}

void Explore::makePlan()
{
  // 必须确保已经初始化，否则报错返回
  if (!costmap_client_ || !search_) {
    RCLCPP_ERROR(get_logger(), "costmap_client_ not initialized! Call init() before spin.");
    return;
  }

  auto pose = costmap_client_->getRobotPose();

  // ---------- 检查当前目标状态 ----------
  if (!current_goal_.header.frame_id.empty()) {
    double dx = pose.position.x - current_goal_.pose.position.x;
    double dy = pose.position.y - current_goal_.pose.position.y;
    double dist = std::hypot(dx, dy);

    bool is_goal_reached = false;
    if (dist <= goal_tolerance_) {
      is_goal_reached = true;
      RCLCPP_INFO(get_logger(), "Goal reached (distance %.2f <= %.2f)", dist, goal_tolerance_);
    } else {
      if (prev_distance_ < 0) {
        prev_distance_ = dist;
      } else {
        double dist_change = prev_distance_ - dist;
        prev_distance_ = dist;

        if (dist_change < 0.01) {
          if (now() - last_movement_time_ > rclcpp::Duration::from_seconds(movement_timeout_)) {
            RCLCPP_WARN(get_logger(), "Robot stuck (no movement) for %.2f sec, abandoning goal", movement_timeout_);
            frontier_blacklist_.push_back(current_goal_.pose.position);
            current_goal_.header.frame_id = "";
            is_goal_reached = true;
          }
        } else {
          last_movement_time_ = now();
        }
      }
    }

    if (is_goal_reached) {
      current_goal_.header.frame_id = "";
      prev_distance_ = -1.0;
      RCLCPP_INFO(get_logger(), "Goal cleared, searching for new frontier.");
    } else {
      if (now() - last_progress_ > progress_timeout_) {
        frontier_blacklist_.push_back(current_goal_.pose.position);
        current_goal_.header.frame_id = "";
        prev_distance_ = -1.0;
        RCLCPP_WARN(get_logger(), "Goal timed out, blacklisting and clearing.");
      } else {
        return; // 还在导航中，继续执行
      }
    }
  }

  // ---------- 无当前目标，执行前沿搜索 ----------
  auto frontiers = search_->searchFrom(pose.position);

  if (frontiers.empty()) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "No frontiers found, retrying...");
    return;
  }

  if (visualize_ && marker_array_publisher_) {
    visualizeFrontiers(frontiers);
  }

  auto frontier =
      std::find_if_not(frontiers.begin(), frontiers.end(),
                       [this](const frontier_exploration::Frontier& f) {
                         return goalOnBlacklist(f.centroid);
                       });
  if (frontier == frontiers.end()) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "All frontiers blacklisted, clearing blacklist.");
    frontier_blacklist_.clear();
    frontier = frontiers.begin();
    if (frontier == frontiers.end()) {
      return;
    }
  }
  geometry_msgs::msg::Point target_position = frontier->centroid;

  geometry_msgs::msg::PoseStamped goal_msg;
  goal_msg.header.frame_id = costmap_client_->getGlobalFrameID();
  goal_msg.header.stamp = now();
  goal_msg.pose.position = target_position;
  goal_msg.pose.orientation.w = 1.0;

  current_goal_ = goal_msg;
  last_progress_ = now();
  last_movement_time_ = now();

  goal_pub_->publish(goal_msg);
  RCLCPP_INFO(get_logger(), "Published frontier goal to motionPlan: (%.2f, %.2f)", target_position.x, target_position.y);
}

bool Explore::goalOnBlacklist(const geometry_msgs::msg::Point& goal)
{
  constexpr static size_t tolerance = 5;
  const nav2_costmap_2d::Costmap2D* costmap2d = costmap_client_->getCostmap();

  for (auto& frontier_goal : frontier_blacklist_) {
    double x_diff = std::fabs(goal.x - frontier_goal.x);
    double y_diff = std::fabs(goal.y - frontier_goal.y);

    if (x_diff < tolerance * costmap2d->getResolution() &&
        y_diff < tolerance * costmap2d->getResolution())
      return true;
  }
  return false;
}

void Explore::start()
{
}

void Explore::stop()
{
  current_goal_.header.frame_id = "";
  if (exploring_timer_) {
    exploring_timer_->cancel();
  }
  RCLCPP_INFO(get_logger(), "Exploration stopped.");
}

}  // namespace explore

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<explore::Explore>();
  // 关键：在 spin 之前调用 init()
  node->init();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}