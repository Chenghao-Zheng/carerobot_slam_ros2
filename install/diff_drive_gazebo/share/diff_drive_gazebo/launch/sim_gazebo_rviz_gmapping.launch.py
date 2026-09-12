import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # 路径获取
    diff_drive_gazebo_share = get_package_share_directory('diff_drive_gazebo')
    gazebo_ros_share = get_package_share_directory('gazebo_ros')

    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    # 文件路径
    urdf_file = os.path.join(diff_drive_gazebo_share, 'urdf', 'robot2.urdf')
    rviz_config_file = os.path.join(diff_drive_gazebo_share, 'rviz', 'diff_drive.rviz')
    world_file = os.path.join(diff_drive_gazebo_share, 'worlds', 'big_house.world')

    # 读取 URDF 内容
    with open(urdf_file, 'r') as infp:
        robot_description_config = infp.read()

    # 1. 启动 Gazebo Server
    start_gazebo_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_share, 'launch', 'gzserver.launch.py')
        ),
        launch_arguments={'world': world_file}.items()
    )

    # 2. 启动 Gazebo Client
    start_gazebo_client_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_share, 'launch', 'gzclient.launch.py')
        )
    )

    # 3. 发布 robot_state_publisher
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'robot_description': robot_description_config,
            'publish_frequency': 50.0
        }]
    )

    # 4. 在 Gazebo 中 Spawn 机器人模型（延时 3 秒确保 Gazebo 加载完毕）
    spawn_entity_node = TimerAction(
        period=3.0,
        actions=[
            Node(
                package='gazebo_ros',
                executable='spawn_entity.py',
                arguments=[
                    '-entity', 'diff_drive',
                    '-file', urdf_file,
                    '-x', '1.0', '-y', '0.0', '-z', '0.0'
                ],
                output='screen'
            )
        ]
    )

    # 5. 启动 RViz2
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', rviz_config_file],
        parameters=[{'use_sim_time': use_sim_time}]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation clock if true'
        ),
        start_gazebo_cmd,
        start_gazebo_client_cmd,
        robot_state_publisher_node,
        spawn_entity_node,
        rviz_node
    ])