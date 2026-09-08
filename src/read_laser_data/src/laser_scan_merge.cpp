#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/crop_box.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <Eigen/Dense>
#include <pcl/filters/radius_outlier_removal.h>

class LaserScanMerger : public rclcpp::Node {
public:
    LaserScanMerger() : Node("laser_scan_merger") {
        // 订阅两个原始单线二维 LaserScan 话题
        scan1_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan1", 10, std::bind(&LaserScanMerger::scan1Callback, this, std::placeholders::_1));
        scan2_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan2", 10, std::bind(&LaserScanMerger::scan2Callback, this, std::placeholders::_1));

        // 发布合并后的二维 LaserScan 话题 (/scan) 及调试点云
        scan_pub_ = this->create_publisher<sensor_msgs::msg::LaserScan>("/scan", 10);
        point_cloud_1_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/point_cloud_1", 10);
        point_cloud_2_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/point_cloud_2", 10);
        point_cloud_merged_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/point_cloud_merged", 10);
    }

private:
    // 回调函数，处理前雷达 LaserScan
    void scan1Callback(const sensor_msgs::msg::LaserScan::SharedPtr scan1) {
        projector_.projectLaser(*scan1, cloud1_);  // 2D LaserScan 转为 3D 点云
        pcl::fromROSMsg(cloud1_, *pcl_cloud1_);

        // 前雷达在 base_link 正前方 X = +0.15m 处，将其对齐到 base_link 中心
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.translation() << 0.15, 0.0, 0.0;
        pcl::transformPointCloud(*pcl_cloud1_, *pcl_cloud1_, transform);

        // 更新点云并发布调试话题
        pcl::toROSMsg(*pcl_cloud1_, cloud1_);
        cloud1_.header.frame_id = "base_link";
        point_cloud_1_pub_->publish(cloud1_);

        has_scan1_ = true;
        mergeAndPublish(scan1->header);
    }

    // 回调函数，处理后雷达 LaserScan
    void scan2Callback(const sensor_msgs::msg::LaserScan::SharedPtr scan2) {
        projector_.projectLaser(*scan2, cloud2_);  // 2D LaserScan 转为 3D 点云
        pcl::fromROSMsg(cloud2_, *pcl_cloud2_);

        // 后雷达在 base_link 正后方 X = -0.15m 处，且物理安装旋转了 180 度 (M_PI)
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.translation() << -0.15, 0.0, 0.0;
        transform.rotate(Eigen::AngleAxisf(M_PI, Eigen::Vector3f::UnitZ()));
        pcl::transformPointCloud(*pcl_cloud2_, *pcl_cloud2_, transform);

        // 更新点云并发布调试话题
        pcl::toROSMsg(*pcl_cloud2_, cloud2_);
        cloud2_.header.frame_id = "base_link";
        point_cloud_2_pub_->publish(cloud2_);

        has_scan2_ = true;
        mergeAndPublish(scan2->header);
    }

