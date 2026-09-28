-- Copyright 2016 The Cartographer Authors
--
-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at
--
--      http://www.apache.org/licenses/LICENSE-2.0
--
-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

include "map_builder.lua"
include "trajectory_builder.lua"

options = {
  map_builder = MAP_BUILDER,
  trajectory_builder = TRAJECTORY_BUILDER,
  map_frame = "map",                     -- 地图坐标系
  tracking_frame = "base_link",          -- 跟踪坐标系
  published_frame = "odom",              -- 发布位姿坐标系
  odom_frame = "odom",                   -- 里程计坐标系
  provide_odom_frame = false,            -- 由外部里程计（Gazebo）提供 odom
  publish_frame_projected_to_2d = true,  -- 姿态限制在 2D 平面
  use_pose_extrapolator = true,          -- 使用位姿推算器
  use_odometry = true,                   -- 使用 Gazebo 编码器里程计
  use_nav_sat = false,
  use_landmarks = false,
  num_laser_scans = 1,                   -- 订阅融合后的单条 /scan 话题
  num_multi_echo_laser_scans = 0,
  num_subdivisions_per_laser_scan = 1,
  num_point_clouds = 0,
  lookup_transform_timeout_sec = 0.2,
  submap_publish_period_sec = 0.3,
  pose_publish_period_sec = 5e-3,
  trajectory_publish_period_sec = 30e-3,
  rangefinder_sampling_ratio = 1.0,      -- 使用 100% 的雷达数据
  odometry_sampling_ratio = 1.0,
  fixed_frame_pose_sampling_ratio = 1.0,
  imu_sampling_ratio = 1.0,
  landmarks_sampling_ratio = 1.0,
}

TRAJECTORY_BUILDER_2D.use_imu_data = false   -- 禁用 IMU 数据
MAP_BUILDER.use_trajectory_builder_2d = true
MAP_BUILDER.collate_by_trajectory = false

-- 激光参数设置
TRAJECTORY_BUILDER_2D.max_range = 10.0
TRAJECTORY_BUILDER_2D.min_range = 0.10
TRAJECTORY_BUILDER_2D.num_accumulated_range_data = 1
TRAJECTORY_BUILDER_2D.submaps.num_range_data = 60
TRAJECTORY_BUILDER_2D.missing_data_ray_length = 5.
TRAJECTORY_BUILDER_2D.submaps.range_data_inserter.probability_grid_range_data_inserter.insert_free_space = true

-- 前端 Ceres 求解器匹配权重
TRAJECTORY_BUILDER_2D.ceres_scan_matcher.occupied_space_weight = 10.
TRAJECTORY_BUILDER_2D.ceres_scan_matcher.translation_weight = 10.
TRAJECTORY_BUILDER_2D.ceres_scan_matcher.rotation_weight = 40.
TRAJECTORY_BUILDER_2D.ceres_scan_matcher.ceres_solver_options.max_num_iterations = 20
TRAJECTORY_BUILDER_2D.submaps.grid_options_2d.resolution = 0.05

-- 【纯定位配置】只在内存中保留最近 3 个子图做配准，绝不全局建图
TRAJECTORY_BUILDER.pure_localization_trimmer = {
  max_submaps_to_keep = 3,
}

-- 【关键设定】开启实时相关匹配，防止无 IMU 转向时位姿发生漂移
TRAJECTORY_BUILDER_2D.use_online_correlative_scan_matching = true

-- 运动滤波设置（缩小更新门槛，提高响应速度）
TRAJECTORY_BUILDER_2D.motion_filter.max_time_seconds = 0.2
TRAJECTORY_BUILDER_2D.motion_filter.max_distance_meters = 0.02
TRAJECTORY_BUILDER_2D.motion_filter.max_angle_radians = math.rad(0.5)

-- 后端与位姿图全局约束优化
MAP_BUILDER.num_background_threads = 2
MAP_BUILDER.pose_graph.optimize_every_n_nodes = 20
MAP_BUILDER.pose_graph.constraint_builder.min_score = 0.55
MAP_BUILDER.pose_graph.constraint_builder.global_localization_min_score = 0.6
MAP_BUILDER.pose_graph.optimization_problem.odometry_translation_weight = 1e2
MAP_BUILDER.pose_graph.optimization_problem.odometry_rotation_weight = 1e2

return options