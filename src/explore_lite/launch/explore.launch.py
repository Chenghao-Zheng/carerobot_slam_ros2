import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'
        ),
        Node(
            package='explore_lite',
            executable='explore',
            name='explore',
            output='screen',
            remappings=[
                # 将 explore 内部发布的探索目标点 remap 到 /goal_pose
                ('/explore/goal', '/goal_pose'),
                # 关键：将地图话题 remap 到实际的全局代价地图
                ('/map', '/global_cost_map'),
                # 若存在地图更新话题，也可添加（按需）
                # ('/map_updates', '/global_cost_map_updates'),
            ],
            parameters=[{
                'use_sim_time': use_sim_time,
                'robot_base_frame': 'base_footprint',
                'costmap_topic': '/global_cost_map',      # 保留参数（若节点内部使用）
                'costmap_updates_topic': '/global_cost_map_updates',
                'visualize': True,
                'planner_frequency': 0.33,
                'progress_timeout': 30.0,
                'movement_timeout': 10.0,
                'potential_scale': 3.0,
                'orientation_scale': 0.0,
                'gain_scale': 1.0,
                'transform_tolerance': 1.0,
                'min_frontier_size': 0.3,
                'goal_topic': '/goal_pose',
                'goal_tolerance': 0.3,
            }]
        )
    ])