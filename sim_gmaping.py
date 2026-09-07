import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    # 获取各个功能包路径
    diff_drive_gazebo_share = get_package_share_directory('diff_drive_gazebo')
    slam_gmapping_share = get_package_share_directory('slam_gmapping')

    # 1. 仿真环境与机器人 Launch (Gazebo + RViz2 + Robot State Publisher)
    gazebo_rviz_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(diff_drive_gazebo_share, 'launch', 'sim_gazebo_rviz_gmapping.launch.py')
        ),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 2. 建图节点 (延时 4 秒启动)
    gmapping_launch = TimerAction(
        period=4.0,
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    os.path.join(slam_gmapping_share, 'launch', 'slam_gmapping.launch.py')
                ),
                launch_arguments={'use_sim_time': use_sim_time}.items()
            )
        ]
    )

    # 3. 键盘控制节点 (延时 5 秒启动，直接通过 Node 加 prefix 强行弹出 xterm 终端)
    keyboard_node = TimerAction(
        period=5.0,
        actions=[
            Node(
                package='keyboard_control',
                executable='keyboard_control',
                name='keyboard_control',
                output='screen',
                parameters=[{
                    'max_linear_speed': 1.0,
                    'max_angular_speed': 2.0
                }],
                prefix='xterm -e'  # 强行弹出独立终端窗口以接收键盘焦点
            )
        ]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'
        ),
        gazebo_rviz_launch,
        gmapping_launch,
        keyboard_node
    ])