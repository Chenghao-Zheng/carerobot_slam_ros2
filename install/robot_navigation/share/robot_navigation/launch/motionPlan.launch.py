import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    pkg_share = get_package_share_directory('robot_navigation')
    pid_param_path = os.path.join(pkg_share, 'config', 'pid_param.yaml')
    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation clock if true'
        ),
        Node(
            package='robot_navigation',
            executable='motionPlan_node',
            name='motionPlan_node',
            output='screen',
            remappings=[
                # ===== 对照ROS1 motionPlan_sim.launch 的 remap =====
                # ROS1: <remap from="/global_map_esdf_display" to="/global_cost_map"/>
                # 把代码里订阅的 /global_map_esdf_display 重映射到 /global_cost_map
                # 因为 map_deal 发布的 /global_cost_map 是 OccupancyGrid 类型，类型匹配
                ('/global_map_esdf_display', '/global_cost_map'),

                # RViz2 的 2D Goal Pose 发布到 /goal_pose
                # 代码里订阅 /move_base_simple/goal，重映射到 /goal_pose
                ('/move_base_simple/goal', '/goal_pose'),

                # ===== 去掉以下错误的 remap =====
                # ('/odom_carto', '/odom')       ← is_sim=true 时代码直接订阅 /odom，不需要remap
                # ('/local_map_esdf', '/local_esdf_map')  ← 类型不匹配，直接订阅 /local_map_esdf
            ],
            parameters=[
                pid_param_path,
                {'use_sim_time': True},
                # ===== 对照ROS1，必须显式设置这些参数 =====
                {'motion_node.is_sim': True},        # ROS1: <param name="motion_node/is_sim" value="true"/>
                {'motion_plan.frame_id': 'map'},      # ROS1: <param name="motion_plan/frame_id" value="map"/>
            ]
        )
    ])
