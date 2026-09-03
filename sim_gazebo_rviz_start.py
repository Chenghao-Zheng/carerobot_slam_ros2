#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    # 获取各个功能包的共享路径
    diff_drive_gazebo_share = get_package_share_directory('diff_drive_gazebo')
    robot_costmap_share = get_package_share_directory('robot_costmap')
    robot_pid_share = get_package_share_directory('robot_pid_local_planner')
    robot_nav_share = get_package_share_directory('robot_navigation')

    # 指向各自的 launch 文件
    sim_gazebo_launch = os.path.join(diff_drive_gazebo_share, 'launch', 'sim_gazebo_rviz.launch.py')
    map_deal_launch = os.path.join(robot_costmap_share, 'launch', 'map_deal.launch.py')
    pid_planner_launch = os.path.join(robot_pid_share, 'launch', 'differential_PID.launch.py')
    motion_plan_launch = os.path.join(robot_nav_share, 'launch', 'motionPlan.launch.py')

    return LaunchDescription([
        # 1. 启动仿真环境、Gazebo、地图服务及 RViz2
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(sim_gazebo_launch)
        ),

        # 2. 延时 2 秒启动地图处理与 Costmap 节点
        TimerAction(
            period=2.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(map_deal_launch)
                )
            ]
        ),

        # 3. 延时 3.5 秒启动 PID 局部规划器节点 (包含 launch_arguments 设置仿真时间)
        TimerAction(
            period=3.5,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(pid_planner_launch),
                    launch_arguments={'use_sim_time': 'true'}.items()
                )
            ]
        ),

        # 4. 延时 5 秒启动顶层路径规划节点 (motionPlan_node)
        TimerAction(
            period=5.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(motion_plan_launch),
                    launch_arguments={'use_sim_time': 'true'}.items()
                )
            ]
        )
    ])