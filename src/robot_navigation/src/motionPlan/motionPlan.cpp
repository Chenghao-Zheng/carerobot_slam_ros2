/*
 * @Author: your name
 * @Date: 2023-04-28 10:46:52
 * @LastEditTime: 2026-08-31
 * @Description: ROS 2 motionPlan Node implementation
 */

#include "motionPlan/motionPlan.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <chrono>

using namespace std::chrono_literals;

motionPlan::motionPlan(const rclcpp::NodeOptions & options) 
: Node("motion_plan_node", options)
{
  // 【关键修复】：构造函数中不能直接调用 motionInit()
  // 必须在 main() 函数中 std::make_shared 完成后再手动调用！
  // motionInit();

  double loop_period_sec = 1.0 / 50.0;
  timer_ = this->create_wall_timer(
    std::chrono::duration<double>(loop_period_sec),
    std::bind(&motionPlan::controlLoop, this));
}

motionPlan::~motionPlan()
{
}

void motionPlan::controlLoop()
{
  auto timeStart = std::chrono::steady_clock::now();

  pathPlanning(startPoint, endPoint);

  auto timeEnd = std::chrono::steady_clock::now();
  auto timeDuration = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart);
}

void motionPlan::BuildPathTest_Follow(void)
{
  BuildFixPath(pathNav.worldpath);
  PublishPath(optPathPub, pathNav.worldpath);
}

