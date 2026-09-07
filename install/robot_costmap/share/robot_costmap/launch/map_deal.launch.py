from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='robot_costmap',
            executable='map_deal_node',
            name='map_deal_node',
            output='screen',
            parameters=[{
                # 显式开启仿真时间同步，确保 ROS 时钟与 Gazebo 一致
                'use_sim_time': True,

                # 全局代价地图参数设定 (用 / 隔开以匹配 C++ 中的 get_parameter)
                'global_cost_map/costdownvalue': 90,
                'global_cost_map/costupvalue': 97,
                'global_cost_map/costdownk': 0.0,
                'global_cost_map/costupk': 0.5,
                'global_cost_map/esdfwidth': 3,
                'global_map/inflate': 0.50,

                # 局部代价地图参数设定
                'local_cost_map/costdownvalue': 75,
                'local_cost_map/costupvalue': 80,
                'local_cost_map/costdownk': 1.0,
                'local_cost_map/costupk': 1.0,

                # 局部地图仿真运行参数 (保证 Width/Height 恢复为 40)
                'local_map/is_use_sim': True,
                'local_map/xmin': -2.0,
                'local_map/ymin': -2.0,
                'local_map/xmax': 2.0,
                'local_map/ymax': 2.0,
                'local_map/resolution': 0.1,  # (2.0 - (-2.0)) / 0.1 = 40 像素格
                'local_map/inflate': 0.50,
                'local_map/virtual_map': 1.0
            }]
        )
    ])