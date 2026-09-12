#include "local_plan/differential_dwa.h"
#include <angles/angles.h>
#include <limits>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

// ========== State 和 Window 构造函数实现 ==========
Differential_DWAPlanner::State::State(double _x, double _y, double _yaw, double _velocity, double _yawrate)
    : x(_x), y(_y), yaw(_yaw), velocity(_velocity), yawrate(_yawrate) {}

Differential_DWAPlanner::Window::Window(void)
    : min_velocity(0.0), max_velocity(0.0), min_yawrate(0.0), max_yawrate(0.0) {}

Differential_DWAPlanner::Window::Window(const double min_v, const double max_v, const double min_y, const double max_y)
    : min_velocity(min_v), max_velocity(max_v), min_yawrate(min_y), max_yawrate(max_y) {}

// ------------------------------------------------------------
// 构造函数
// ------------------------------------------------------------
Differential_DWAPlanner::Differential_DWAPlanner()
    : Node("dwa_planner"),
      odom_updated(false),
      local_goal_subscribed(false),
      local_map_updated(false),
      scan_updated(false),
      current_path_index_(0),
      final_reached_(false)
{
  HZ = this->declare_parameter<double>("HZ", 20.0);
  ROBOT_FRAME = this->declare_parameter<std::string>("ROBOT_FRAME", "base_link");
  TARGET_VELOCITY = this->declare_parameter<double>("TARGET_VELOCITY", 0.6);
  MAX_VELOCITY = this->declare_parameter<double>("MAX_VELOCITY", 0.8);
  MIN_VELOCITY = this->declare_parameter<double>("MIN_VELOCITY", 0.0);
  MAX_YAWRATE = this->declare_parameter<double>("MAX_YAWRATE", 1.2);
  MAX_ACCELERATION = this->declare_parameter<double>("MAX_ACCELERATION", 0.8);
  MAX_D_YAWRATE = this->declare_parameter<double>("MAX_D_YAWRATE", 2.5);
  MAX_DIST = this->declare_parameter<double>("MAX_DIST", 5.0);
  VELOCITY_RESOLUTION = this->declare_parameter<double>("VELOCITY_RESOLUTION", 0.05);
  YAWRATE_RESOLUTION = this->declare_parameter<double>("YAWRATE_RESOLUTION", 0.05);
  ANGLE_RESOLUTION = this->declare_parameter<double>("ANGLE_RESOLUTION", 0.0087);
  PREDICT_TIME = this->declare_parameter<double>("PREDICT_TIME", 2.0);
  TO_GOAL_COST_GAIN = this->declare_parameter<double>("TO_GOAL_COST_GAIN", 1.0);
  SPEED_COST_GAIN = this->declare_parameter<double>("SPEED_COST_GAIN", 1.0);
  OBSTACLE_COST_GAIN = this->declare_parameter<double>("OBSTACLE_COST_GAIN", 1.0);
  GOAL_THRESHOLD = this->declare_parameter<double>("GOAL_THRESHOLD", 0.15);
  TURN_DIRECTION_THRESHOLD = this->declare_parameter<double>("TURN_DIRECTION_THRESHOLD", 0.1);
  TEMP_GOAL_RADIUS = this->declare_parameter<double>("TEMP_GOAL_RADIUS", 1.5);
  ROBOT_RADIUS = this->declare_parameter<double>("ROBOT_RADIUS", 0.265);
  SAFETY_MARGIN = this->declare_parameter<double>("SAFETY_MARGIN", 0.05);
  laser_max_range_ = this->declare_parameter<double>("LASER_MAX_RANGE", 3.0);
  LOOKAHEAD_DIST = this->declare_parameter<double>("LOOKAHEAD_DIST", 0.65);

  DT = 1.0 / HZ;

  candidate_trajectories_pub = this->create_publisher<visualization_msgs::msg::MarkerArray>("candidate_trajectories", 1);
  selected_trajectory_pub = this->create_publisher<visualization_msgs::msg::Marker>("selected_trajectory", 1);
  localPathPub = this->create_publisher<nav_msgs::msg::Path>("/local_path", 1);
  chassCtlPub = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel_auto", 1);
  localgoalPub = this->create_publisher<visualization_msgs::msg::Marker>("/local_goal_vis", 10);

  local_goal_sub = this->create_subscription<robot_communication::msg::Goal>(
      "/local_goal", 1, std::bind(&Differential_DWAPlanner::local_goal_callback, this, std::placeholders::_1));
  local_map_sub = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
      "/local_map_inflate", 1, std::bind(&Differential_DWAPlanner::local_map_callback, this, std::placeholders::_1));
  odom_sub = this->create_subscription<nav_msgs::msg::Odometry>(
      "/carto_odom", 1, std::bind(&Differential_DWAPlanner::odom_callback, this, std::placeholders::_1));
  target_velocity_sub = this->create_subscription<geometry_msgs::msg::Twist>(
      "/velocity_control", 1, std::bind(&Differential_DWAPlanner::target_velocity_callback, this, std::placeholders::_1));
  pathSub = this->create_subscription<nav_msgs::msg::Path>(
      "/opt_path", 10, std::bind(&Differential_DWAPlanner::pathCallback, this, std::placeholders::_1));
  scan_sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/scan", 1, std::bind(&Differential_DWAPlanner::scan_callback, this, std::placeholders::_1));

  pidFollow.Init();
  anglePID[0] = 10.0; anglePID[1] = 0.0; anglePID[2] = 0.0; anglePID[3] = 3.0; anglePID[4] = -3.0; anglePID[5] = 0.05;
  pidFollow.SetPIDParameter(&pidFollow.gyro_pid, anglePID);

  RCLCPP_INFO(this->get_logger(), "DWA local planner (ROS2 with min-distance goal cost) started.");
}

