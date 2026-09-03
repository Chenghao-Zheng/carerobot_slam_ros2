#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2/utils.h>  // <- 新增此头文件
#include <cmath>
#include <algorithm>

static inline double wrap_to_pi(double a)
{
  while (a > M_PI) a -= 2.0 * M_PI;
  while (a < -M_PI) a += 2.0 * M_PI;
  return a;
}

static inline double clamp(double x, double lo, double hi)
{
  return std::max(lo, std::min(hi, x));
}

struct PID
{
  double kp{0}, ki{0}, kd{0};
  double i{0}, prev_e{0};
  double i_limit{1.0};

  double step(double e, double dt)
  {
    if (dt <= 1e-6) return kp * e;
    i += e * dt;
    i = clamp(i, -i_limit, i_limit);
    const double de = (e - prev_e) / dt;
    prev_e = e;
    return kp * e + ki * i + kd * de;
  }

  void reset()
  {
    i = 0;
    prev_e = 0;
  }
};

class DifferentialPIDLocalPlanner : public rclcpp::Node
{
public:
  DifferentialPIDLocalPlanner() : Node("differential_pid_local_planner")
  {
    declare_parameter("LOOKAHEAD_DIST", 0.5);
    declare_parameter("GOAL_TOL", 0.25);
    declare_parameter("MAX_VX", 0.4);
    declare_parameter("MAX_WZ", 0.8);
    declare_parameter("KP_X", 0.9);
    declare_parameter("KD_X", 0.0);
    declare_parameter("KP_YAW", 1.2);
    declare_parameter("KD_YAW", 0.0);
    declare_parameter("I_LIMIT_X", 0.6);
    declare_parameter("I_LIMIT_YAW", 1.0);
    declare_parameter("CMD_TIMEOUT", 0.5);
    declare_parameter("PUB_HZ", 30.0);
    declare_parameter("FILTER_ALPHA", 0.3);
    declare_parameter("LATERAL_GAIN", 0.5);
    declare_parameter("LATERAL_I_GAIN", 0.1);
    declare_parameter("LATERAL_I_LIMIT", 1.0);

    get_parameter("LOOKAHEAD_DIST", lookahead_dist_);
    get_parameter("GOAL_TOL", goal_tol_);
    get_parameter("MAX_VX", max_vx_);
    get_parameter("MAX_WZ", max_wz_);
    get_parameter("KP_X", pid_x_.kp);
    get_parameter("KD_X", pid_x_.kd);
    get_parameter("KP_YAW", pid_yaw_.kp);
    get_parameter("KD_YAW", pid_yaw_.kd);
    get_parameter("I_LIMIT_X", pid_x_.i_limit);
    get_parameter("I_LIMIT_YAW", pid_yaw_.i_limit);
    get_parameter("CMD_TIMEOUT", cmd_timeout_);
    get_parameter("PUB_HZ", pub_hz_);
    get_parameter("FILTER_ALPHA", filter_alpha_);
    get_parameter("LATERAL_GAIN", lateral_gain_);
    get_parameter("LATERAL_I_GAIN", lateral_i_gain_);
    get_parameter("LATERAL_I_LIMIT", lateral_i_limit_);

    path_sub_ = create_subscription<nav_msgs::msg::Path>(
      "/opt_path", 1, std::bind(&DifferentialPIDLocalPlanner::pathCb, this, std::placeholders::_1));
    odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
      "/odom", 1, std::bind(&DifferentialPIDLocalPlanner::odomCb, this, std::placeholders::_1));
    goal_sub_ = create_subscription<geometry_msgs::msg::PoseStamped>(
      "/move_base_simple/goal", 1, std::bind(&DifferentialPIDLocalPlanner::goalCb, this, std::placeholders::_1));

    cmd_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 1);
    local_path_pub_ = create_publisher<nav_msgs::msg::Path>("/local_path", 1);
    marker_pub_ = create_publisher<visualization_msgs::msg::Marker>("/local_goal", 1);

    last_cmd_time_ = rclcpp::Time(0);
    timer_ = create_wall_timer(
      std::chrono::duration<double>(1.0 / std::max(1.0, pub_hz_)),
      std::bind(&DifferentialPIDLocalPlanner::onTimer, this));

    RCLCPP_INFO(get_logger(), "DifferentialPIDLocalPlanner started. lookahead=%.2f, max_vx=%.2f, max_wz=%.2f",
                lookahead_dist_, max_vx_, max_wz_);
  }

