import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    pkg_dir = get_package_share_directory('robot_pid_local_planner')
    param_file = os.path.join(pkg_dir, 'config', 'differential_pid_param.yaml')

    return LaunchDescription([
        Node(
            package='robot_pid_local_planner',
            executable='differential_pid_local_planner_node',
            name='differential_pid_local_planner',
            output='screen',
            parameters=[
                param_file,
                {'use_sim_time': True}  # 强制同步仿真时间
            ],
            # 核心重映射：映射目标点与路径话题
            remappings=[
                ('/move_base_simple/goal', '/goal_pose'),  # 接收 RViz2 的 2D Goal Pose
                # ('/opt_path', '/opt2_path')                # 连接全局规划器的最终路径
            ]
        )
    ])