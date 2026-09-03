#ifndef __MOTION_PLAN_H
#define __MOTION_PLAN_H

#include <iostream>
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/empty.hpp>
#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <tf2/utils.h>

// 包含全局规划包
#include "path_searcher/Astar_searcher.h"
#include "path_searcher/JPS_searcher.h"
#include "path_searcher/JPS_utils.h"
#include "path_searcher/node.h"
#include "path_searcher/two_way_rrt.h"
#include "path_searcher/nav_app.h"
#include "path_searcher/Hybrid_astar.h"

// 包含自定义速度转换包
#include "vel_transform/vel_transform.h"

// 包含路径优化包
#include "path_optimization/minimum_snap.h"
#include "path_optimization/bezier_curve.h"
#include "path_optimization/BSpline.h"
#include "path_optimization/non_uniform_bspline.h"
#include "path_optimization/bspline_optimizer.h"
#include "path_optimization/fast_security.h"

// 包含路径跟随包
#include "path_follow/pid_follow.h"

// 包含自定义消息包
#include "robot_communication/msg/localization_info_broadcast.hpp"
#include "robot_communication/msg/chassis_control.hpp"
#include "robot_communication/msg/esdf_map.hpp"
#include "robot_communication/msg/goal.hpp"

using namespace std;
using namespace std::chrono;
using namespace dyn_planner;

class motionPlan : public rclcpp::Node
{
private:
  // 话题发布
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr navmapPub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr oriPathPub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr optPathPub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr optPath2Pub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr esdfPathPub;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr localPathPub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr localGoalPub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr optpathNodePub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr goalPointPub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr startPointPub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr firstPointPub;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr secondPointPub;

  rclcpp::TimerBase::SharedPtr timer_;            // 修复 1：补齐 timer_ 声明[cite: 8, 9]
  rclcpp::TimerBase::SharedPtr safety_timer_;       
  bool Replan_Path_Flag;          

  void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg);
  void safetyCallback();

  robot_communication::msg::Goal local_goal;    
  geometry_msgs::msg::PoseStamped global_goal;   

  rclcpp::Publisher<robot_communication::msg::ChassisControl>::SharedPtr chassConPub;    
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr StatusPub;      

  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr visitNodesPub;  
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr globalEndPub;  
  rclcpp::Publisher<robot_communication::msg::ChassisControl>::SharedPtr chassVelPub;  

  mapDefine pathNav;          
  AstarPathFinder::Ptr astar_path_finder;
  AstarPathFinder::Ptr astar_esdf_path_finder;
  JPSPathFinder::Ptr jps_path_finder;
  Hybrid_astar::Ptr hybrid_astar_finder;
  RRTstarPlanner::Ptr rrt_path_finder;

  MinimumSnap MinimumSnapFlow;      
  BEZIER Bezier_Flow;               

  Fast_Security::Ptr fast_security_opt;  

  Eigen::Vector2d startPoint;
  Eigen::Vector2d endPoint;

  robot_communication::msg::LocalizationInfoBroadcast localData;   
  robot_communication::msg::ChassisControl motionData;             
  robot_communication::msg::ChassisControl motionLocal;            

  pid_follow pidFollow;

  // 话题接收
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr staticMap;        
  void staticMapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map); 
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr staticinflateMap;    
  void staticinflateMapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map); 
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr clickSub;     
  void clickCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg); 
  rclcpp::Subscription<robot_communication::msg::LocalizationInfoBroadcast>::SharedPtr localizationSub;  
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odomSub;                  // 修复 2：分离 odom 订阅类型，解决赋值不匹配[cite: 8, 9]
  void localizationCallback(const robot_communication::msg::LocalizationInfoBroadcast::SharedPtr msg); 
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr dynamicMap;   
  void dynamicMapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr map); 
  rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr localPath;  
  void localPathCallback(const nav_msgs::msg::Path::SharedPtr localpath);
  rclcpp::Subscription<robot_communication::msg::ChassisControl>::SharedPtr localVelocitySub;   
  void localVelocityCallback(const robot_communication::msg::ChassisControl::SharedPtr velocity);
  rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initalposeSub;      
  void initalPoseCallback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg);

  vector<Vector2d> local_path;
  Odom_data_define localVel;
  Odom_data_define globalVel;
  vector<Vector2d> tempath;
  double length;
  Vector2d localGoal;

  bool mapInitFlag = false;   
  bool localMapFlag = false;    
  bool getStartFlag = false;    
  bool getEndFlag = false;      
  bool has_arrived_end = false; 

  int control_method = 0;       

  int cruise_num;
  double first_point_x, first_point_y;
  double second_point_x, second_point_y;
  double third_point_x, third_point_y;
  double forth_point_x, forth_point_y;
  double fifth_point_x, fifth_point_y;
  
  vector<Vector2d> cruise_points;

  bool is_sim;
  bool is_cruise;
  double stop_margin;
  string frame_id_name;       

  void pathPlanning(Eigen::Vector2d startMapPoint, Eigen::Vector2d goalMapPoint);
  void pathFollow(std::vector<Eigen::Vector2d> path, Vector2d start, Vector2d goal);
  void BuildPathTest_Follow(void);

  void visual_VisitedNode(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pathPublish, 
                          std::vector<Eigen::Vector2d> visitnodes,
                          float a_set, float r_set, float g_set, float b_set, float length);
  void visualPoints(rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr pointPublish, 
                    Vector2d visitnodes, float a_set, float r_set, float g_set, float b_set, float length); 

  void PublishPath(rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pathPublish, std::vector<Eigen::Vector2d> path);
  void NavtfGrid(const nav_msgs::msg::OccupancyGrid::SharedPtr data, std::vector<int> &map, int x_size, int y_size);
  void mapInit(void); 

  vector<Eigen::Vector2d> fixedpath;
  void BuildFixPath(vector<Eigen::Vector2d> &fixpath);
  
  int control_hz;
  bool worldToMap(double wx, double wy, int &mx, int &my) const;

public:
  // 修复 3：消除无参和带参构造函数的二义性，仅保留带默认参数的构造函数[cite: 8]
  explicit motionPlan(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  void controlLoop();
  ~motionPlan();
  
  void motionInit(void);
};

#endif  // __MOTION_PLAN_H