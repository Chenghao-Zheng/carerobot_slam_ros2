## 注意事项 v2.0 (ROS 2 版本)

此功能包只放置自定义通讯文件，不编写任何代码[cite: 33]。
相对应的 action 和 msg 必须放入对应的文件夹内[cite: 33]。
自定义的通讯文件需遵循规范命名，例如串口发给视觉的消息命名为 `usart2vision.msg`（2 代表 to）[cite: 33]。

## 若编译遇到问题

在 ROS 2 工作空间根目录下，优先单独编译该消息包：
```bash
colcon build --packages-select robot_communication