void Differential_DWAPlanner::local_goal_callback(const robot_communication::msg::Goal::SharedPtr msg) {
  local_goal = *msg;
  local_goal_subscribed = true;
}

void Differential_DWAPlanner::local_map_callback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg) {
  local_map = *msg;
  local_map_updated = true;
  map_origin_x_ = msg->info.origin.position.x;
  map_origin_y_ = msg->info.origin.position.y;
}

void Differential_DWAPlanner::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
  current_velocity = msg->twist.twist;
  nowposition[0] = msg->pose.pose.position.x;
  nowposition[1] = msg->pose.pose.position.y;
  nowposition[2] = tf2::getYaw(msg->pose.pose.orientation);
  odom_updated = true;
}

void Differential_DWAPlanner::target_velocity_callback(const geometry_msgs::msg::Twist::SharedPtr msg) {
  TARGET_VELOCITY = sqrt(msg->linear.x * msg->linear.x + msg->linear.y * msg->linear.y);
}

void Differential_DWAPlanner::scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg) {
  scan_points_.clear();
  double range_min = msg->range_min;
  for (size_t i = 0; i < msg->ranges.size(); ++i) {
    double r = msg->ranges[i];
    if (!std::isfinite(r) || r < range_min || r > laser_max_range_) continue;
    if (r < ROBOT_RADIUS) continue;

    double angle = msg->angle_min + i * msg->angle_increment;
    scan_points_.push_back({r * cos(angle), r * sin(angle)});
  }
  scan_updated = true;
}

