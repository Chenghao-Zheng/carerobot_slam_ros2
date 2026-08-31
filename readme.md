
### 常用命令


# 发送极低速度，观察机器人是否平稳前进
 rostopic pub /cmd_vel geometry_msgs/Twist "linear: {x: 0.3, y: 0.0, z: 0.0}" -r 10

git fetch && git reset --hard origin/main && git clean -fd
# git保存
git add .
git commit -m "更新说明"
git push

# 查看tf树
rosrun rqt_tf_tree rqt_tf_tree
# 查看 tf位姿 变化
rosrun tf tf_echo map base_footprint
rosrun tf tf_echo map livox_frame


rosrun tri_steer_gazebo odom_tf_basefootprint

rostopic echo -n 1 /joint_states
rosrun tf tf_echo base_link turn1



<!-- 编译 -->
# 先编译robot_communication
catkin_make  --pkg robot_communication
# 再编译其他的
catkin_make
