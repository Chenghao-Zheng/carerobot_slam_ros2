import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    # 启动双雷达融合节点
    merged_scan = Node(
        package='read_laser_data',
        executable='merger_node',
        name='merger_node',
        output='screen',
        emulate_tty=True
    )

    # 发布静态 TF：base_link -> merged_laser (融合后雷达放置在机器人中心上方 0.1m 处)
    tf2_node = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='static_tf_pub_laser_merged',
        arguments=['0', '0', '0.1', '0', '0', '0', '1', 'base_link', 'merged_laser'],
    )

    return LaunchDescription([
        merged_scan,
        tf2_node,
    ])