void Differential_DWAPlanner::pathCallback(const nav_msgs::msg::Path::SharedPtr path) {
  nav_msgs::msg::Path tempath = *path;
  int new_size = tempath.poses.size();
  if (new_size <= 0) {
    RCLCPP_WARN(this->get_logger(), "Received empty path, ignoring.");
    return;
  }

  bool path_updated = (new_size != last_path_nodes_num);
  if (!path_updated && new_size == last_path_nodes_num) {
    Vector2d new_end(tempath.poses.back().pose.position.x, tempath.poses.back().pose.position.y);
    if (trajpath.size() > 0 && calPointLength(trajpath.back(), new_end) > 0.1) {
      path_updated = true;
    }
  }

  if (path_updated) {
    trajpath.clear();
    visitPath.clear();
    for (int i = 0; i < new_size; ++i) {
      Vector2d pt(tempath.poses[i].pose.position.x, tempath.poses[i].pose.position.y);
      trajpath.push_back(pt);
      visitPath.push_back({0, pt});
    }
    current_path_index_ = 0;
    final_reached_ = false;
    last_path_nodes_num = new_size;
    compute_lookahead_target(nowposition[0], nowposition[1],
                             localposition[0], localposition[1], localposition[2]);
    local_goal_subscribed = true;
    return;
  }

  if (!trajpath.empty()) {
    update_path_index(nowposition[0], nowposition[1]);
    compute_lookahead_target(nowposition[0], nowposition[1],
                             localposition[0], localposition[1], localposition[2]);
    local_goal_subscribed = true;
  }
}

void Differential_DWAPlanner::update_path_index(double rx, double ry) {
  if (trajpath.empty() || current_path_index_ >= (int)trajpath.size() - 1) return;

  const int max_steps = 20;
  for (int step = 0; step < max_steps; ++step) {
    if (current_path_index_ >= (int)trajpath.size() - 1) break;
    int idx = current_path_index_;
    double x0 = trajpath[idx][0], y0 = trajpath[idx][1];
    double x1 = trajpath[idx + 1][0], y1 = trajpath[idx + 1][1];
    double sx = x1 - x0, sy = y1 - y0;
    double len_sq = sx * sx + sy * sy;
    if (len_sq < 1e-9) {
      current_path_index_++;
      continue;
    }
    double proj = ((rx - x0) * sx + (ry - y0) * sy) / len_sq;
    double dist_to_next = hypot(rx - x1, ry - y1);
    double dist_to_curr = hypot(rx - x0, ry - y0);
    if (proj >= 0.5 || dist_to_next < dist_to_curr || dist_to_next < 0.09) {
      current_path_index_++;
    } else {
      break;
    }
  }
}

void Differential_DWAPlanner::compute_lookahead_target(double rx, double ry,
                                                       double &gx, double &gy, double &g_yaw) {
  if (trajpath.empty()) {
    gx = rx; gy = ry; g_yaw = nowposition[2];
    return;
  }

  int start_idx = std::min(current_path_index_, (int)trajpath.size() - 1);
  double accumulated = 0.0;
  int target_idx = start_idx;
  double current_speed = fabs(current_velocity.linear.x);
  double lookahead = LOOKAHEAD_DIST + 0.5 * current_speed;
  lookahead = std::max(0.3, std::min(lookahead, TEMP_GOAL_RADIUS));

  for (int i = start_idx; i < (int)trajpath.size() - 1; ++i) {
    double seg = hypot(trajpath[i + 1][0] - trajpath[i][0],
                       trajpath[i + 1][1] - trajpath[i][1]);
    if (accumulated + seg >= lookahead) {
      target_idx = i + 1;
      break;
    }
    accumulated += seg;
    target_idx = i + 1;
  }
  target_idx = std::min(target_idx, (int)trajpath.size() - 1);
  gx = trajpath[target_idx][0];
  gy = trajpath[target_idx][1];
  if (target_idx < (int)trajpath.size() - 1) {
    double dx = trajpath[target_idx + 1][0] - trajpath[target_idx][0];
    double dy = trajpath[target_idx + 1][1] - trajpath[target_idx][1];
    g_yaw = atan2(dy, dx);
  } else {
    g_yaw = atan2(gy - ry, gx - rx);
  }
  double dist_to_final = hypot(trajpath.back()[0] - rx, trajpath.back()[1] - ry);
  if (dist_to_final < GOAL_THRESHOLD || target_idx == (int)trajpath.size() - 1) {
    if (!final_reached_) {
      final_reached_ = true;
      final_goal_ = trajpath.back();
      if (trajpath.size() >= 2) {
        Vector2d last_dir = trajpath.back() - trajpath[trajpath.size() - 2];
        goal_yaw_ = atan2(last_dir[1], last_dir[0]);
      } else {
        goal_yaw_ = atan2(final_goal_[1] - ry, final_goal_[0] - rx);
      }
    }
    gx = final_goal_[0];
    gy = final_goal_[1];
    g_yaw = goal_yaw_;
  }
}

