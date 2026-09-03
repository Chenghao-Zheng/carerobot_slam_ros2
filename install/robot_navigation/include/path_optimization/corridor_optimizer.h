#ifndef __CORRIDOR_OPTIMIZER_H
#define __CORRIDOR_OPTIMIZER_H

#include <iostream>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <Eigen/Eigen>

// Boost Geometry
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/linestring.hpp>

// OSQP-Eigen
#include <OsqpEigen/OsqpEigen.h>

// ROS 2 可视化
#include <visualization_msgs/msg/marker_array.hpp>

using namespace std;
using namespace Eigen;
namespace bg = boost::geometry;
using Point_bg = bg::model::d2::point_xy<double>;
using Polygon_bg = bg::model::polygon<Point_bg>;
using Linestring_bg = bg::model::linestring<Point_bg>;

class Corridor_Optimizer
{
private:
    // ROS 2 节点指针 (修复编译错误的关键项)
    rclcpp::Node::SharedPtr node_;

    // 地图参数
    double resolution_;
    double origin_x_;
    double origin_y_;
    int width_;
    int height_;
    std::vector<int> map_data_;

    // 优化参数
    double max_corridor_width_;
    double extend_length_;
    double safe_margin_;

    // ROS 2 发布器
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr corridor_pub_;

    // 内部功能函数 (私有)
    vector<Vector2d> simplifyPath(const vector<Vector2d>& path, double corner_deg, int corner_dilate);
    vector<array<double, 8>> convexCorridor(const vector<Vector2d>& path_xy);
    vector<Polygon_bg> generateCorridorsOptimized(const vector<Vector2d>& path_xy, vector<array<double, 8>>& rects);
    vector<Vector2d> minimumSnapSolver(const vector<Polygon_bg>& corridor, const vector<Vector2d>& path, int N, int dim, double lambda_center);
    
    // 几何工具函数
    bool pointInPolygon(const Polygon_bg &poly, double x, double y);
    vector<Polygon_bg> splitPolygonByLine(const Polygon_bg &poly, const pair<double,double>& p1, const pair<double,double>& p2);

    // 坐标转换
    Vector2i worldToMap(const Vector2d& world_pt);
    Vector2d mapToWorld(const Vector2i& grid_pt);
    bool isOccupied(int x, int y);

private:
    std::vector<std::vector<int>> grid_;

    void world2Grid(const Eigen::Vector2d& world, int& gx, int& gy);
    Eigen::Vector2d grid2World(int gx, int gy);
    std::vector<double> computeAngles(const std::vector<Eigen::Vector2d>& points);
    Polygon_bg rectToPolygon(const std::array<double, 8>& rect);
    std::pair<double, double> polygonCentroid(const Polygon_bg& poly);
    std::vector<std::pair<int, int>> polygonObstaclesInSubgrid(const Polygon_bg& poly, int min_x, int min_y);
    Eigen::MatrixXd makeDiffMatrix(int order, int N);
    void polygonToInequalities(const Polygon_bg& poly, Eigen::MatrixXd& A, Eigen::VectorXd& b);

public:
    typedef shared_ptr<Corridor_Optimizer> Ptr;

    Corridor_Optimizer();
    ~Corridor_Optimizer();

    // 初始化 ROS 2 参数和 Publisher
    void InitParams(rclcpp::Node::SharedPtr node);

    // 每次规划前更新地图数据
    void updateMap(double res, double ox, double oy, int w, int h, const std::vector<int>& map);

    // 核心接口
    vector<Vector2d> optimizePathWithCorridor(const vector<Vector2d>& raw_world_path);

    // 发布安全走廊用于 RViz 显示
    void visualCorridorsPolygons(const vector<Polygon_bg>& corridors);
};

#endif