void motionPlan::motionInit(void)
{
  startPoint = Eigen::Vector2d(0.00f, 0.00f);
  endPoint = Eigen::Vector2d(0.00f, 0.00f);

  // 【关键修复】：所有参数声明前添加 has_parameter 安全防护
  if (!this->has_parameter("motion_node.is_sim"))
    is_sim = this->declare_parameter<bool>("motion_node.is_sim", false);
  else
    is_sim = this->get_parameter("motion_node.is_sim").as_bool();

  if (!this->has_parameter("motion_node.is_cruise"))
    is_cruise = this->declare_parameter<bool>("motion_node.is_cruise", false);
  else
    is_cruise = this->get_parameter("motion_node.is_cruise").as_bool();

  if (!this->has_parameter("motion_plan.control_hz"))
    control_hz = this->declare_parameter<int>("motion_plan.control_hz", 50);
  else
    control_hz = this->get_parameter("motion_plan.control_hz").as_int();

  if (!this->has_parameter("motion_plan.control_method"))
    control_method = this->declare_parameter<int>("motion_plan.control_method", 1);
  else
    control_method = this->get_parameter("motion_plan.control_method").as_int();

  if (!this->has_parameter("motion_plan.stop_margin"))
    stop_margin = this->declare_parameter<double>("motion_plan.stop_margin", 0.1);
  else
    stop_margin = this->get_parameter("motion_plan.stop_margin").as_double();

  if (!this->has_parameter("cruise_num"))
    cruise_num = this->declare_parameter<int>("cruise_num", 5);
  else
    cruise_num = this->get_parameter("cruise_num").as_int();

  auto declare_or_get_double = [this](const std::string &name, double default_val) {
    if (!this->has_parameter(name)) {
      return this->declare_parameter<double>(name, default_val);
    }
    return this->get_parameter(name).as_double();
  };

  auto declare_or_get_int = [this](const std::string &name, int default_val) {
    if (!this->has_parameter(name)) {
      return this->declare_parameter<int>(name, default_val);
    }
    return this->get_parameter(name).as_int();
  };

  first_point_x = declare_or_get_double("first_point_x", 0.1);
  first_point_y = declare_or_get_double("first_point_y", 0.1);
  second_point_x = declare_or_get_double("second_point_x", 0.1);
  second_point_y = declare_or_get_double("second_point_y", 0.1);
  third_point_x = declare_or_get_double("third_point_x", 0.1);
  third_point_y = declare_or_get_double("third_point_y", 0.1);
  forth_point_x = declare_or_get_double("forth_point_x", 0.1);
  forth_point_y = declare_or_get_double("forth_point_y", 0.1);
  fifth_point_x = declare_or_get_double("fifth_point_x", 0.1);
  fifth_point_y = declare_or_get_double("fifth_point_y", 0.1);

  cruise_points.resize(cruise_num);
  if(is_cruise == true)
  {
    cruise_points[0][0] = first_point_x; cruise_points[0][1] = first_point_y;
    cruise_points[1][0] = second_point_x; cruise_points[1][1] = second_point_y;
    cruise_points[2][0] = third_point_x; cruise_points[2][1] = third_point_y;
    cruise_points[3][0] = forth_point_x; cruise_points[3][1] = forth_point_y;
    cruise_points[4][0] = fifth_point_x; cruise_points[4][1] = fifth_point_y;
  }

  double max_vel = declare_or_get_double("minimum_snap.max_vel", 1.0);
  double max_acce = declare_or_get_double("minimum_snap.max_acce", 1.0);
  int order = declare_or_get_int("minimum_snap.order", 3);
  MinimumSnapFlow.setParams(order, max_vel, max_acce);

  int sub = declare_or_get_int("bezier_curve.sub", 3);
  double max_vel_b = declare_or_get_double("bezier_curve.max_vel", 1.0);
  double time_resolution = declare_or_get_double("bezier_curve.time_resolution", 0.01);
  Bezier_Flow.setParams(max_vel_b, time_resolution, sub);

  pidFollow.pid_params[0] = declare_or_get_double("pid_p", 1.0);
  pidFollow.pid_params[1] = declare_or_get_double("pid_i", 0.0);
  pidFollow.pid_params[2] = declare_or_get_double("pid_d", 0.0);
  pidFollow.pid_params[3] = declare_or_get_double("pid_outmax", 0.0);
  pidFollow.pid_params[4] = declare_or_get_double("pid_outmin", 0.0);
  pidFollow.pid_params[5] = declare_or_get_double("pid_intmax", 0.0);
  pidFollow.pid_params[6] = declare_or_get_double("pid_intdt", 0.0);
  pidFollow.forwardDistance = declare_or_get_double("forwardDistance", 0.0);

  pidFollow.Init();

  astar_path_finder.reset(new AstarPathFinder);
  astar_path_finder->InitParams(shared_from_this());

  astar_esdf_path_finder.reset(new AstarPathFinder);
  astar_esdf_path_finder->InitParams(shared_from_this(), true);

  jps_path_finder.reset(new JPSPathFinder);
  jps_path_finder->InitParams(shared_from_this());

  hybrid_astar_finder.reset(new Hybrid_astar);
  hybrid_astar_finder->InitParams(shared_from_this());

  rrt_path_finder.reset(new RRTstarPlanner);

  fast_security_opt.reset(new Fast_Security);
  fast_security_opt->InitParams(shared_from_this());

  auto map_qos = rclcpp::QoS(rclcpp::KeepLast(1)).transient_local().reliable();
  staticMap = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
    "/global_map_esdf_display", map_qos, std::bind(&motionPlan::staticMapCallback, this, std::placeholders::_1));
  
  clickSub = this->create_subscription<geometry_msgs::msg::PoseStamped>(
    "/move_base_simple/goal", 10, std::bind(&motionPlan::clickCallback, this, std::placeholders::_1));

  globalEndPub = this->create_publisher<geometry_msgs::msg::PoseStamped>("/globalEnd", 1);

  initalposeSub = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
    "/initialpose", 10, std::bind(&motionPlan::initalPoseCallback, this, std::placeholders::_1));

  if (is_sim == false)
  {
    localizationSub = this->create_subscription<robot_communication::msg::LocalizationInfoBroadcast>(
      "/odom_carto", 10, std::bind(&motionPlan::localizationCallback, this, std::placeholders::_1));
  }
  else
  {
    odomSub = this->create_subscription<nav_msgs::msg::Odometry>(
      "/odom", 10, std::bind(&motionPlan::odomCallback, this, std::placeholders::_1));
  }

  dynamicMap = this->create_subscription<nav_msgs::msg::OccupancyGrid>(
    "/local_map_esdf", 10, std::bind(&motionPlan::dynamicMapCallback, this, std::placeholders::_1));

  localVelocitySub = this->create_subscription<robot_communication::msg::ChassisControl>(
    "/local_velocity", 10, std::bind(&motionPlan::localVelocityCallback, this, std::placeholders::_1));

  oriPathPub = this->create_publisher<nav_msgs::msg::Path>("/ori_path", 10);
  optPathPub = this->create_publisher<nav_msgs::msg::Path>("/opt_path", 10);
  optPath2Pub = this->create_publisher<nav_msgs::msg::Path>("/opt2_path", 10);
  esdfPathPub = this->create_publisher<nav_msgs::msg::Path>("/esdf_path", 10);

  optpathNodePub = this->create_publisher<visualization_msgs::msg::Marker>("/Opt_path_Nodes", 10);
  goalPointPub = this->create_publisher<visualization_msgs::msg::Marker>("/goal_point", 1);
  startPointPub = this->create_publisher<visualization_msgs::msg::Marker>("/start_point", 1);
  firstPointPub = this->create_publisher<visualization_msgs::msg::Marker>("/first_point", 1);
  secondPointPub = this->create_publisher<visualization_msgs::msg::Marker>("/second_point", 1);

  if (!this->has_parameter("motion_plan.frame_id"))
    frame_id_name = this->declare_parameter<std::string>("motion_plan.frame_id", "odom");
  else
    frame_id_name = this->get_parameter("motion_plan.frame_id").as_string();
}