private:
  void pathCb(const nav_msgs::msg::Path::SharedPtr msg)
  {
    path_ = *msg;
    has_path_ = !path_.poses.empty();
    lateral_i_ = 0.0;
  }

  void goalCb(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
  {
    goal_ = *msg;
    has_goal_ = true;
  }

void odomCb(const nav_msgs::msg::Odometry::SharedPtr msg)
  {
    x_ = msg->pose.pose.position.x;
    y_ = msg->pose.pose.position.y;
    tf2::Quaternion q(
      msg->pose.pose.orientation.x,
      msg->pose.pose.orientation.y,
      msg->pose.pose.orientation.z,
      msg->pose.pose.orientation.w);
      
    yaw_ = tf2::getYaw(q); // <- 将 tf2::impl::getYaw(q) 修改为 tf2::getYaw(q)
    has_odom_ = true;
  }

  bool computeLookaheadPoint(double& gx, double& gy, double& g_yaw_target)
  {
    if (!has_path_ || path_.poses.empty()) return false;

    int nearest = 0;
    double best_d2 = 1e100;
    for (size_t i = 0; i < path_.poses.size(); ++i)
    {
      double dx = path_.poses[i].pose.position.x - x_;
      double dy = path_.poses[i].pose.position.y - y_;
      double d2 = dx*dx + dy*dy;
      if (d2 < best_d2) { best_d2 = d2; nearest = i; }
    }

    double acc = 0.0;
    int idx = nearest;
    for (size_t i = nearest; i+1 < path_.poses.size(); ++i)
    {
      double x0 = path_.poses[i].pose.position.x;
      double y0 = path_.poses[i].pose.position.y;
      double x1 = path_.poses[i+1].pose.position.x;
      double y1 = path_.poses[i+1].pose.position.y;
      double seg = std::hypot(x1-x0, y1-y0);
      acc += seg;
      if (acc >= lookahead_dist_) { idx = i+1; break; }
      idx = i+1;
    }

    gx = path_.poses[idx].pose.position.x;
    gy = path_.poses[idx].pose.position.y;
    g_yaw_target = std::atan2(gy - y_, gx - x_);

    // 发布局部路径
    nav_msgs::msg::Path local;
    local.header = path_.header;
    for (int i = nearest; i <= idx; ++i)
      local.poses.push_back(path_.poses[i]);
    local_path_pub_->publish(local);

    // 发布目标点marker
    visualization_msgs::msg::Marker mk;
    mk.header = path_.header;
    mk.ns = "pid_local_goal";
    mk.id = 1;
    mk.type = visualization_msgs::msg::Marker::SPHERE;
    mk.action = visualization_msgs::msg::Marker::ADD;
    mk.pose.position.x = gx;
    mk.pose.position.y = gy;
    mk.pose.position.z = 0.1;
    mk.pose.orientation.w = 1.0;
    mk.scale.x = mk.scale.y = mk.scale.z = 0.18;
    mk.color.a = 1.0; mk.color.r = 1.0; mk.color.g = 0.8; mk.color.b = 0.0;
    marker_pub_->publish(mk);

    const auto& last = path_.poses.back().pose.position;
    double dist_goal = std::hypot(last.x - x_, last.y - y_);
    return (dist_goal > goal_tol_);
  }

  void publishZero()
  {
    geometry_msgs::msg::Twist z;
    cmd_pub_->publish(z);
  }

  void onTimer()
  {
    if (!has_odom_)
    {
      publishZero();
      return;
    }

    double gx, gy, yaw_target;
    if (!computeLookaheadPoint(gx, gy, yaw_target))
    {
      pid_x_.reset();
      pid_yaw_.reset();
      publishZero();
      return;
    }

    rclcpp::Time now = get_clock()->now();
    double dt = (last_cmd_time_.nanoseconds() == 0) ? (1.0 / std::max(1.0, pub_hz_))
                                                    : (now - last_cmd_time_).seconds();
    last_cmd_time_ = now;

    double dx = gx - x_;
    double dy = gy - y_;
    double cy = std::cos(yaw_);
    double sy = std::sin(yaw_);
    double ex =  cy*dx + sy*dy;
    double ey = -sy*dx + cy*dy;
    double e_yaw = wrap_to_pi(yaw_target - yaw_);

    double vx = pid_x_.step(ex, dt);
    double wz_angle = pid_yaw_.step(e_yaw, dt);
    double wz_lateral = lateral_gain_ * ey;

    lateral_i_ += ey * dt;
    lateral_i_ = clamp(lateral_i_, -lateral_i_limit_, lateral_i_limit_);
    wz_lateral += lateral_i_gain_ * lateral_i_;
    double wz = wz_angle + wz_lateral;

    cmd_vx_filtered_ = filter_alpha_ * vx + (1.0 - filter_alpha_) * cmd_vx_filtered_;
    cmd_wz_filtered_ = filter_alpha_ * wz + (1.0 - filter_alpha_) * cmd_wz_filtered_;
    vx = cmd_vx_filtered_;
    wz = cmd_wz_filtered_;

    vx = clamp(vx, -max_vx_, max_vx_);
    wz = clamp(wz, -max_wz_, max_wz_);

    geometry_msgs::msg::Twist cmd;
    cmd.linear.x = vx;
    cmd.angular.z = wz;
    cmd_pub_->publish(cmd);
  }

private:
  rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr path_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr local_path_pub_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Time last_cmd_time_;

  nav_msgs::msg::Path path_;
  geometry_msgs::msg::PoseStamped goal_;
  bool has_path_{false}, has_goal_{false}, has_odom_{false};

  double lookahead_dist_{0.6}, goal_tol_{0.25};
  double max_vx_{0.4}, max_wz_{0.8};
  double cmd_timeout_{0.5}, pub_hz_{30.0};
  double lateral_i_{0.0};
  double lateral_i_limit_{1.0};
  double lateral_i_gain_{0.0};

  double x_{0}, y_{0}, yaw_{0};
  PID pid_x_, pid_yaw_;

  double cmd_vx_filtered_{0.0}, cmd_wz_filtered_{0.0};
  double filter_alpha_{0.3};
  double lateral_gain_{0.5};
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<DifferentialPIDLocalPlanner>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}