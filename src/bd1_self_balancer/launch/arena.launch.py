import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node


def generate_launch_description():
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    pkg_diff_drive = get_package_share_directory('diff_drive_gazebo')

    urdf_file = os.path.join(pkg_diff_drive, 'urdf', 'STM32-V2-V1.SLDASM.urdf')
    world_file = os.path.join(pkg_diff_drive, 'worlds', 'kexueguan205.world')

    with open(urdf_file, 'r') as f:
        robot_urdf = f.read()

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'use_sim_time': True, 'robot_description': robot_urdf}],
    )

    gzserver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py')
        ),
        launch_arguments={'world': world_file, 'pause': 'true'}.items()
    )

    spawn = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'stm32_bot', '-topic', 'robot_description',
                   '-x', '0', '-y', '0', '-z', '0.0'],
        output='screen'
    )

    self_balancer = Node(
        package='bd1_self_balancer',
        executable='self_balancer',
        output='screen',
        parameters=[{
            'Kp': 3.0,
            'Ki': 0.0,
            'Kd': 25.0,
            'output_scale': 1.0,
            'deadband': 0.03,
            'tilt_axis': 'pitch',
            'invert': True,
            'max_speed': 1.5,
        }],
    )

    return LaunchDescription([
        gzserver,
        robot_state_publisher_node,
        spawn,
        RegisterEventHandler(OnProcessExit(
            target_action=spawn,
            on_exit=[self_balancer],
        )),
    ])