void motionPlan::BuildFixPath(std::vector<Eigen::Vector2d> &fixpath)
{
  static int start = 0;
  start++;
  if(start >= 2500)
  {
    start = 2400;
  }

  fixpath.resize(2500 - start + 1);

  fixpath[0](0) = startPoint(0);
  fixpath[0](1) = startPoint(1);

  for (int i = start; i < 2500; i++)
  {
    double x = 0.0, y = 0.0;
    if(i <= 240)
    {
      x = 0;
      y = i / 40.0;
    }
    else if(i > 240 && i <= 400)
    {
      x = (i - 240) / 40.0;
      y = 6;
    }
    else if(i > 400 && i <= 1040)
    {
      x = 4;
      y = 6 + (i - 400) / 40.0;
    }
    else if(i > 1040 && i <= 1440)
    {
      x = 4 + (i - 1040) / 40.0;
      y = 22;
    }
    else if(i > 1440 && i <= 1680)
    {
      x = 14;
      y = 22 - (i - 1440) / 40.0;
    }
    else if(i > 1680 && i <= 1840)
    {
      x = 14 + (i - 1680) / 40.0;
      y = 16;
    }
    else if(i > 1840 && i <= 2160)
    {
      x = 18;
      y = 16 - (i - 1840) / 40.0;
    }
    else if(i > 2160 && i <= 2400)
    {
      x = 18 - (i - 2160) / 40.0;
      y = 8;
    }

    fixpath[i - start + 1](0) = x;
    fixpath[i - start + 1](1) = y;
  }
}

void motionPlan::clickCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  global_goal = *msg;

  double roll, pitch, yaw;
  tf2::Quaternion quat(
      global_goal.pose.orientation.x,
      global_goal.pose.orientation.y,
      global_goal.pose.orientation.z,
      global_goal.pose.orientation.w);
  tf2::Matrix3x3(quat).getRPY(roll, pitch, yaw);

  if(is_cruise == false)
  {
    endPoint[0] = msg->pose.position.x;
    endPoint[1] = msg->pose.position.y;
    getEndFlag = true;
    visualPoints(goalPointPub, endPoint, 1.0f, 1.0f, 0.0f, 0.0f, 5.0f);
  }
  else
  {
    endPoint = cruise_points[0];
    getEndFlag = true;
    visualPoints(goalPointPub, endPoint, 1.0f, 1.0f, 0.0f, 0.0f, 5.0f);    
  }
}

void motionPlan::visualPoints(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pointPublish,
                            Eigen::Vector2d visitnodes, float a_set, float r_set, float g_set, float b_set, float length)
{
  visualization_msgs::msg::Marker node_vis2;
  node_vis2.header.frame_id = frame_id_name; // ✅ 改为读取配置变量
  node_vis2.header.stamp = this->now();
  node_vis2.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis2.action = visualization_msgs::msg::Marker::ADD;
  node_vis2.id = 0;

  node_vis2.pose.orientation.x = 0.0;
  node_vis2.pose.orientation.y = 0.0;
  node_vis2.pose.orientation.z = 0.0;
  node_vis2.pose.orientation.w = 1.0;

  node_vis2.color.a = a_set;
  node_vis2.color.r = r_set;
  node_vis2.color.g = g_set;
  node_vis2.color.b = b_set;
  node_vis2.scale.x = pathNav.resolution * length;
  node_vis2.scale.y = pathNav.resolution * length;
  node_vis2.scale.z = pathNav.resolution * length;

  geometry_msgs::msg::Point pt2;
  pt2.x = visitnodes[0];
  pt2.y = visitnodes[1];
  pt2.z = 0.0;
  node_vis2.points.push_back(pt2);
  pointPublish->publish(node_vis2);
}