Differential_DWAPlanner::Window Differential_DWAPlanner::calc_dynamic_window(const geometry_msgs::msg::Twist &cur_velocity) {
  Window window(MIN_VELOCITY, MAX_VELOCITY, -MAX_YAWRATE, MAX_YAWRATE);
  double eval_dt = 0.4;
  double accel_v = MAX_ACCELERATION * eval_dt;
  double accel_w = MAX_D_YAWRATE * eval_dt;

  window.min_velocity = std::max(cur_velocity.linear.x - accel_v, MIN_VELOCITY);
  if (window.min_velocity < 0.0) window.min_velocity = 0.0;
  window.max_velocity = std::min(cur_velocity.linear.x + accel_v, MAX_VELOCITY);
  window.min_yawrate = std::max(cur_velocity.angular.z - accel_w, -MAX_YAWRATE);
  window.max_yawrate = std::min(cur_velocity.angular.z + accel_w, MAX_YAWRATE);
  return window;
}

// ============================================================
// ★★★ 核心修复 1：用"轨迹上到目标的最小距离"替换"末端距离" ★★★
// 关键：轨迹经过目标就算距离为 0，不再惩罚"过冲"
// 彻底解决 PREDICT_TIME 大时机器人走慢的问题
// 参考 dwa_planner.cpp 里 cal_to_goal_cost 的思路
// ============================================================
float Differential_DWAPlanner::calc_to_goal_cost(const std::vector<State> &traj, const Eigen::Vector3d &goal) {
  float min_dist = 1e6f;
  for (const auto &state : traj) {
    float d = hypot(goal[0] - state.x, goal[1] - state.y);
    if (d < min_dist) min_dist = d;
  }
  return min_dist;
}

float Differential_DWAPlanner::calc_speed_cost(const std::vector<State> &traj, const float target_velocity) {
  // 与参考代码一致，用轨迹起点速度
  return fabs(target_velocity - traj.front().velocity);
}

// ============================================================
// ★★★ 核心修复 2：线性避障代价 + 只在真实穿透时硬拒绝 ★★★
// 参考 dwa_planner.cpp 里 cal_obs_cost 的公式
// ============================================================
float Differential_DWAPlanner::calc_obstacle_cost(std::vector<State> &traj,
                                                  const std::vector<std::pair<double,double>> &scan_points) {
  if (scan_points.empty()) return 0.0f;

  float min_dist = 1e6f;
  for (const auto &state : traj) {
    for (const auto &pt : scan_points) {
      // 减去机器人半径，得到"车体边缘到障碍物"的净距离
      float dist = hypot(state.x - pt.first, state.y - pt.second) - ROBOT_RADIUS;
      if (dist < min_dist) min_dist = dist;
    }
  }

  // 真实穿透：障碍物进入车体内部，硬拒绝
  if (min_dist < 0.0f) return 1e6f;

  // 否则：离障碍物越近代价越高，线性增长，范围 [0, laser_max_range_]
  return laser_max_range_ - min_dist;
}

void Differential_DWAPlanner::motion(State &state, const double velocity, const double yawrate) {
  state.yaw += yawrate * DT;
  state.x += velocity * cos(state.yaw) * DT;
  state.y += velocity * sin(state.yaw) * DT;
  state.velocity = velocity;
  state.yawrate = yawrate;
}

