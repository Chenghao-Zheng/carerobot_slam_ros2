import os
from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction


def generate_launch_description():
    # ========== 参数（直接改这里即可） ==========
    map_dir = '/home/zheng/carerobot_slam_ros2/src/cartographer_bringup/maps'
    map_name = 'yahboom_map'
    trajectory_id = 0
    resolution = 0.05

    pbstream = f'{map_dir}/{map_name}.pbstream'
    filestem = f'{map_dir}/{map_name}'

    return LaunchDescription([
        # ========== 第 1 步：停止轨迹 ==========
        ExecuteProcess(
            cmd=[
                'ros2', 'service', 'call',
                '/finish_trajectory',
                'cartographer_ros_msgs/srv/FinishTrajectory',
                f'{{trajectory_id: {trajectory_id}}}'
            ],
            output='screen',
        ),

        # ========== 第 2 步：保存 pbstream（延时 2 秒） ==========
        TimerAction(
            period=2.0,
            actions=[
                ExecuteProcess(
                    cmd=[
                        'ros2', 'service', 'call',
                        '/write_state',
                        'cartographer_ros_msgs/srv/WriteState',
                        f"{{filename: '{pbstream}'}}"
                    ],
                    output='screen',
                )
            ]
        ),

        # ========== 第 3 步：转 pgm + yaml（延时 5 秒） ==========
        TimerAction(
            period=5.0,
            actions=[
                ExecuteProcess(
                    cmd=[
                        'ros2', 'run', 'cartographer_ros',
                        'cartographer_pbstream_to_ros_map',
                        f'-map_filestem={filestem}',
                        f'-pbstream_filename={pbstream}',
                        f'-resolution={resolution}'
                    ],
                    output='screen',
                )
            ]
        ),
    ])