void motionPlan::initalPoseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg)
{
  startPoint[0] = msg->pose.pose.position.x;
  startPoint[1] = msg->pose.pose.position.y;

  if(std::abs((startPoint - endPoint).norm()) <= stop_margin)
  {
    has_arrived_end = true;
  }
  else {
    has_arrived_end = false;
  }

  getStartFlag = true;
  visualPoints(startPointPub, startPoint, 1.0f, 0.0f, 1.0f, 0.0f, 5.0f);
}

void motionPlan::localizationCallback(const robot_communication::msg::LocalizationInfoBroadcast::SharedPtr msg)
{
  localData.xposition = msg->xposition;
  localData.yposition = msg->yposition;
  localData.xspeed = msg->xspeed;
  localData.yspeed = msg->yspeed;
  localData.xaccel = msg->xaccel;
  localData.yaccel = msg->yaccel;
  localData.chassisgyro = msg->chassisgyro;
  localData.chassisangle = msg->chassisangle;

  startPoint[0] = msg->xposition;
  startPoint[1] = msg->yposition;

  static int i = 0;
  if(std::abs((startPoint - endPoint).norm()) <= stop_margin)
  {
    has_arrived_end = true;
    if(is_cruise)
    {
      endPoint = cruise_points[i];
      getEndFlag = true;
      visualPoints(goalPointPub, endPoint, 1.0f, 1.0f, 0.0f, 0.0f, 5.0f); 
      i++;
    }
  }
  else
  {
    has_arrived_end = false;
    if(is_cruise)
    {
      if(i == 5)
      {
        i = 0;
      }
    }
  }
  getStartFlag = true;
}

void motionPlan::odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    startPoint[0] = msg->pose.pose.position.x;
    startPoint[1] = msg->pose.pose.position.y;
    getStartFlag = true;
}

void motionPlan::staticMapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
{
  pathNav.origin_x = msg->info.origin.position.x;
  pathNav.origin_y = msg->info.origin.position.y;
  pathNav.resolution = msg->info.resolution;
  pathNav.width = msg->info.width;
  pathNav.height = msg->info.height;

  if(stop_margin < pathNav.resolution)
  {
    stop_margin = pathNav.resolution;
  }

  RCLCPP_INFO(this->get_logger(), "\033[1;32m ***********map message**********\033[0m");
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_x: %f  \033[0m", pathNav.origin_x);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m origin_y: %f  \033[0m", pathNav.origin_y);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m resolution: %f  \033[0m", pathNav.resolution);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m width: %d  \033[0m", pathNav.width);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m height: %d  \033[0m", pathNav.height);
  RCLCPP_INFO(this->get_logger(), "\033[1;32m *********************************\033[0m");

  pathNav.mapData.resize(pathNav.width * pathNav.height);
  for (unsigned int i = 0; i < pathNav.width; i++)
  {
    for (unsigned int j = 0; j < pathNav.height; j++)
    {
      pathNav.mapData[i * pathNav.height + j] = static_cast<int>(msg->data[j * pathNav.width + i]);
    }
  }

  for (size_t i = 0; i < pathNav.mapData.size(); ++i)
  {
      if (pathNav.mapData[i] == -1)
          pathNav.mapData[i] = 40;
  }

  if(control_method == 1)
  {
    astar_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                              pathNav.width, pathNav.height, pathNav.mapData);

    astar_esdf_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                              pathNav.width, pathNav.height, pathNav.mapData); 

    fast_security_opt->SetMapParams(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                              pathNav.width, pathNav.height, msg->data);
  }
  if(control_method == 2)
  {
    hybrid_astar_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                              pathNav.width, pathNav.height, pathNav.mapData);
  }
  if(control_method == 3)
  {
    jps_path_finder->InitMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                              pathNav.width, pathNav.height, pathNav.mapData);
  }
  if(control_method == 4)
  {
    rrt_path_finder->initMap(pathNav.resolution, pathNav.origin_x, pathNav.origin_y,
                              pathNav.width, pathNav.height, pathNav.mapData);
  }

  mapInitFlag = true;
}

