import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    # 1. Gazebo + Robot + RViz 启动文件
    gazebo_rviz_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('diff_drive_gazebo'),
                'launch',
                'sim_gazebo_rviz_gmapping.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 2. 双雷达融合节点 (read_laser_data)
    laser_merge_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('read_laser_data'),
                'launch',
                'scan_merge.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 3. Gmapping 建图节点
    gmapping_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('slam_gmapping'),
                'launch',
                'slam_gmapping.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 4. 代价地图 / 地图处理节点 (robot_costmap)
    map_deal_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('robot_costmap'),
                'launch',
                'map_deal.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 5. 全局规划器 (motion_plan)
    motion_plan_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('robot_navigation'),
                'launch',
                'motionPlan.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 6. 局部规划器 (Differential_DWA)
    local_planner_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('robot_navigation'),
                'launch',
                'differential_dwa.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    # 7. 自动探索节点 (explore_lite)
    explore_lite_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('explore_lite'),
                'launch',
                'explore.launch.py'
            )
        ]),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation (Gazebo) clock if true'
        ),
        gazebo_rviz_launch,
        laser_merge_launch,
        gmapping_launch,
        map_deal_launch,
        motion_plan_launch,
        local_planner_launch,
        explore_lite_launch
    ])