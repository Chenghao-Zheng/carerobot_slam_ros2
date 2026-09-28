"""
  Copyright 2018 The Cartographer Authors
  Copyright 2022 Wyca Robotics (for the ros2 conversion)

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
"""

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import Shutdown

def generate_launch_description():

    default_pbstream = os.path.join(
        get_package_share_directory('cartographer_bringup'),
        'maps', 'yahboom_map.pbstream')

    load_state_filename_arg = DeclareLaunchArgument(
        'load_state_filename',
        default_value=default_pbstream
    )
    
    use_rviz_arg = DeclareLaunchArgument(
        'use_rviz',
        default_value='true',
    )

    # 1. Cartographer 纯定位核心节点（仅负责计算并发布 map -> odom TF 变换）
    cartographer_node = Node(
        package = 'cartographer_ros',
        executable = 'cartographer_node',
        parameters = [{'use_sim_time': True}],
        arguments = [
            '-configuration_directory', os.path.join(
                get_package_share_directory('cartographer_bringup'), 'params'),
            '-configuration_basename', 'ros1_backpack_2d_localization_no_imu.lua',
            '-load_state_filename', LaunchConfiguration('load_state_filename')],
        output = 'screen'
    )
    
    # 2. 静态 TF 发布 (base_link -> laser_frame)
    base_link_to_laser_tf_node = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='base_link_to_base_laser',
        arguments=['0.0', '0.0', '0.0', '0', '0', '0', 'base_link', 'laser_frame']
    ) 

    # 3. RViz2 可视化节点
    rviz_node = Node(
        package = 'rviz2',
        executable = 'rviz2',
        on_exit = Shutdown(),
        arguments = ['-d', FindPackageShare('cartographer_ros').find('cartographer_ros') + '/configuration_files/demo_2d.rviz'],
        parameters = [{'use_sim_time': True}],
        condition=IfCondition(LaunchConfiguration('use_rviz'))
    )

    return LaunchDescription([
        load_state_filename_arg,
        use_rviz_arg,
        base_link_to_laser_tf_node,
        cartographer_node,
        rviz_node,
    ])