void motionPlan::dynamicMapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map)
{
  std::vector<int> tempmap;
  tempmap.resize(map->info.width * map->info.height);
  for (unsigned int i = 0; i < map->info.width; i++)
  {
    for (unsigned int j = 0; j < map->info.height; j++)
    {
      tempmap[i * map->info.height + j] = static_cast<int>(map->data[j * map->info.width + i]);
    }
  }

  localMapFlag = true;
}

void motionPlan::localVelocityCallback(const robot_communication::msg::ChassisControl::SharedPtr velocity)
{
  motionLocal = *velocity;
}

void motionPlan::visual_VisitedNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish, 
                                    std::vector<Eigen::Vector2d> visitnodes,
                                    float a_set, float r_set, float g_set, float b_set, float length)
{
  visualization_msgs::msg::Marker node_vis;
  node_vis.header.frame_id = frame_id_name; // ✅ 改为读取配置变量
  node_vis.header.stamp = this->now();

  node_vis.color.a = a_set;
  node_vis.color.r = r_set;
  node_vis.color.g = g_set;
  node_vis.color.b = b_set;
  node_vis.ns = "fast_security_visited";

  node_vis.type = visualization_msgs::msg::Marker::CUBE_LIST;
  node_vis.action = visualization_msgs::msg::Marker::ADD;
  node_vis.id = 0;

  node_vis.pose.orientation.x = 0.0;
  node_vis.pose.orientation.y = 0.0;
  node_vis.pose.orientation.z = 0.0;
  node_vis.pose.orientation.w = 1.0;

  node_vis.scale.x = 0.05 * length;
  node_vis.scale.y = 0.05 * length;
  node_vis.scale.z = 0.05 * length;

  geometry_msgs::msg::Point pt;
  for (size_t i = 0; i < visitnodes.size(); i++)
  {
    pt.x = visitnodes[i][0];
    pt.y = visitnodes[i][1];
    node_vis.points.push_back(pt);
  }

  pathPublish->publish(node_vis);  
}

void motionPlan::PublishPath(rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pathPublish, std::vector<Eigen::Vector2d> path)
{
  nav_msgs::msg::Path pathTopic;
  pathTopic.header.frame_id = frame_id_name;
  pathTopic.header.stamp = this->now();

  for (size_t i = 0; i < path.size(); i++)
  {
    geometry_msgs::msg::PoseStamped pathPose;
    pathPose.header.frame_id = frame_id_name;
    pathPose.header.stamp = this->now();
    pathPose.pose.position.x = path[i][0];
    pathPose.pose.position.y = path[i][1];
    pathPose.pose.position.z = 0.0;

    pathTopic.poses.push_back(pathPose);
  }
  pathPublish->publish(pathTopic);
}

bool motionPlan::worldToMap(double wx, double wy, int &mx, int &my) const
{
    if (wx < pathNav.origin_x || wy < pathNav.origin_y)
        return false;
    mx = static_cast<int>((wx - pathNav.origin_x) / pathNav.resolution);
    my = static_cast<int>((wy - pathNav.origin_y) / pathNav.resolution);
    if (mx < 0 || mx >= static_cast<int>(pathNav.width) || my < 0 || my >= static_cast<int>(pathNav.height))
        return false;
    return true;
}