// ============================================================
// ★★★ 核心修复 3：恢复碰撞丢弃（配合新避障代价的 1e6 返回） ★★★
// ============================================================
std::vector<Differential_DWAPlanner::State>
Differential_DWAPlanner::dwa_planning(Window dynamic_window,
                                      Eigen::Vector3d goal,
                                      const std::vector<std::pair<double,double>> &scan_points,
                                      double target_velocity) {
  float min_cost = 1e6;
  std::vector<State> best_traj;

  double min_v_sample = std::max(dynamic_window.min_velocity, 0.1);

  for (double v = min_v_sample; v <= dynamic_window.max_velocity; v += VELOCITY_RESOLUTION) {
    for (double w = dynamic_window.min_yawrate; w <= dynamic_window.max_yawrate; w += YAWRATE_RESOLUTION) {
      State state(0.0, 0.0, 0.0, current_velocity.linear.x, current_velocity.angular.z);
      std::vector<State> traj;
      for (double t = 0; t <= PREDICT_TIME; t += DT) {
        motion(state, v, w);
        traj.push_back(state);
      }

      float to_goal = calc_to_goal_cost(traj, goal);
      float speed = calc_speed_cost(traj, target_velocity);
      float obstacle = calc_obstacle_cost(traj, scan_points);

      // 真实穿透 → 丢弃
      if (obstacle >= 1e5f) continue;

      float final_cost = TO_GOAL_COST_GAIN * to_goal
                       + SPEED_COST_GAIN * speed
                       + OBSTACLE_COST_GAIN * obstacle;

      if (final_cost < min_cost) {
        min_cost = final_cost;
        best_traj = traj;
      }
    }
  }

  if (best_traj.empty()) {
    State state(0.0, 0.0, 0.0, 0.1, 0.0);
    best_traj.push_back(state);
    RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                         "No valid trajectory found, using default speed 0.1 m/s!");
  }
  return best_traj;
}

