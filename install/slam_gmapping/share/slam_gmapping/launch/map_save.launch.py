import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, OpaqueFunction
from launch.substitutions import LaunchConfiguration

def save_map_action(context, *args, **kwargs):
    map_name = LaunchConfiguration('map_name').perform(context)

    # 1. 获取 install 目录路径
    install_share = get_package_share_directory('slam_gmapping')

    # 2. 从 install 路径自动反向推导 src 源码路径
    # install/slam_gmapping/share/slam_gmapping -> src/slam_gmapping
    ws_dir = os.path.abspath(os.path.join(install_share, '../../../../'))
    src_maps_dir = os.path.join(ws_dir, 'src', 'slam_gmapping', 'maps')

    # 3. 自动创建 src/slam_gmapping/maps 文件夹
    os.makedirs(src_maps_dir, exist_ok=True)

    # 4. 拼接完整保存路径
    save_path = os.path.join(src_maps_dir, map_name)

    print(f"\n[Map Saver] 地图将被保存至源码路径: {save_path}.pgm / .yaml\n")

    return [
        ExecuteProcess(
            cmd=['ros2', 'run', 'nav2_map_server', 'map_saver_cli', '-f', save_path],
            output='screen'
        )
    ]

def generate_launch_description():
    map_name_arg = DeclareLaunchArgument(
        'map_name',
        default_value='my_map',
        description='Saved map file name (without extension)'
    )

    return LaunchDescription([
        map_name_arg,
        OpaqueFunction(function=save_map_action)
    ])