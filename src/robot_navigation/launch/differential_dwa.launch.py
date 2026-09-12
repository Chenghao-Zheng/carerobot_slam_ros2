import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    robot_nav_share = get_package_share_directory('robot_navigation')

    # 只有一个配置文件，两个变量都指向它即可
    param_file = os.path.join(robot_nav_share, 'config', 'dwa_param.yaml')

    parameters_list = []
    if os.path.exists(param_file):
        parameters_list.append(param_file)
    else:
        print(f"[launch warning] param file not found: {param_file}")

    # 这里只放节点没在 YAML 里写的通用参数，注意键必须和节点名无关，直接是参数名
    parameters_list.append({'use_sim_time': use_sim_time})

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'
        ),
        Node(
            package='robot_navigation',
            executable='Differential_DWA_node',
            name='dwa_planner',            # ← 必须和 YAML 根键一致
            output='screen',
            parameters=parameters_list,
            remappings=[
                ('/carto_odom', '/odom'),   
                ('/cmd_vel_auto', '/cmd_vel')
            ]
        )
    ])