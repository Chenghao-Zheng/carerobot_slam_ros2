from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='keyboard_control',
            executable='keyboard_control',
            name='keyboard_control',
            output='screen',
            parameters=[{
                'max_linear_speed': 1.0,
                'max_angular_speed': 2.0
            }]
        )
    ])