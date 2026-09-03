#ifndef __DIFFERENTIAL_DWA_H
#define __DIFFERENTIAL_DWA_H

#include <rclcpp/rclcpp.hpp>
#include <tf2/utils.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>

#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <memory>
#include <string>

#include "vel_transform/vel_transform.h"
#include "path_follow/pid_follow.h"
#include "robot_communication/msg/localization_info_broadcast.hpp"
#include "robot_communication/msg/chassis_control.hpp"
#include "robot_communication/msg/goal.hpp"

using namespace std;
using namespace Eigen;

class Differential_DWAPlanner : public rclcpp::Node
{
public:
  Differential_DWAPlanner();

  class State
  {
  public:
    State(double, double, double, double, double);
    double x, y, yaw, velocity, yawrate;
  };

  class Window
  {
  public:
    Window(void);
    Window(const double, const double, const double, const double);
    double min_velocity, max_velocity, min_yawrate, max_yawrate;
  };

  // 主循环
  void process(void);

  // 回调
  void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg);
  void local_goal_callback(const robot_communication::msg::Goal::SharedPtr msg);
  void pathCallback(const nav_msgs::msg::Path::SharedPtr path);
  void local_map_callback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg);
  void target_velocity_callback(const geometry_msgs::msg::Twist::SharedPtr global);
  void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg);

  // DWA 核心函数
  Window calc_dynamic_window(const geometry_msgs::msg::Twist &cur_velocity);
  float calc_to_goal_cost(const std::vector<State> &traj, const Eigen::Vector3d &goal);
  float calc_speed_cost(const std::vector<State> &traj, const float target_velocity);
  float calc_obstacle_cost(std::vector<State> &traj, const std::vector<std::pair<double,double>> &scan_points);
  void motion(State &state, const double velocity, const double yawrate);
  std::vector<State> dwa_planning(Window dynamic_window, Eigen::Vector3d goal,
                                  const std::vector<std::pair<double,double>> &scan_points,
                                  double target_velocity);

  // 可视化
  void visualize_trajectory(const std::vector<State> &trajectory, const double r, const double g, const double b, 
                            const rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr &pub);
  void visual_VisitedNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish, 
                          std::vector<Eigen::Vector2d> visitnodes,
                          float a_set, float r_set, float g_set, float b_set, float length);

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr chassCtlPub;

protected:
  // ----- 参数 -----
  double HZ;
  std::string ROBOT_FRAME;
  double TARGET_VELOCITY;
  double MAX_VELOCITY, MIN_VELOCITY;
  double MAX_YAWRATE;
  double MAX_ACCELERATION, MAX_D_YAWRATE;
  double MAX_DIST;
  double VELOCITY_RESOLUTION, YAWRATE_RESOLUTION;
  double ANGLE_RESOLUTION;
  double PREDICT_TIME;
  double TO_GOAL_COST_GAIN, SPEED_COST_GAIN, OBSTACLE_COST_GAIN;
  double DT;
  double GOAL_THRESHOLD, TURN_DIRECTION_THRESHOLD;
  double TEMP_GOAL_RADIUS;
  double ROBOT_RADIUS, SAFETY_MARGIN;
  double LOOKAHEAD_DIST;

  // ----- 状态 -----
  Vector3d nowposition;
  Vector3d localposition;
  geometry_msgs::msg::Twist current_velocity;
  bool odom_updated, local_goal_subscribed, local_map_updated, scan_updated;
  bool update_path;
  int path_nodes_num, last_path_nodes_num;
  int current_path_index_;
  bool final_reached_;
  Vector2d final_goal_;
  double goal_yaw_;

  // ----- 路径存储 -----
  vector<Vector2d> trajpath;
  vector<pair<int,Vector2d>> visitPath;   // 保留兼容

  // ----- 激光点云 -----
  std::vector<std::pair<double,double>> scan_points_;
  double laser_max_range_;

  // ----- TF 与 地图 -----
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  nav_msgs::msg::OccupancyGrid local_map;
  double map_origin_x_, map_origin_y_;

  // ----- ROS 2 发布/订阅 -----
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr candidate_trajectories_pub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr selected_trajectory_pub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr localPathPub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr localgoalPub;

  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr local_map_sub;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub;
  rclcpp::Subscription<robot_communication::msg::Goal>::SharedPtr local_goal_sub;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr target_velocity_sub;
  rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr pathSub;

  // 用于 local_goal_callback 存储消息
  robot_communication::msg::Goal local_goal;

  // ----- 辅助函数 -----
  double calPointLength(const Vector2d &a, const Vector2d &b);
  double clearance_at(double x, double y);
  void update_path_index(double rx, double ry);
  void compute_lookahead_target(double rx, double ry, double &gx, double &gy, double &g_yaw);
  void LIMIT_VECTOR_Velocity(double &velocity, double &yawrate);

  std::vector<std::vector<float>> raycast();
  void GetRobotVelocity(Vector3d, Vector3d, Vector3d&);
  void Deal_Super_Circle(double*, double*);
  double calVectorAngle(Vector2d, Vector2d);
  Vector2d calUnitvector(Vector2d);
  Vector2d caLocalGoalPosition(vector<Vector2d>, Vector2d, double);
  pid_follow pidFollow;
  double anglePID[7];
};
#endif // __DIFFERENTIAL_DWA_H