void motionPlan::pathPlanning(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint)
{
  if(has_arrived_end){
    std::cout << "Arrived the end!" << std::endl;
    if(!pathNav.worldpath.empty()) {
      PublishPath(oriPathPub, pathNav.worldpath);
      PublishPath(optPathPub, pathNav.optpath);
    }
    return;
  }

  if(control_method == 1)
  {
    if (mapInitFlag == true && getStartFlag == true )
    {
      if(getEndFlag == true)
      {
        auto isFree = [this](const Eigen::Vector2d& pt) -> bool {
            int mx, my;
            if (!this->worldToMap(pt.x(), pt.y(), mx, my))
                return false;
            int idx = mx * pathNav.height + my;
            if (idx < 0 || idx >= static_cast<int>(pathNav.mapData.size()))
                return false;
            return pathNav.mapData[idx] < 50;  
        };

        static int start_retry_count = 0;
        static int goal_retry_count = 0;
        const int MAX_RETRY = 5;

        if (!isFree(startMapPoint)) {
            RCLCPP_WARN(this->get_logger(), "Start point is in obstacle, searching nearby... (retry %d)", start_retry_count);
            Eigen::Vector2d new_start = startMapPoint;
            bool found = false;
            double step = 0.1;
            for (double r = 0.3; r <= 2.0 && !found; r += 0.2) {
                for (double dx = -r; dx <= r && !found; dx += step) {
                    for (double dy = -r; dy <= r && !found; dy += step) {
                        if (std::abs(dx) < 1e-6 && std::abs(dy) < 1e-6) continue;
                        Eigen::Vector2d test = startMapPoint + Eigen::Vector2d(dx, dy);
                        if (isFree(test)) {
                            new_start = test;
                            found = true;
                            RCLCPP_WARN(this->get_logger(), "Found alternative start at (%.2f, %.2f)", new_start.x(), new_start.y());
                        }
                    }
                }
            }
            if (found) {
                startMapPoint = new_start;
                startPoint = new_start;
                start_retry_count = 0;
            } else {
                start_retry_count++;
                if (start_retry_count >= MAX_RETRY) {
                    RCLCPP_ERROR(this->get_logger(), "Start invalid for %d times, clearing getEndFlag and publishing empty path.", MAX_RETRY);
                    getEndFlag = false;
                    start_retry_count = 0;
                    pathNav.worldpath.clear();
                    pathNav.optpath.clear();
                    PublishPath(oriPathPub, pathNav.worldpath);
                    PublishPath(optPathPub, pathNav.optpath);
                    has_arrived_end = true;
                    return;
                } else {
                    RCLCPP_ERROR(this->get_logger(), "No free start found, keep trying (retry %d/%d)", start_retry_count, MAX_RETRY);
                    return;
                }
            }
        } else {
            start_retry_count = 0;
        }

        if (!isFree(goalMapPoint)) {
            RCLCPP_WARN(this->get_logger(), "Goal point is in obstacle, searching nearby... (retry %d)", goal_retry_count);
            Eigen::Vector2d new_goal = goalMapPoint;
            bool found = false;
            double step = 0.1;
            for (double r = 0.3; r <= 2.0 && !found; r += 0.2) {
                for (double dx = -r; dx <= r && !found; dx += step) {
                    for (double dy = -r; dy <= r && !found; dy += step) {
                        if (std::abs(dx) < 1e-6 && std::abs(dy) < 1e-6) continue;
                        Eigen::Vector2d test = goalMapPoint + Eigen::Vector2d(dx, dy);
                        if (isFree(test)) {
                            new_goal = test;
                            found = true;
                            RCLCPP_WARN(this->get_logger(), "Found alternative goal at (%.2f, %.2f)", new_goal.x(), new_goal.y());
                        }
                    }
                }
            }
            if (found) {
                goalMapPoint = new_goal;
                endPoint = new_goal;
                goal_retry_count = 0;
            } else {
                goal_retry_count++;
                if (goal_retry_count >= MAX_RETRY) {
                    RCLCPP_ERROR(this->get_logger(), "Goal invalid for %d times, clearing getEndFlag and publishing empty path.", MAX_RETRY);
                    getEndFlag = false;
                    goal_retry_count = 0;
                    pathNav.worldpath.clear();
                    pathNav.optpath.clear();
                    PublishPath(oriPathPub, pathNav.worldpath);
                    PublishPath(optPathPub, pathNav.optpath);
                    has_arrived_end = true;
                    return;
                } else {
                    RCLCPP_ERROR(this->get_logger(), "No free goal found, keep trying (retry %d/%d)", goal_retry_count, MAX_RETRY);
                    return;
                }
            }
        } else {
            goal_retry_count = 0;
        }

        std::cout << "Start is: " << startMapPoint[0] << " " << startMapPoint[1] << std::endl;
        std::cout << "Goal is: " << goalMapPoint[0] << " " << goalMapPoint[1] << std::endl;

        astar_esdf_path_finder->resetUsedGrids();
        rclcpp::Time time_5 = this->now();
        
        astar_esdf_path_finder->AstarWorldSearch(startMapPoint, goalMapPoint);
        
        std::vector<Eigen::Vector2d> World_Path = astar_esdf_path_finder->getWorldPath();
        pathNav.worldpath = astar_esdf_path_finder->getWorldPath();
        World_Path = astar_esdf_path_finder->getSamples(0.5);

        pathNav.optpath = MinimumSnapFlow.Minimum_Snap(World_Path);
        rclcpp::Time time_6 = this->now();
        
        std::cout << "astar_esdf 扩展总的栅格数目: " << astar_esdf_path_finder->getVisitedNodesNum() << std::endl;
        std::cout << "astar_esdf 优化的路径长度: " << astar_esdf_path_finder->getWorldPathLength() << " m" << std::endl;
        RCLCPP_WARN(this->get_logger(), "astar esdf search time is: %f ms", (time_6 - time_5).seconds() * 1000.0);

        PublishPath(oriPathPub, pathNav.worldpath);
        PublishPath(optPathPub, pathNav.optpath);

        if(pathNav.optpath.size() > 0)
        {
          getEndFlag = false;
          start_retry_count = 0;
          goal_retry_count = 0;
        }
      }
      else
      {
        PublishPath(oriPathPub, pathNav.worldpath);
        PublishPath(optPathPub, pathNav.optpath);
      }
    }
  }
  else if(control_method == 2)
  {
    if (mapInitFlag == true && getStartFlag == true )
    {
      if(getEndFlag == true)
      {
        rclcpp::Time time_1 = this->now();

        hybrid_astar_finder->reset();
        int status = hybrid_astar_finder->search(startMapPoint,
                                      Eigen::Vector2d(0, 0),
                                      Eigen::Vector2d(0, 0),
                                      goalMapPoint, 
                                      Eigen::Vector2d(0, 0), true, false, -1.0);
        if (status == Hybrid_astar::NO_PATH)
        {
          std::cout << "[planner]: init search fail!" << std::endl;
          hybrid_astar_finder->reset();
          status = hybrid_astar_finder->search(startMapPoint, 
                                                Eigen::Vector2d(0, 0), 
                                                Eigen::Vector2d(0, 0), 
                                                goalMapPoint, 
                                                Eigen::Vector2d(0, 0), false, false, -1.0);
          if (status == Hybrid_astar::NO_PATH)
          {
            std::cout << "[planner]: Can't find path." << std::endl;
          }
          else
          {
            std::cout << "[planner]: retry search success." << std::endl;
          }
        }
        rclcpp::Time time_2 = this->now(); 

        pathNav.worldpath = hybrid_astar_finder->getKinoTraj(0.02);
        std::cout << "原始路径点数目:" << pathNav.worldpath.size() << std::endl;
        RCLCPP_WARN(this->get_logger(), "hybrid a star search time is:%f", (time_2 - time_1).seconds() * 1000.0);

        PublishPath(optPathPub, pathNav.worldpath);
        getEndFlag = false;
      }
      else
      {
        PublishPath(optPathPub, pathNav.worldpath);
      }      
    }
  }
  else if(control_method == 3)
  {
    if (mapInitFlag == true && getStartFlag == true )
    {
      if(getEndFlag == true)
      {
        getEndFlag = false;
        rclcpp::Time time_1 = this->now();

        jps_path_finder->resetUsedGrids();
        int status = jps_path_finder->JPSWorldSearch(startMapPoint, goalMapPoint);
        (void)status;
        rclcpp::Time time_2 = this->now();

        pathNav.worldpath = jps_path_finder->getWorldPath();
        std::cout << "原始路径点数目:" << pathNav.worldpath.size() << std::endl;
        RCLCPP_WARN(this->get_logger(), "jps search time is:%f", (time_2 - time_1).seconds() * 1000.0);
        PublishPath(oriPathPub, pathNav.worldpath);
        getEndFlag = false;
      }
      else
      {
        PublishPath(oriPathPub, pathNav.worldpath);
      }
    }
  }
  else if(control_method == 4)
  {
    if (mapInitFlag == true && getStartFlag == true )
    {
      if(getEndFlag == true)
      {
        getEndFlag = false;
        rclcpp::Time time_1 = this->now();
        rrt_path_finder->FindPath(startMapPoint, goalMapPoint);
        rclcpp::Time time_2 = this->now();

        pathNav.worldpath = rrt_path_finder->path;
        std::cout << "原始路径点数目:" << pathNav.worldpath.size() << std::endl;
        RCLCPP_WARN(this->get_logger(), "rrt star search time is:%f", (time_2 - time_1).seconds() * 1000.0);
        PublishPath(oriPathPub, pathNav.worldpath);
        getEndFlag = false;
      }
      else
      {
        PublishPath(oriPathPub, pathNav.worldpath);
      }
    }
  }  
}