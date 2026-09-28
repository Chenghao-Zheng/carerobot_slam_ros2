# BD1 Self Balancer

<p align = "justify">
This package contains the code for balancing the bot. The BD1 bot is balanced using the PID Controller.</p>

Launch the arena and test code using the below-mentioned command.

        ros2 launch bd1_self_balancer arena.launch.py
        ros2 run bd1_self_balancer self_balancer

<div style="text" align="center">
    <img src="https://github.com/hari-vickey/ROS2-Self-Balancing-Bot/blob/main/documents/images/test_sbr_arena.png" />
</div>

# 终端1
pkill -9 -f gzserver
pkill -9 -f gzclient
pkill -9 -f self_balancer
pkill -9 -f robot_state_publisher
sleep 2

cd ~/carerobot_slam_ros2
colcon build --packages-select diff_drive_gazebo bd1_self_balancer
source install/setup.bash
source /usr/share/gazebo-11/setup.sh

ros2 launch bd1_self_balancer arena.launch.py

# 终端2
ros2 daemon start
ros2 service call /unpause_physics std_srvs/srv/Empty 