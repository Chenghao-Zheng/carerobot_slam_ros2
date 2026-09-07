#ifndef FRONTIER_SEARCH_H_
#define FRONTIER_SEARCH_H_

#include <cstdint>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>

namespace frontier_exploration
{
struct Frontier {
  std::uint32_t size;
  double min_distance;
  double cost;
  geometry_msgs::msg::Point initial;
  geometry_msgs::msg::Point centroid;
  geometry_msgs::msg::Point middle;
  std::vector<geometry_msgs::msg::Point> points;
};

class FrontierSearch
{
public:
  FrontierSearch() = default;

  FrontierSearch(nav2_costmap_2d::Costmap2D* costmap, double potential_scale,
                 double gain_scale, double min_frontier_size);

  std::vector<Frontier> searchFrom(geometry_msgs::msg::Point position);

protected:
  Frontier buildNewFrontier(unsigned int initial_cell, unsigned int reference,
                            std::vector<bool>& frontier_flag);

  bool isNewFrontierCell(unsigned int idx,
                         const std::vector<bool>& frontier_flag);

  double frontierCost(const Frontier& frontier);

private:
  nav2_costmap_2d::Costmap2D* costmap_{nullptr};
  unsigned char* map_{nullptr};
  unsigned int size_x_{0}, size_y_{0};
  double potential_scale_{0.0}, gain_scale_{0.0};
  double min_frontier_size_{0.0};
};
}  // namespace frontier_exploration

#endif