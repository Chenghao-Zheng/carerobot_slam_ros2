import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    robot_nav_share = get_package_share_directory('robot_navigation')
    
    # 确保路径匹配
    robot_param = os.path.join(robot_nav_share, 'config', 'differential_robot_param.yaml')
    dwa_param = os.path.join(robot_nav_share, 'config', 'differential_dwa_param.yaml')

    parameters_list = []
    if os.path.exists(robot_param):
        parameters_list.append(robot_param)
    if os.path.exists(dwa_param):
        parameters_list.append(dwa_param)
        
    parameters_list.append({'HZ': 20.0, 'use_sim_time': use_sim_time})

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'
        ),
        Node(
            package='robot_navigation',
            executable='Differential_DWA_node',
            name='dwa_planner',  # 统一节点名为 dwa_planner
            output='screen',
            parameters=parameters_list,
            remappings=[
                ('/carto_odom', '/odom'),
                ('/cmd_vel_auto', '/cmd_vel')
            ]
        )
    ])