// ============================================================
// process()：每周期推进路径索引 + 前瞻点可视化 + 剩余路径减速
// ============================================================
void Differential_DWAPlanner::process(void) {
  rclcpp::Rate loop_rate(HZ);

  static bool rotating_mode = false;
  static int stuck_counter = 0;

  const double ANGLE_A = 1.0;
  const double ANGLE_B = 0.15;
  const int STUCK_THRESHOLD = 20;
  const int STUCK_MAX = 60;

  while (rclcpp::ok()) {
    if (!local_goal_subscribed && !trajpath.empty()) {
        local_goal_subscribed = true;
    }

    // 每周期推进路径索引 + 前瞻点可视化
    if (!trajpath.empty()) {
      update_path_index(nowposition[0], nowposition[1]);
      compute_lookahead_target(nowposition[0], nowposition[1],
                               localposition[0], localposition[1], localposition[2]);

      std::vector<Vector2d> tempvec = {Vector2d(localposition[0], localposition[1])};
      visual_VisitedNode(localgoalPub, tempvec, 1.0, 0.0, 1.0, 0.5, 5.0);
    }

    if (local_map_updated && local_goal_subscribed && odom_updated && scan_updated) {
      Window dynamic_window = calc_dynamic_window(current_velocity);

      double cos_yaw = cos(nowposition[2]);
      double sin_yaw = sin(nowposition[2]);
      double dx = localposition[0] - nowposition[0];
      double dy = localposition[1] - nowposition[1];
      double local_goal_x =  dx * cos_yaw + dy * sin_yaw;
      double local_goal_y = -dx * sin_yaw + dy * cos_yaw;
      double local_goal_yaw = atan2(local_goal_y, local_goal_x);

      Eigen::Vector3d goal(local_goal_x, local_goal_y, local_goal_yaw);
      double dist_to_goal = hypot(goal[0], goal[1]);
      double angle_error = fabs(local_goal_yaw);

      // ★ 修复：remaining_path_dist 提到最外层作用域 ★
      double remaining_path_dist = 0.0;
      if (!trajpath.empty()) {
        int end_idx = (int)trajpath.size() - 1;
        for (int i = current_path_index_; i < end_idx; ++i) {
          remaining_path_dist += hypot(trajpath[i + 1][0] - trajpath[i][0],
                                        trajpath[i + 1][1] - trajpath[i][1]);
          if (remaining_path_dist > 2.0) break;
        }
      }

      // 检查"到局部目标方向"是否被障碍物堵住
      bool path_to_goal_blocked = false;
      for (const auto &pt : scan_points_) {
        double pt_angle = atan2(pt.second, pt.first);
        double pt_dist  = hypot(pt.first, pt.second);
        double ang_diff = fabs(angles::shortest_angular_distance(pt_angle, local_goal_yaw));
        if (ang_diff < 0.7 && pt_dist < 1.2) {
          path_to_goal_blocked = true;
          break;
        }
      }

      if (angle_error > ANGLE_A && dist_to_goal > 0.5 && !path_to_goal_blocked) {
        rotating_mode = true;
      } else if (angle_error < ANGLE_B || dist_to_goal <= 0.1 || path_to_goal_blocked) {
        rotating_mode = false;
      }

      geometry_msgs::msg::Twist cmd_vel;

      if (dist_to_goal < GOAL_THRESHOLD && !rotating_mode) {
        cmd_vel.linear.x = 0.0;
        if (fabs(local_goal_yaw) < 0.1) cmd_vel.angular.z = 0.0;
        else cmd_vel.angular.z = std::min(std::max(local_goal_yaw * 1.2, -MAX_YAWRATE), MAX_YAWRATE);
        stuck_counter = 0;
      }
      else if (rotating_mode) {
        cmd_vel.linear.x = 0.0;
        cmd_vel.angular.z = std::min(std::max(local_goal_yaw * 1.5, -MAX_YAWRATE), MAX_YAWRATE);
        stuck_counter = 0;
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
            "Hysteresis rotating, angle_error=%.3f", angle_error);
      }
      else if (stuck_counter > STUCK_THRESHOLD) {
        cmd_vel.linear.x = 0.0;
        double turn_dir = (local_goal_yaw > 0.05) ? 1.0
                        : ((local_goal_yaw < -0.05) ? -1.0 : 1.0);
        cmd_vel.angular.z = turn_dir * MAX_YAWRATE * 0.6;
        stuck_counter++;
        if (stuck_counter > STUCK_MAX) stuck_counter = 0;
        RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 500,
            "Escape rotation, stuck=%d", stuck_counter);
      }
      else {
        // 正常 DWA 规划
        double current_target_vel = TARGET_VELOCITY;

        // 剩余路径长度过短 → 减速，准备等待新目标
        if (remaining_path_dist < 0.3) {
          current_target_vel = std::min(current_target_vel, 0.15);
        }

        // 接近局部目标时也减速
        if (dist_to_goal < 0.5) {
          current_target_vel = std::min(current_target_vel, 0.1 + 0.5 * (dist_to_goal / 0.5));
        }
        dynamic_window.max_velocity = std::min(dynamic_window.max_velocity,
                                               std::max(current_target_vel, 0.1));

        std::vector<State> best_traj = dwa_planning(dynamic_window, goal, scan_points_, current_target_vel);
        if (!best_traj.empty()) {
          cmd_vel.linear.x = best_traj.back().velocity;
          cmd_vel.angular.z = best_traj.back().yawrate;
          visualize_trajectory(best_traj, 1.0, 0.0, 0.0, selected_trajectory_pub);

          if (fabs(cmd_vel.linear.x) < 0.02) stuck_counter++;
          else stuck_counter = 0;
        } else {
          cmd_vel.linear.x = 0.0;
          cmd_vel.angular.z = 0.0;
          stuck_counter++;
        }
      }

      RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
          "cmd_vel: v=%.3f, w=%.3f, dist=%.2f, idx=%d/%zu, remain=%.2f, stuck=%d, rot=%d, ang_err=%.2f, blocked=%d",
          cmd_vel.linear.x, cmd_vel.angular.z, dist_to_goal,
          current_path_index_, trajpath.size(), remaining_path_dist, stuck_counter,
          (int)rotating_mode, angle_error, (int)path_to_goal_blocked);

      chassCtlPub->publish(cmd_vel);
    }

    rclcpp::spin_some(this->get_node_base_interface());
    loop_rate.sleep();
  }
}

