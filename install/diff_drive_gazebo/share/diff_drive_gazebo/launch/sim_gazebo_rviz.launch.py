import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, TimerAction, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    pkg_share = get_package_share_directory('diff_drive_gazebo')
    gazebo_ros_share = get_package_share_directory('gazebo_ros')

    # Paths
    urdf_file = os.path.join(pkg_share, 'urdf', 'robot2.urdf')
    world_file = os.path.join(pkg_share, 'worlds', 'kexueguan205.world')
    map_yaml_file = os.path.join(pkg_share, 'map', 'carto_mapf.yaml')
    rviz_config_file = os.path.join(pkg_share, 'rviz', 'diff_drive.rviz')

    with open(urdf_file, 'r') as infp:
        robot_desc = infp.read()

    return LaunchDescription([
        # 1. 自动注入 GAZEBO_MODEL_PATH 环境变量，确保 package:// 能够正确找到 STL 模型
        SetEnvironmentVariable(
            name='GAZEBO_MODEL_PATH',
            value=[os.path.join(pkg_share, '..')]
        ),

        # 强制使用仿真时间
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'
        ),

        # 2. 启动 Robot State Publisher
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{
                'use_sim_time': True,
                'robot_description': robot_desc
            }]
        ),

        # 3.1 优先启动 Gazebo 后台物理引擎 (gzserver)
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(gazebo_ros_share, 'launch', 'gzserver.launch.py')
            ),
            launch_arguments={'world': world_file}.items()
        ),

        # 3.2 延时 3 秒启动 Gazebo 渲染界面 (gzclient)，给核显预留缓冲时间
        TimerAction(
            period=3.0,
            actions=[
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(
                        os.path.join(gazebo_ros_share, 'launch', 'gzclient.launch.py')
                    )
                )
            ]
        ),

        # 4. 在 Gazebo 中 Spawn 机器人模型
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=[
                '-entity', 'diff_drive',
                '-topic', 'robot_description',
                '-x', '1.0',
                '-y', '0.0',
                '-z', '0.0'
            ],
            output='screen'
        ),

        # 5. ROS 2 Nav2 Map Server + Lifecycle Manager 节点
        Node(
            package='nav2_map_server',
            executable='map_server',
            name='map_server',
            output='screen',
            parameters=[{
                'use_sim_time': True,
                'yaml_filename': map_yaml_file
            }]
        ),
        Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager_map',
            output='screen',
            parameters=[{
                'use_sim_time': True,
                'autostart': True,
                'node_names': ['map_server']
            }]
        ),

        # 6. 静态 TF 广播 (map -> odom)
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='link_broadcaster',
            arguments=['0', '0', '0', '0', '0', '0', 'map', 'odom'],
            parameters=[{'use_sim_time': True}]
        ),

        # 7. 启动 RViz2
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config_file],
            parameters=[{'use_sim_time': True}],
            output='screen'
        )
    ])