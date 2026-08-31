#!/usr/bin/env bash
set -e

# 1) 清理旧进程（允许失败）
# ROS 2 中没有 rosnode kill -a，改用 pkill 或 killall 杀掉相关 ROS 2 节点
pkill -f "ros2" 2>/dev/null || true
killall -9 gzserver gzclient 2>/dev/null || true
# 不再有 roscore/rosmaster

sleep 2

# 关闭所有终端（可选）
killall gnome-terminal-server 2>/dev/null || true
