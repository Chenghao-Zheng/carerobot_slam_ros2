#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    # 获取各个功能包的共享路径
    diff_drive_gazebo_share = get_package_share_directory('diff_drive_gazebo')
    read_laser_data_share = get_package_share_directory('read_laser_data')
    robot_costmap_share = get_package_share_directory('robot_costmap')
    robot_nav_share = get_package_share_directory('robot_navigation')
    cartographer_bringup_share = get_package_share_directory('cartographer_bringup')

    # 指向各自的 launch 文件
    sim_gazebo_launch = os.path.join(diff_drive_gazebo_share, 'launch', 'sim_gazebo_rviz.launch.py')
    laser_merge_launch = os.path.join(read_laser_data_share, 'launch', 'scan_merge.launch.py')
    localization_launch = os.path.join(cartographer_bringup_share, 'launch', 'localization_imu_odom_without.launch.py')
    map_deal_launch = os.path.join(robot_costmap_share, 'launch', 'map_deal.launch.py')
    dwa_planner_launch = os.path.join(robot_nav_share, 'launch', 'differential_dwa.launch.py')
    motion_plan_launch = os.path.join(robot_nav_share, 'launch', 'motionPlan.launch.py')

    return LaunchDescription([
        # 1. 启动仿真环境、Gazebo、地图服务及 RViz2
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(sim_gazebo_launch)
        ),

        # 1.5 延时 1 秒启动双雷达融合节点 (/scan1 + /scan2 -> /scan)
        TimerAction(
            period=1.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(laser_merge_launch),
                    launch_arguments={'use_sim_time': 'true'}.items()
                )
            ]
        ),

        # 1.8 延时 2 秒启动 Cartographer 纯定位
        #     （必须在雷达融合之后，地图处理之前）
        TimerAction(
            period=2.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(localization_launch),
                    launch_arguments={
                        'use_sim_time': 'true',
                        'use_rviz': 'false',
                        'load_state_filename': '/home/zheng/carerobot_slam_ros2/src/cartographer_bringup/maps/yahboom_map.pbstream'
                    }.items()
                )
            ]
        ),

        # 2. 延时 4 秒启动地图处理与 Costmap 节点
        TimerAction(
            period=4.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(map_deal_launch),
                    launch_arguments={'use_sim_time': 'true'}.items()
                )
            ]
        ),

        # 3. 延时 5.5 秒启动 DWA 局部规划器节点
        TimerAction(
            period=5.5,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(dwa_planner_launch),
                    launch_arguments={'use_sim_time': 'true'}.items()
                )
            ]
        ),

        # 4. 延时 7 秒启动顶层路径规划节点 (motionPlan_node)
        TimerAction(
            period=7.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(motion_plan_launch),
                    launch_arguments={'use_sim_time': 'true'}.items()
                )
            ]
        )
    ])