import os
from ament_index_python.packages import get_package_share_path
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition

def generate_launch_description():
    package_path = get_package_share_path('cartographer_bringup')
    package_launch_path = os.path.join(get_package_share_path('cartographer_bringup'), 'launch')
    default_rviz_config_path = package_path / 'rviz/view.rviz'
    
    rviz_arg = DeclareLaunchArgument(
        name='rvizconfig', 
        default_value=str(default_rviz_config_path),
        description='Absolute path to rviz config file'
    )
    
    use_rviz_arg = DeclareLaunchArgument(
        name='use_rviz', 
        default_value='true',
    )
    
    cartographer_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [package_launch_path, '/cartographer_launch.py']
        )
    )
    
    base_link_to_laser_tf_node = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='base_link_to_base_laser',
        arguments=['0.0', '0.0', '0.0', '0', '0', '0', 'base_link', 'laser_frame']
    )
    
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
        condition=IfCondition(LaunchConfiguration('use_rviz'))
    )

    return LaunchDescription([
        rviz_arg,
        use_rviz_arg,
        rviz_node,
        cartographer_launch,
        base_link_to_laser_tf_node
    ])