    // 合并点云并转化回 2D LaserScan 发布
    void mergeAndPublish(const std_msgs::msg::Header& header) {
        if (!has_scan1_ || !has_scan2_) {
            return;  // 等待两个雷达数据均到达后再合并
        }

        // 1. 合并前后雷达点云
        pcl::PointCloud<pcl::PointXYZ> merged_pcl_cloud;
        merged_pcl_cloud += *pcl_cloud1_;
        merged_pcl_cloud += *pcl_cloud2_;

        // 2. CropBox 滤波器：切除车体自身范围内部的反射点 (正方形 -0.2m ~ 0.2m)
        Eigen::Vector4f min_point(-0.20, -0.20, -1.0, 1.0);
        Eigen::Vector4f max_point(0.20, 0.20, 1.0, 1.0);

        pcl::CropBox<pcl::PointXYZ> crop_box_filter;
        crop_box_filter.setInputCloud(merged_pcl_cloud.makeShared());
        crop_box_filter.setMin(min_point);
        crop_box_filter.setMax(max_point);
        crop_box_filter.setNegative(true); // 保留正方形区域外部的点

        pcl::PointCloud<pcl::PointXYZ> crop_filtered_cloud;
        crop_box_filter.filter(crop_filtered_cloud);

        // 3. RadiusOutlierRemoval 半径滤波器：去除噪点
        pcl::RadiusOutlierRemoval<pcl::PointXYZ> radius_filter;
        radius_filter.setInputCloud(crop_filtered_cloud.makeShared());
        radius_filter.setRadiusSearch(0.1);
        radius_filter.setMinNeighborsInRadius(2);

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
        radius_filter.filter(*cloud_filtered);

        // 4. 发布合并并滤波后的 3D 点云话题
        sensor_msgs::msg::PointCloud2 merged_cloud_msg;
        pcl::toROSMsg(*cloud_filtered, merged_cloud_msg);
        merged_cloud_msg.header = header;
        merged_cloud_msg.header.frame_id = "base_link";
        point_cloud_merged_pub_->publish(merged_cloud_msg);

        // 5. 将点云转换为 360 度全视角的 2D LaserScan
        sensor_msgs::msg::LaserScan merged_scan;
        pointcloudToLaserScan(merged_cloud_msg, merged_scan);
        merged_scan.header = header;
        merged_scan.header.frame_id = "merged_laser";

        // 发布合并后的 2D 雷达话题
        scan_pub_->publish(merged_scan);
    }

    // 从 PointCloud2 还原为二维 LaserScan 结构
    void pointcloudToLaserScan(const sensor_msgs::msg::PointCloud2& cloud, sensor_msgs::msg::LaserScan& laser_scan) {
    laser_scan.header = cloud.header;
    laser_scan.angle_min = -M_PI;
    laser_scan.angle_max = M_PI;
    laser_scan.angle_increment = 2.0 * M_PI / 360.0; // 360 个采样点
    laser_scan.time_increment = 0.0;
    laser_scan.scan_time = 0.1;
    laser_scan.range_min = 0.15; // 盲区最小值
    laser_scan.range_max = 8.0;  // 设定有效最大量程（根据实际环境调整，如 8.0m 或 10.0m）

    // 1. 初始化数组，默认填充无穷大
    laser_scan.ranges.resize(360, std::numeric_limits<float>::infinity());

    pcl::PointCloud<pcl::PointXYZ> pcl_cloud;
    pcl::fromROSMsg(cloud, pcl_cloud);

    // 2. 填充扫到的障碍物最近距离
    for (const auto& point : pcl_cloud.points) {
        float angle = std::atan2(point.y, point.x);
        float range = std::hypot(point.x, point.y);

        if (range < laser_scan.range_min || range > laser_scan.range_max) {
            continue;
        }

        int index = static_cast<int>(std::round((angle - laser_scan.angle_min) / laser_scan.angle_increment));
        if (index >= 0 && index < 360) {
            if (range < laser_scan.ranges[index]) {
                laser_scan.ranges[index] = range;
            }
        }
    }

    // 3. 关键修正：将所有未扫到障碍物（infinity）的角度替换为 range_max
    //    这样 Gmapping 才能收到“前方空旷”的信息，从而快速清除灰色阴影！
    for (auto &range : laser_scan.ranges) {
        if (std::isinf(range) || range > laser_scan.range_max) {
            range = laser_scan.range_max;
        }
    }
}

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan1_sub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan2_sub_;
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr scan_pub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_1_pub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_2_pub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_merged_pub_;

    laser_geometry::LaserProjection projector_;
    sensor_msgs::msg::PointCloud2 cloud1_, cloud2_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud1_ = pcl::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
    pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud2_ = pcl::make_shared<pcl::PointCloud<pcl::PointXYZ>>();

    bool has_scan1_{false};
    bool has_scan2_{false};
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LaserScanMerger>());
    rclcpp::shutdown();
    return 0;
}