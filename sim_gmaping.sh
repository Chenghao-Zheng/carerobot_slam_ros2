#!/usr/bin/env bash
set -e

# 1) 清理旧进程
rosnode kill -a 2>/dev/null || true
killall -9 gzserver gzclient 2>/dev/null || true
killall -9 roscore rosmaster 2>/dev/null || true
yes | rosclean purge
sleep 2

# 2) 启动 roscore
gnome-terminal -t "roscore" -- bash -lc "roscore"
until rostopic list >/dev/null 2>&1; do sleep 0.2; done

rosparam set /use_sim_time true   # 仿真时使用 sim time

# 3) 启动 Gazebo + robot（建图专用 launch）
gnome-terminal -t "gazebo_rviz_start" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch diff_drive_gazebo sim_gazebo_rviz_gamapping.launch"
until rostopic list 2>/dev/null | grep -q "/gazebo/model_states"; do sleep 0.5; done

# 4) 启动 gmapping（建图）
gnome-terminal -t "gmapping_start" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch robot_gmapping gmapping.launch; exec bash"

# 5) 雷达点云转换成point-cloud2
gnome-terminal -t "laser to cloud" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch read_laser_data laser_to_cloud.launch; exec bash"

# 6）启动地图节点
gnome-terminal -t "map start" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch robot_costmap map_deal.launch;exec bash"

# 7) 启动你自己的全局规划器（原来的 motionPlan_sim.launch 但可能需调整地图话题）
gnome-terminal -t "motion_plan" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch robot_navigation motionPlan_sim.launch"

# 8) 启动你自己的局部规划器（DWA）
gnome-terminal -t "local_planner" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch robot_navigation Differential_DWA.launch"

# # 8）局部规划d算法***********
# gnome-terminal -t "PID_control" -- bash -c \
# "source ~/carerobot_slam_ros1/devel/setup.bash; 
# roslaunch robot_pid_local_planner differential_PID.launch; exec bash"

# 9) 启动 explore_lite（自动探索）
gnome-terminal -t "explore_lite" -- bash -lc "source ~/carerobot_slam_ros1/devel/setup.bash; roslaunch explore_lite explore.launch"

# （可选）启动键盘控制用于调试
# gnome-terminal -t "teleop" -- bash -lc "source ... keyboard_control.launch"