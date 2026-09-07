
### 常用命令


# 发送极低速度，观察机器人是否平稳前进
 rostopic pub /cmd_vel geometry_msgs/Twist "linear: {x: 0.3, y: 0.0, z: 0.0}" -r 10

git fetch && git reset --hard origin/main && git clean -fd
# git保存
git add .
git commit -m "更新说明"
git push

# 查看tf树
ros2 run tf2_tools view_frames
# 查看 各个节点间的通讯
rqt_graph


# 当ros topic list等无法进行时
ros2 daemon stop
ros2 daemon start


<!-- 编译 -->
# 先编译robot_communication
colcon build --packages-select robot_communication
# 再编译其他的
colcon  build