// ========== 占位空实现 ==========
std::vector<std::vector<float>> Differential_DWAPlanner::raycast() { return std::vector<std::vector<float>>(); }
void Differential_DWAPlanner::GetRobotVelocity(Vector3d, Vector3d, Vector3d&) {}
void Differential_DWAPlanner::Deal_Super_Circle(double*, double*) {}
double Differential_DWAPlanner::calVectorAngle(Vector2d, Vector2d) { return 0.0; }
Vector2d Differential_DWAPlanner::calUnitvector(Vector2d v) { return v; }
Vector2d Differential_DWAPlanner::caLocalGoalPosition(vector<Vector2d>, Vector2d, double) { return Vector2d(0,0); }

void Differential_DWAPlanner::LIMIT_VECTOR_Velocity(double &velocity, double &yawrate) {
  if (velocity > MAX_VELOCITY) velocity = MAX_VELOCITY;
  if (velocity < MIN_VELOCITY) velocity = MIN_VELOCITY;
  if (yawrate > MAX_YAWRATE) yawrate = MAX_YAWRATE;
  if (yawrate < -MAX_YAWRATE) yawrate = -MAX_YAWRATE;
}

double Differential_DWAPlanner::calPointLength(const Vector2d &a, const Vector2d &b) {
  return hypot(a[0] - b[0], a[1] - b[1]);
}

void Differential_DWAPlanner::visualize_trajectory(const std::vector<State> &trajectory,
                                                   const double r, const double g, const double b,
                                                   const rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr &pub) {
  visualization_msgs::msg::Marker v_trajectory;
  v_trajectory.header.frame_id = ROBOT_FRAME;
  v_trajectory.header.stamp = this->now();
  v_trajectory.color.r = r; v_trajectory.color.g = g; v_trajectory.color.b = b;
  v_trajectory.color.a = 0.8;
  v_trajectory.ns = pub->get_topic_name();
  v_trajectory.type = visualization_msgs::msg::Marker::LINE_STRIP;
  v_trajectory.action = visualization_msgs::msg::Marker::ADD;
  v_trajectory.scale.x = 0.05;
  geometry_msgs::msg::Pose pose; pose.orientation.w = 1.0; v_trajectory.pose = pose;

  nav_msgs::msg::Path local_path;
  local_path.header.frame_id = ROBOT_FRAME;
  local_path.header.stamp = this->now();

  for (const auto &state : trajectory) {
    geometry_msgs::msg::Point p; p.x = state.x; p.y = state.y;
    v_trajectory.points.push_back(p);

    geometry_msgs::msg::PoseStamped ps;
    ps.pose.position.x = state.x; ps.pose.position.y = state.y;
    local_path.poses.push_back(ps);
  }
  pub->publish(v_trajectory);
  localPathPub->publish(local_path);
}

void Differential_DWAPlanner::visual_VisitedNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish,
                                                 std::vector<Eigen::Vector2d> visitnodes,
                                                 float a_set, float r_set, float g_set,
                                                 float b_set, float length) {
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = "map";
  node_vis.header.stamp = this->now();
  node_vis.color.a = a_set; node_vis.color.r = r_set; node_vis.color.g = g_set; node_vis.color.b = b_set;
  node_vis.ns = "differential_dwa";
  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  node_vis.id = 0;
  node_vis.pose.orientation.w = 1.0;
  node_vis.scale.x = node_vis.scale.y = node_vis.scale.z = 0.05 * length;
  for (const auto &pt : visitnodes) {
    geometry_msgs::msg::Point p; p.x = pt[0]; p.y = pt[1];
    node_vis.points.push_back(p);
  }
  pathPublish->publish(node_vis);
}