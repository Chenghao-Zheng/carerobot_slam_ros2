#!/usr/bin/env python3
"""Path tracking local planner aligned with differential_dwa C++ node interfaces and parameters.

This node replaces DWA with a full Python path tracker compatible with the ROS 2
`robot_navigation` topics (/opt_path, /carto_odom, /cmd_vel_auto, etc.), fully aligned
with the C++ DWA cost functions and dynamic window logic.
"""
import math
import heapq

import rclpy
from geometry_msgs.msg import PoseStamped, Twist
from nav_msgs.msg import OccupancyGrid, Path, Odometry
from rclpy.node import Node
from rclpy.qos import (
    DurabilityPolicy,
    QoSProfile,
    ReliabilityPolicy,
    qos_profile_sensor_data,
)
from rclpy.time import Time
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Float32, String
from visualization_msgs.msg import Marker, MarkerArray
from tf2_ros import Buffer, TransformException, TransformListener


def normalize_angle(angle):
    return math.atan2(math.sin(angle), math.cos(angle))


def yaw_from_quat(q):
    siny_cosp = 2.0 * (q.w * q.z + q.x * q.y)
    cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z)
    return math.atan2(siny_cosp, cosy_cosp)


class LocalPathTracker(Node):
    def __init__(self):
        super().__init__("dwa_planner")
        defaults = {
            "HZ": 20.0,
            "path_topic": "/opt_path",
            "cmd_vel_topic": "/cmd_vel_auto",
            "odom_topic": "/carto_odom",
            "scan_topic": "/scan",
            "local_trajectory_topic": "/selected_trajectory",
            "local_costmap_topic": "/local_costmap",
            "global_costmap_topic": "/local_map_inflate",
            "ROBOT_FRAME": "base_link",
            "global_frame": "map",
            "TARGET_VELOCITY": 0.8,
            "MAX_VELOCITY": 1.0,
            "MIN_VELOCITY": 0.0,
            "MAX_YAWRATE": 1.5,
            "MAX_ACCELERATION": 0.6,
            "MAX_D_YAWRATE": 3.0,
            "LOOKAHEAD_DIST": 0.65,
            "GOAL_THRESHOLD": 0.2,
            "TEMP_GOAL_RADIUS": 1.5,
            "ROBOT_RADIUS": 0.265,
            "SAFETY_MARGIN": 0.035,
            "LASER_MAX_RANGE": 3.0,
            "PREDICT_TIME": 2.0,
            "static_lethal_cost": 100,
            "static_cost_weight": 2.0,
            "heading_stop_angle": 1.0,       # ANGLE_A
            "turn_exit_angle": 0.15,         # ANGLE_B
            "waypoint_tolerance": 0.09,
            "path_search_window": 30,
            "scan_timeout": 0.6,
            "local_costmap_size": 4.0,
            "local_costmap_resolution": 0.05,
            "local_inflation_radius": 0.40,
            # 与 C++ 完全对齐的 DWA 代价权重与采样分辨率[cite: 18]
            "VELOCITY_RESOLUTION": 0.05,
            "YAWRATE_RESOLUTION": 0.05,
            "TO_GOAL_COST_GAIN": 0.3,
            "SPEED_COST_GAIN": 0.2,
            "OBSTACLE_COST_GAIN": 10.0,
            "EVAL_DT": 0.4,
        }
        for name, value in defaults.items():
            self.declare_parameter(name, value)

        self.path = []
        self.last_path_end = None
        self.last_path_len = 0
        self.global_costmap = None
        self.robot_world_pose = None
        self.enforce_static_costmap = False
        self.turning_in_place = False
        self.path_frame = str(self.get_parameter("global_frame").value)
        self.current_index = 0
        self.scan_points = []
        self.last_scan_time = None
        self.active = False
        self.current_v = 0.0
        self.current_w = 0.0
        self.no_motion_since = None
        self.last_status = None
        self.recovery_start = None
        self.recovery_turn_sign = 1.0

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # 订阅与发布
        self.path_sub = self.create_subscription(
            Path, str(self.get_parameter("path_topic").value), self.on_path, 10
        )
        self.scan_sub = self.create_subscription(
            LaserScan,
            str(self.get_parameter("scan_topic").value),
            self.on_scan,
            qos_profile_sensor_data,
        )
        self.odom_sub = self.create_subscription(
            Odometry,
            str(self.get_parameter("odom_topic").value),
            self.on_odom,
            1,
        )
        self.vel_control_sub = self.create_subscription(
            Twist,
            "/velocity_control",
            self.on_velocity_control,
            1,
        )

        map_qos = QoSProfile(depth=1)
        map_qos.reliability = ReliabilityPolicy.RELIABLE
        map_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.global_costmap_sub = self.create_subscription(
            OccupancyGrid,
            str(self.get_parameter("global_costmap_topic").value),
            self.on_global_costmap,
            map_qos,
        )

        self.cmd_pub = self.create_publisher(
            Twist, str(self.get_parameter("cmd_vel_topic").value), 1
        )
        self.local_path_pub = self.create_publisher(
            Path, "/local_path", 1
        )
        self.selected_traj_pub = self.create_publisher(
            Marker, str(self.get_parameter("local_trajectory_topic").value), 1
        )
        self.local_costmap_pub = self.create_publisher(
            OccupancyGrid,
            str(self.get_parameter("local_costmap_topic").value),
            10,
        )
        self.progress_pub = self.create_publisher(
            Float32, "sweepbot/path_progress", 10
        )
        self.status_pub = self.create_publisher(String, "sweepbot/tracker_status", 10)

        hz = float(self.get_parameter("HZ").value)
        control_period = 1.0 / hz if hz > 0 else 0.05
        self.timer = self.create_timer(control_period, self.tick)
        self.get_logger().info("LocalPathTracker (C++ aligned DWA Python node) ready.")

    def on_path(self, msg):
        new_path = [(p.pose.position.x, p.pose.position.y) for p in msg.poses]
        new_len = len(new_path)
        new_end = new_path[-1] if new_path else None

        path_changed = False
        if new_len != self.last_path_len:
            path_changed = True
        elif self.last_path_end is not None and new_end is not None:
            if math.hypot(new_end[0] - self.last_path_end[0],
                          new_end[1] - self.last_path_end[1]) > 0.1:
                path_changed = True
        else:
            path_changed = True

        if not path_changed and self.path:
            self.update_path_index(self.robot_world_pose[0] if self.robot_world_pose else 0.0,
                                   self.robot_world_pose[1] if self.robot_world_pose else 0.0)
            self.active = True
            return

        self.path_frame = msg.header.frame_id or str(self.get_parameter("global_frame").value)
        self.path = new_path
        self.last_path_len = new_len
        self.last_path_end = new_end
        self.current_index = 0
        self.active = bool(self.path)
        self.no_motion_since = None
        self.turning_in_place = False
        self.publish_status(f"PATH_RECEIVED:{len(self.path)}")
        if not self.active:
            self.stop()

    def on_odom(self, msg):
        self.current_v = msg.twist.twist.linear.x
        self.current_w = msg.twist.twist.angular.z

    def on_velocity_control(self, msg):
        target_v = math.hypot(msg.linear.x, msg.linear.y)
        self.set_parameters([rclpy.parameter.Parameter("TARGET_VELOCITY", value=target_v)])

    def on_scan(self, msg):
        raw_points = []
        limit = float(self.get_parameter("LASER_MAX_RANGE").value)
        for i, distance in enumerate(msg.ranges):
            if not math.isfinite(distance) or distance < msg.range_min:
                continue
            if distance > limit:
                continue
            angle = msg.angle_min + i * msg.angle_increment
            raw_points.append((distance * math.cos(angle), distance * math.sin(angle)))

        base_frame = str(self.get_parameter("ROBOT_FRAME").value)
        scan_frame = msg.header.frame_id or base_frame
        if scan_frame != base_frame:
            try:
                transform = self.tf_buffer.lookup_transform(
                    base_frame, scan_frame, Time.from_msg(msg.header.stamp)
                )
            except TransformException:
                try:
                    transform = self.tf_buffer.lookup_transform(
                        base_frame, scan_frame, Time()
                    )
                except TransformException as exc:
                    self.get_logger().warn(f"Cannot transform laser scan: {exc}")
                    return
            tx = transform.transform.translation.x
            ty = transform.transform.translation.y
            angle = yaw_from_quat(transform.transform.rotation)
            cosine, sine = math.cos(angle), math.sin(angle)
            points = [
                (tx + cosine * x - sine * y, ty + sine * x + cosine * y)
                for x, y in raw_points
            ]
        else:
            points = raw_points
        self.scan_points = points
        self.last_scan_time = self.get_clock().now()
        self.publish_local_costmap(msg)

    def on_global_costmap(self, msg):
        self.global_costmap = msg

    def publish_local_costmap(self, scan):
        base_frame = str(self.get_parameter("ROBOT_FRAME").value)
        try:
            transform = self.tf_buffer.lookup_transform(
                self.path_frame, base_frame, Time()
            )
        except TransformException:
            return
        robot_x = transform.transform.translation.x
        robot_y = transform.transform.translation.y
        robot_yaw = yaw_from_quat(transform.transform.rotation)

        resolution = float(self.get_parameter("local_costmap_resolution").value)
        map_size = float(self.get_parameter("local_costmap_size").value)
        width = max(10, int(round(map_size / resolution)))
        height = width
        origin_x = robot_x - 0.5 * width * resolution
        origin_y = robot_y - 0.5 * height * resolution
        obstacle = [False] * (width * height)

        for px, py in self.scan_points:
            world_x = robot_x + math.cos(robot_yaw) * px - math.sin(robot_yaw) * py
            world_y = robot_y + math.sin(robot_yaw) * px + math.cos(robot_yaw) * py
            cell_x = int((world_x - origin_x) / resolution)
            cell_y = int((world_y - origin_y) / resolution)
            if 0 <= cell_x < width and 0 <= cell_y < height:
                obstacle[cell_y * width + cell_x] = True

        inflation_radius = float(self.get_parameter("local_inflation_radius").value)
        lethal_radius = (
            float(self.get_parameter("ROBOT_RADIUS").value)
            + float(self.get_parameter("SAFETY_MARGIN").value)
        )
        distances = [float("inf")] * len(obstacle)
        queue = []
        for index, occupied in enumerate(obstacle):
            if occupied:
                distances[index] = 0.0
                heapq.heappush(queue, (0.0, index))

        while queue:
            distance, index = heapq.heappop(queue)
            if distance > distances[index] or distance >= inflation_radius:
                continue
            x, y = index % width, index // width
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1),
                           (1, 1), (1, -1), (-1, 1), (-1, -1)):
                nx, ny = x + dx, y + dy
                if not (0 <= nx < width and 0 <= ny < height):
                    continue
                neighbor = ny * width + nx
                candidate = distance + resolution * math.hypot(dx, dy)
                if candidate < distances[neighbor] and candidate <= inflation_radius:
                    distances[neighbor] = candidate
                    heapq.heappush(queue, (candidate, neighbor))

        costs = [0] * len(obstacle)
        for index, distance in enumerate(distances):
            if not math.isfinite(distance):
                continue
            if distance <= lethal_radius:
                costs[index] = 100
            else:
                ratio = (inflation_radius - distance) / max(
                    resolution, inflation_radius - lethal_radius
                )
                costs[index] = max(1, min(99, int(round(99.0 * ratio))))

        for y in range(height):
            world_y = origin_y + (y + 0.5) * resolution
            for x in range(width):
                world_x = origin_x + (x + 0.5) * resolution
                static_cost = self.global_cost_at_world(world_x, world_y)
                if static_cost is not None:
                    index = y * width + x
                    costs[index] = max(costs[index], static_cost)

        grid = OccupancyGrid()
        grid.header.stamp = self.get_clock().now().to_msg()
        grid.header.frame_id = self.path_frame
        grid.info.resolution = resolution
        grid.info.width = width
        grid.info.height = height
        grid.info.origin.position.x = origin_x
        grid.info.origin.position.y = origin_y
        grid.info.origin.orientation.w = 1.0
        grid.data = costs
        self.local_costmap_pub.publish(grid)

    def tick(self):
        if not self.active or not self.path:
            return
        
        scan_timeout = float(self.get_parameter("scan_timeout").value)
        if self.last_scan_time is None or (
            self.get_clock().now() - self.last_scan_time
        ).nanoseconds * 1e-9 > scan_timeout:
            self.stop()
            self.publish_status("WAITING_FOR_SCAN")
            return

        pose = self.robot_pose()
        if pose is None:
            self.stop()
            return

        rx, ry, yaw = pose
        self.robot_world_pose = pose

        self.update_path_index(rx, ry)
        gx, gy = self.lookahead_target(rx, ry)

        # 转换至机器人局部坐标系[cite: 18]
        dx = gx - rx
        dy = gy - ry
        cos_yaw = math.cos(yaw)
        sin_yaw = math.sin(yaw)
        local_goal_x = dx * cos_yaw + dy * sin_yaw
        local_goal_y = -dx * sin_yaw + dy * cos_yaw

        angle_to_goal = math.atan2(dy, dx)
        local_goal_yaw = normalize_angle(angle_to_goal - yaw)

        dist_to_goal = math.hypot(local_goal_x, local_goal_y)
        angle_error = abs(local_goal_yaw)

        goal_tolerance = float(self.get_parameter("GOAL_THRESHOLD").value)
        dist_to_final = math.hypot(self.path[-1][0] - rx, self.path[-1][1] - ry)

        # 1. 终点停止逻辑[cite: 18]
        if dist_to_final < goal_tolerance:
            cmd = Twist()
            cmd.linear.x = 0.0
            if abs(local_goal_yaw) < 0.1:
                cmd.angular.z = 0.0
            else:
                max_w = float(self.get_parameter("MAX_YAWRATE").value)
                cmd.angular.z = max(-max_w, min(max_w, local_goal_yaw * 1.2))
            self.cmd_pub.publish(cmd)
            self.current_v, self.current_w = 0.0, cmd.angular.z
            if self.current_index >= len(self.path) - 1:
                self.active = False
                self.publish_progress(1.0)
                self.publish_status("GOAL_REACHED")
            return

        # 2. 原地旋转逻辑[cite: 18]
        ANGLE_A = float(self.get_parameter("heading_stop_angle").value)
        ANGLE_B = float(self.get_parameter("turn_exit_angle").value)

        if angle_error > ANGLE_A and dist_to_goal > 0.5:
            self.turning_in_place = True
        elif angle_error < ANGLE_B or dist_to_goal <= 0.1:
            self.turning_in_place = False

        if self.turning_in_place:
            max_w = float(self.get_parameter("MAX_YAWRATE").value)
            cmd = Twist()
            cmd.linear.x = 0.0
            cmd.angular.z = max(-max_w, min(max_w, local_goal_yaw * 1.5))
            self.cmd_pub.publish(cmd)
            self.current_v = 0.0
            self.current_w = cmd.angular.z
            self.publish_status("TURN_IN_PLACE")
            self.publish_progress(self.current_index / max(1, len(self.path) - 1))
            return

        # 3. 动态目标速度平滑缩放[cite: 18]
        target_vel_param = float(self.get_parameter("TARGET_VELOCITY").value)
        if dist_to_goal < 0.5:
            max_vel = 0.1 + 0.5 * (dist_to_goal / 0.5)
            current_target_vel = min(target_vel_param, max_vel)
        else:
            current_target_vel = target_vel_param
            if dist_to_goal < goal_tolerance * 2.0:
                current_target_vel *= (dist_to_goal / (goal_tolerance * 2.0))
                current_target_vel = max(current_target_vel, 0.05)

        target_local = (local_goal_x, local_goal_y)

        # 4. 执行 DWA 选速
        best = self.choose_velocity(target_local, current_target_vel)
        if best is None:
            self.stop()
            self.publish_status("BLOCKED_NO_SAFE_TRAJECTORY")
            return

        v, w, trajectory = best
        cmd = Twist()
        cmd.linear.x = v
        cmd.angular.z = w
        self.cmd_pub.publish(cmd)
        self.current_v, self.current_w = v, w

        self.publish_trajectory(trajectory, rx, ry, yaw)
        self.publish_progress(self.current_index / max(1, len(self.path) - 1))
        self.publish_status("TRACKING")

    def lookahead_target(self, rx, ry):
        if not self.path:
            return rx, ry

        start_idx = min(self.current_index, len(self.path) - 1)
        accumulated = 0.0
        target_idx = start_idx
        current_speed = abs(self.current_v)
        
        # 动态前视距离[cite: 18]
        lookahead = float(self.get_parameter("LOOKAHEAD_DIST").value) + 0.5 * current_speed
        lookahead = max(0.3, min(lookahead, float(self.get_parameter("TEMP_GOAL_RADIUS").value)))

        for i in range(start_idx, len(self.path) - 1):
            seg = math.hypot(self.path[i + 1][0] - self.path[i][0],
                             self.path[i + 1][1] - self.path[i][1])
            if accumulated + seg >= lookahead:
                target_idx = i + 1
                break
            accumulated += seg
            target_idx = i + 1

        target_idx = min(target_idx, len(self.path) - 1)
        dist_to_final = math.hypot(self.path[-1][0] - rx, self.path[-1][1] - ry)
        
        if dist_to_final < float(self.get_parameter("GOAL_THRESHOLD").value) or target_idx == len(self.path) - 1:
            return self.path[-1]

        return self.path[target_idx]

    def calc_to_goal_cost(self, trajectory, goal_x, goal_y):
        end_x, end_y, end_yaw = trajectory[-1]
        dx = goal_x - end_x
        dy = goal_y - end_y
        dist_cost = math.hypot(dx, dy)
        angle_to_goal = math.atan2(dy, dx)
        heading_error = abs(normalize_angle(end_yaw - angle_to_goal))
        return dist_cost + 2.0 * heading_error

    def calc_speed_cost(self, trajectory, target_velocity, v):
        return abs(target_velocity - v)

    def calc_obstacle_cost(self, trajectory):
        if not self.scan_points:
            return 0.0
        safety_dist = float(self.get_parameter("ROBOT_RADIUS").value) + float(self.get_parameter("SAFETY_MARGIN").value)
        total_cost = 0.0
        valid_count = 0

        # 指数型障碍物避障模型[cite: 18]
        for x, y, _ in trajectory:
            min_dist = float('inf')
            for px, py in self.scan_points:
                dist = math.hypot(x - px, y - py)
                if dist < min_dist:
                    min_dist = dist
            if min_dist < safety_dist:
                total_cost += math.exp(-(min_dist / safety_dist)) * 5.0
            valid_count += 1
        return (total_cost / valid_count) if valid_count > 0 else 0.0

    def simulate(self, v, w):
        horizon = float(self.get_parameter("PREDICT_TIME").value)
        hz = float(self.get_parameter("HZ").value)
        dt = 1.0 / hz if hz > 0 else 0.05
        
        x = y = theta = 0.0
        trajectory = []
        steps = max(1, int(math.ceil(horizon / dt)))
        
        for _ in range(steps):
            theta += w * dt
            x += v * math.cos(theta) * dt
            y += v * math.sin(theta) * dt
            trajectory.append((x, y, theta))
        return trajectory

    def choose_velocity(self, target_local, target_velocity):
        eval_dt = float(self.get_parameter("EVAL_DT").value)
        max_dv = float(self.get_parameter("MAX_ACCELERATION").value) * eval_dt
        max_dw = float(self.get_parameter("MAX_D_YAWRATE").value) * eval_dt

        max_v = float(self.get_parameter("MAX_VELOCITY").value)
        min_v = float(self.get_parameter("MIN_VELOCITY").value)
        max_w = float(self.get_parameter("MAX_YAWRATE").value)

        v_min = max(min_v, self.current_v - max_dv)
        if v_min < 0.0:
            v_min = 0.0
        v_max = min(max_v, self.current_v + max_dv)
        
        w_min = max(-max_w, self.current_w - max_dw)
        w_max = min(max_w, self.current_w + max_dw)

        v_res = float(self.get_parameter("VELOCITY_RESOLUTION").value)
        w_res = float(self.get_parameter("YAWRATE_RESOLUTION").value)

        to_goal_gain = float(self.get_parameter("TO_GOAL_COST_GAIN").value)
        speed_gain = float(self.get_parameter("SPEED_COST_GAIN").value)
        obstacle_gain = float(self.get_parameter("OBSTACLE_COST_GAIN").value)

        min_cost = 1e6
        best = None
        goal_x, goal_y = target_local

        # 对齐 C++ 的遍历采样逻辑[cite: 18]
        v = v_min
        while v <= v_max + 1e-5:
            w = w_min
            while w <= w_max + 1e-5:
                trajectory = self.simulate(v, w)
                if not trajectory:
                    w += w_res
                    continue

                to_goal_cost = self.calc_to_goal_cost(trajectory, goal_x, goal_y)
                speed_cost = self.calc_speed_cost(trajectory, target_velocity, v)
                obstacle_cost = self.calc_obstacle_cost(trajectory)

                final_cost = (to_goal_gain * to_goal_cost +
                              speed_gain * speed_cost +
                              obstacle_gain * obstacle_cost)

                if final_cost < min_cost:
                    min_cost = final_cost
                    best = (v, w, trajectory)
                w += w_res
            v += v_res

        if min_cost == 1e6 or best is None:
            return 0.05, 0.0, self.simulate(0.05, 0.0)

        return best

    def update_path_index(self, rx, ry):
        if not self.path or self.current_index >= len(self.path) - 1:
            return

        max_steps = 20
        for _ in range(max_steps):
            if self.current_index >= len(self.path) - 1:
                break
            idx = self.current_index
            x0, y0 = self.path[idx]
            x1, y1 = self.path[idx + 1]
            sx, sy = x1 - x0, y1 - y0
            len_sq = sx * sx + sy * sy
            if len_sq < 1e-9:
                self.current_index += 1
                continue
            proj = ((rx - x0) * sx + (ry - y0) * sy) / len_sq
            dist_to_next = math.hypot(rx - x1, ry - y1)
            dist_to_curr = math.hypot(rx - x0, ry - y0)
            if proj >= 0.5 or dist_to_next < dist_to_curr or dist_to_next < 0.09:
                self.current_index += 1
            else:
                break

    def global_cost_at_world(self, world_x, world_y):
        if self.global_costmap is None:
            return None
        info = self.global_costmap.info
        x = int((world_x - info.origin.position.x) / info.resolution)
        y = int((world_y - info.origin.position.y) / info.resolution)
        if x < 0 or y < 0 or x >= info.width or y >= info.height:
            return 100
        value = self.global_costmap.data[y * info.width + x]
        return 100 if value < 0 else int(value)

    def robot_pose(self):
        base_frame = str(self.get_parameter("ROBOT_FRAME").value)
        try:
            tf = self.tf_buffer.lookup_transform(self.path_frame, base_frame, Time())
        except TransformException as exc:
            self.get_logger().warn(f"Cannot transform {self.path_frame}->{base_frame}: {exc}")
            return None
        trans = tf.transform.translation
        return trans.x, trans.y, yaw_from_quat(tf.transform.rotation)

    def publish_trajectory(self, trajectory, rx, ry, yaw):
        local_path = Path()
        local_path.header.frame_id = str(self.get_parameter("ROBOT_FRAME").value)
        local_path.header.stamp = self.get_clock().now().to_msg()
        for x, y, theta in trajectory:
            pose = PoseStamped()
            pose.header = local_path.header
            pose.pose.position.x = x
            pose.pose.position.y = y
            pose.pose.orientation.z = math.sin(theta * 0.5)
            pose.pose.orientation.w = math.cos(theta * 0.5)
            local_path.poses.append(pose)
        self.local_path_pub.publish(local_path)

        marker = Marker()
        marker.header.frame_id = str(self.get_parameter("ROBOT_FRAME").value)
        marker.header.stamp = self.get_clock().now().to_msg()
        marker.ns = "selected_trajectory"
        marker.type = Marker.LINE_STRIP
        marker.action = Marker.ADD
        marker.scale.x = 0.05
        marker.color.r = 1.0
        marker.color.g = 0.0
        marker.color.b = 0.0
        marker.color.a = 0.8
        marker.pose.orientation.w = 1.0
        for x, y, _ in trajectory:
            p = PoseStamped().pose.position
            p.x = x
            p.y = y
            p.z = 0.0
            marker.points.append(p)
        self.selected_traj_pub.publish(marker)

    def publish_progress(self, value):
        msg = Float32()
        msg.data = float(max(0.0, min(1.0, value)))
        self.progress_pub.publish(msg)

    def publish_status(self, value):
        msg = String()
        msg.data = value
        self.status_pub.publish(msg)
        if value != self.last_status:
            self.get_logger().info(value)
            self.last_status = value

    def stop(self):
        self.current_v = 0.0
        self.current_w = 0.0
        self.cmd_pub.publish(Twist())


def main():
    rclpy.init()
    node = LocalPathTracker()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if rclpy.ok():
            node.stop()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()