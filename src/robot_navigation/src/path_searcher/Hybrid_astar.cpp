#include "path_searcher/Hybrid_astar.h"
#include <rclcpp/rclcpp.hpp>
#include <sstream>

using namespace std;
using namespace Eigen;

// 构造函数
Hybrid_astar::Hybrid_astar()
{
}

Hybrid_astar::~Hybrid_astar()
{
  for (int i = 0; i < allocate_num_; i++)
  {
    delete path_node_pool_[i];
  }
}

// 参数设定 (ROS 2 版)
void Hybrid_astar::InitParams(std::shared_ptr<rclcpp::Node> node)
{
  node->declare_parameter<double>("search/max_tau", -1.0);
  node->declare_parameter<double>("search/init_max_tau", -1.0);
  node->declare_parameter<double>("search/max_vel", -1.0);
  node->declare_parameter<double>("search/max_acc", -1.0);
  node->declare_parameter<double>("search/w_time", -1.0);
  node->declare_parameter<double>("search/horizon", 10.0);
  node->declare_parameter<double>("search/resolution_astar", -1.0);
  node->declare_parameter<double>("search/time_resolution", -1.0);
  node->declare_parameter<double>("search/lambda_heu", -1.0);
  node->declare_parameter<int>("search/allocate_num", 100000);
  node->declare_parameter<int>("search/check_num", -1);
  node->declare_parameter<bool>("search/optimistic", true);
  node->declare_parameter<bool>("search/is_use_esdf", true);
  node->declare_parameter<double>("search/vel_margin", 0.0);

  node->get_parameter("search/max_tau", max_tau_);
  node->get_parameter("search/init_max_tau", init_max_tau_);
  node->get_parameter("search/max_vel", max_vel_);
  node->get_parameter("search/max_acc", max_acc_);
  node->get_parameter("search/w_time", w_time_);
  node->get_parameter("search/horizon", horizon_);
  node->get_parameter("search/resolution_astar", resolution_);
  node->get_parameter("search/time_resolution", time_resolution_);
  node->get_parameter("search/lambda_heu", lambda_heu_);
  node->get_parameter("search/allocate_num", allocate_num_);
  node->get_parameter("search/check_num", check_num_);
  node->get_parameter("search/optimistic", optimistic_);
  node->get_parameter("search/is_use_esdf", is_use_esdf);

  tie_breaker_ = 1.0 + 1.0 / 10000;

  double vel_margin;
  node->get_parameter("search/vel_margin", vel_margin);
  max_vel_ += vel_margin;

  /* 对于路径池范围进行初始化，最多路径点数为allocate_num_ */
  path_node_pool_.resize(allocate_num_);
  for (int i = 0; i < allocate_num_; i++)
  {
    path_node_pool_[i] = new HybridGridNode;
  }

  phi_ = Eigen::MatrixXd::Identity(4, 4);
  use_node_num_ = 0;
  iter_num_ = 0;
}

// 判断点是否被占据的具体实现形式
// 输入参数栅栏坐标系
inline bool Hybrid_astar::isOccupied(const int &idx, const int &idy) const
{
  return (idx < X_SIZE && idy < Y_SIZE && (data[idx * Y_SIZE + idy] == OBSTACLE));
}

// 判断点是否被占据的具体实现形式
// 输入参数世界坐标系
inline bool Hybrid_astar::isOccupied(const double &dx, const double &dy) const
{
  int idx, idy;
  idx = worldToMap(Vector2d(dx, dy))[0];
  idy = worldToMap(Vector2d(dx, dy))[1];
  return (idx < X_SIZE && idy < Y_SIZE && (data[idx * Y_SIZE + idy] == OBSTACLE));
}

// 检查路径安全性
bool Hybrid_astar::CheckPathSafe(vector<Eigen::Vector2d> path)
{
  // 检测路径上是否存在障碍物
  for (size_t i = 0; i < path.size(); i++)
  {
    // 判断是否碰撞，以及规划路径最后一个点是否是终点
    if(isOccupied(path[i](0),path[i](1)))
    {
      return true;
    }
  }
  return false;
}

/**
 * @brief 栅格地图坐标系转世界坐标系
 * @param mx   地图坐标x
 * @param my   地图坐标y
 * @param wx   世界坐标x
 * @param wy   世界坐标y
 * @return
 * @attention
 * @todo
 * */
Vector2d Hybrid_astar::mapToWorld(Vector2i mapt) const
{
  double wx, wy;
  wx = origin_x + (mapt[0] + 0.5) * resolution_;
  wy = origin_y + (mapt[1] + 0.5) * resolution_;

  return Vector2d(wx, wy);
}

/**
 * @brief 世界坐标系转栅格地图坐标系
 * @param wx   世界坐标x
 * @param wy   世界坐标y
 * @param mx   地图坐标x
 * @param my   地图坐标y
 * @return
 * @attention
 * @todo
 * */
Vector2i Hybrid_astar::worldToMap(Vector2d worldpt) const
{
  int mx, my;

  mx = (int)(1.0 * (worldpt[0] - origin_x) / resolution_);
  my = (int)(1.0 * (worldpt[1] - origin_y) / resolution_);

  return Vector2i(mx, my);
}

/**
 * @brief Astar初始化(面向用户)
 * @param _resolution 地图分辨率
 * @param _originx   地图实际的起点
 * @param _originy   地图实际的终点
 * @param 地图x方向上的尺寸
 * @param 地图y方向上的尺寸
 * @param 一维的地图数据
 * @return
 * @attention
 * @todo
 * */
void Hybrid_astar::InitMap(double _resolution, double _originx, double _originy,
                           int _x_size, int _y_size, std::vector<int32_t> _mapData)
{
  resolution_ = _resolution;

  Y_SIZE = _y_size;
  X_SIZE = _x_size;

  origin_x = _originx;
  origin_y = _originy;

  // 初始化一个数组,按照XYZ的大小去初始化数组
  data = new int32_t[Y_SIZE * X_SIZE]; // 为将地图转化为8进制栅格地图作准备
  // 内存处理,清空数组
  memset(data, 0, Y_SIZE * X_SIZE * sizeof(int32_t));
  for (int i = 0; i < X_SIZE; i++)
  {
    for (int j = 0; j < Y_SIZE; j++)
    {
      // 设定障碍物
      if (_mapData[i * Y_SIZE + j] == 100)
      {
        data[i * Y_SIZE + j] = OBSTACLE; // data用来储存对应栅格点有没有障碍物
      }
      else{
        data[i * Y_SIZE + j] = _mapData[i * Y_SIZE + j];
      }
    }
  }

  // 对地图信息进行赋值
  origin_ = Vector2d(origin_x, origin_y);
  map_size_2d_ = mapToWorld(Vector2i(X_SIZE, Y_SIZE));

  /* ---------- map params ---------- */
  inv_resolution_ = 1.0 / resolution_;
  inv_time_resolution_ = 1.0 / time_resolution_;
}

// 回溯路径
void Hybrid_astar::retrievePath(HybridGridNodePtr end_node)
{
  HybridGridNodePtr cur_node = end_node; // 定义当前节点为路径节点
  // 将结束点添加进来
  path_nodes_.push_back(cur_node);

  // 当父节点不为空
  while (cur_node->cameFrom != NULL)
  {
    // 当前节点
    cur_node = cur_node->cameFrom;
    // 添加父节点
    path_nodes_.push_back(cur_node);
  }

  // 回溯整条路径
  reverse(path_nodes_.begin(), path_nodes_.end());
}

// 获取运动学轨迹
std::vector<Eigen::Vector2d> Hybrid_astar::getKinoTraj(double delta_t)
{
  vector<Vector2d> state_list; // 状态列表

  // 获取搜索到的路径
  HybridGridNodePtr node = path_nodes_.back();

  Matrix<double, 4, 1> x0, xt;

  // 当节点的父节点不为空
  while (node->cameFrom != NULL)
  {
    Vector2d ut = node->input;
    double duration = node->duration;
    // 状态传递
    x0 = node->cameFrom->state;

    for (double t = duration; t >= -1e-5; t -= delta_t)
    {
      // 状态转移
      stateTransit(x0, xt, ut, t);
      // 加入状态列表
      state_list.push_back(xt.head(2));
    }
    node = node->cameFrom;
  }

  // 回溯路径
  reverse(state_list.begin(), state_list.end());

  // 从射线或者说直线中获取路径
  if (is_shot_succ_)
  {
    Vector2d coord;
    VectorXd poly1d, time(4);

    // 进行转换拟合
    for (double t = delta_t; t <= t_shot_; t += delta_t)
    {
      for (int j = 0; j < 4; j++)
        time(j) = pow(t, j); // 高次多项式t的幂计算

      // 二维
      for (int dim = 0; dim < 2; dim++)
      {
        poly1d = coef_shot_.row(dim);
        coord(dim) = poly1d.dot(time);
      }
      state_list.push_back(coord);
    }
  }

  // 取最后一个搜索点
  searchEndpoint = state_list.back();
  return state_list;
}

// 作用从hybrid a star规划的路径中提取关键点,用来进行优化
Eigen::MatrixXd Hybrid_astar::getSamples(double &ts, int &K)
{
  /* ---------- final trajectory time ---------- */
  double T_sum = 0.0;
  if (is_shot_succ_)
    T_sum += t_shot_;

  HybridGridNodePtr node = path_nodes_.back();
  while (node->cameFrom != NULL)
  {
    T_sum += node->duration; // node->duration记录的是以当前节点为终点的前面一小段轨迹的总时长
    node = node->cameFrom;
  }

  /* ---------- init for sampling ---------- */
  K = floor(T_sum / ts);
  ts = T_sum / (K + 1); // 将T_sum平分K+1段, 每段为ts

  bool sample_shot_traj = is_shot_succ_;

  Eigen::VectorXd sx(K + 2), sy(K + 2); // 用来存储x, y, z轴的采样点
  int sample_num = 0;
  node = path_nodes_.back();

  double t;
  if (sample_shot_traj)
    t = t_shot_;
  else
  {
    t = node->duration;
    end_vel_ = node->state.tail(2);
  }

  for (double ti = T_sum; ti > -1e-5; ti -= ts)
  {
    /* ---------- sample shot traj---------- */
    if (sample_shot_traj)
    {
      Vector2d coord;
      VectorXd poly1d, time(4);
      for (int j = 0; j < 4; j++)
        time(j) = pow(t, j);

      for (int dim = 0; dim < 2; dim++)
      {
        poly1d = coef_shot_.row(dim);
        coord(dim) = poly1d.dot(time); // 计算time处的1d坐标
      }

      sx(sample_num) = coord(0), sy(sample_num) = coord(1);
      ++sample_num;
      t -= ts; // t为ShotTraj的时间

      /* end of segment */
      if (t < -1e-5)
      {
        sample_shot_traj = false;
        if (node->cameFrom != NULL)
          t += node->duration;
      }
    }
    /* ---------- sample search traj ---------- */
    else
    {
      Eigen::Matrix<double, 4, 1> x0 = node->cameFrom->state;
      Eigen::Matrix<double, 4, 1> xt;
      Vector2d ut = node->input;

      stateTransit(x0, xt, ut, t);
      sx(sample_num) = xt(0), sy(sample_num) = xt(1);
      ++sample_num;

      t -= ts;

      if (t < -1e-5 && node->cameFrom->cameFrom != NULL)
      {
        node = node->cameFrom;
        t += node->duration;
      }
    }
  }
  /* ---------- return samples ---------- */
  Eigen::MatrixXd samples(2, K + 5);
  samples.block(0, 0, 1, K + 2) = sx.reverse().transpose();
  samples.block(1, 0, 1, K + 2) = sy.reverse().transpose();
  samples.col(K + 2) = start_vel_;
  samples.col(K + 3) = end_vel_;
  samples.col(K + 4) = node->input;

  return samples;
}

// 启发式函数
double Hybrid_astar::estimateHeuristic(Eigen::VectorXd x1, Eigen::VectorXd x2, double &optimal_time)
{
  const Vector2d dp = x2.head(2) - x1.head(2);
  const Vector2d v0 = x1.segment(2, 2);
  const Vector2d v1 = x2.segment(2, 2);

  Vector2i gridMap = worldToMap(x1.head(2));

  double c1 = -36 * dp.dot(dp);
  double c2 = 24 * (v0 + v1).dot(dp);
  double c3 = -4 * (v0.dot(v0) + v1.dot(v1));
  double c4 = (double)data[gridMap(0)*Y_SIZE + gridMap(1)];
  double c5 = w_time_;

  std::vector<double> ts = quartic(c5, c4, c3, c2, c1);

  double v_max = max_vel_ * 0.5;
  double t_bar = (x1.head(2) - x2.head(2)).lpNorm<Infinity>() / v_max;
  ts.push_back(t_bar);

  double cost = 100000000;
  double t_d = t_bar;

  for (auto t : ts)
  {
    if (t < t_bar)
      continue;
    double c;
    if(is_use_esdf == true)
    {
      c = -c1 / (3 * t * t * t) - c2 / (2 * t * t) - c3 / t + w_time_ * t + c4;
    }
    else
    {
      c = -c1 / (3 * t * t * t) - c2 / (2 * t * t) - c3 / t + w_time_ * t;
    }
    if (c < cost)
    {
      cost = c;
      t_d = t;
    }
  }

  optimal_time = t_d;

  return 1.0 * (1 + tie_breaker_) * cost;
}

// 用于求解四次多项式方程的解
vector<double> Hybrid_astar::quartic(double a, double b, double c, double d, double e)
{
  vector<double> dts;

  double a3 = b / a;
  double a2 = c / a;
  double a1 = d / a;
  double a0 = e / a;

  vector<double> ys = cubic(1, -a2, a1 * a3 - 4 * a0, 4 * a2 * a0 - a1 * a1 - a3 * a3 * a0);
  double y1 = ys.front();
  double r = a3 * a3 / 4 - a2 + y1;
  if (r < 0)
    return dts;

  double R = sqrt(r);
  double D, E;
  if (R != 0)
  {
    D = sqrt(0.75 * a3 * a3 - R * R - 2 * a2 + 0.25 * (4 * a3 * a2 - 8 * a1 - a3 * a3 * a3) / R);
    E = sqrt(0.75 * a3 * a3 - R * R - 2 * a2 - 0.25 * (4 * a3 * a2 - 8 * a1 - a3 * a3 * a3) / R);
  }
  else
  {
    D = sqrt(0.75 * a3 * a3 - 2 * a2 + 2 * sqrt(y1 * y1 - 4 * a0));
    E = sqrt(0.75 * a3 * a3 - 2 * a2 - 2 * sqrt(y1 * y1 - 4 * a0));
  }

  if (!std::isnan(D))
  {
    dts.push_back(-a3 / 4 + R / 2 + D / 2);
    dts.push_back(-a3 / 4 + R / 2 - D / 2);
  }
  if (!std::isnan(E))
  {
    dts.push_back(-a3 / 4 - R / 2 + E / 2);
    dts.push_back(-a3 / 4 - R / 2 - E / 2);
  }

  return dts;
}

// 用于求解三次方程的函数
vector<double> Hybrid_astar::cubic(double a, double b, double c, double d)
{
  vector<double> dts;

  double a2 = b / a;
  double a1 = c / a;
  double a0 = d / a;

  double Q = (3 * a1 - a2 * a2) / 9;
  double R = (9 * a1 * a2 - 27 * a0 - 2 * a2 * a2 * a2) / 54;
  double D = Q * Q * Q + R * R;
  if (D > 0)
  {
    double S = std::cbrt(R + sqrt(D));
    double T = std::cbrt(R - sqrt(D));
    dts.push_back(-a2 / 3 + (S + T));
    return dts;
  }
  else if (D == 0)
  {
    double S = std::cbrt(R);
    dts.push_back(-a2 / 3 + S + S);
    dts.push_back(-a2 / 3 - S);
    return dts;
  }
  else
  {
    double theta = acos(R / sqrt(-Q * Q * Q));
    dts.push_back(2 * sqrt(-Q) * cos(theta / 3) - a2 / 3);
    dts.push_back(2 * sqrt(-Q) * cos((theta + 2 * M_PI) / 3) - a2 / 3);
    dts.push_back(2 * sqrt(-Q) * cos((theta + 4 * M_PI) / 3) - a2 / 3);
    return dts;
  }
}

void Hybrid_astar::reset(void)
{
  expanded_nodes_.clear();
  path_nodes_.clear();

  std::priority_queue<HybridGridNodePtr, std::vector<HybridGridNodePtr>, NodeComparator> empty_queue;
  open_set_.swap(empty_queue);

  for (int i = 0; i < use_node_num_; i++)
  {
    HybridGridNodePtr node = path_node_pool_[i];
    node->cameFrom = NULL;
    node->node_state = NOT_EXPAND;
  }

  use_node_num_ = 0;
  iter_num_ = 0;
  is_shot_succ_ = false;
  has_path_ = false;
}

// 将时间转换为整形
int Hybrid_astar::timeToIndex(double time)
{
  int idx = floor((time - time_origin_) * inv_time_resolution_);
  return idx;
}

// 搜索函数 (ROS 2 版)
int Hybrid_astar::search(Eigen::Vector2d start_pt, Eigen::Vector2d start_v, Eigen::Vector2d start_a,
                         Eigen::Vector2d end_pt, Eigen::Vector2d end_v,
                         bool init, bool dynamic, double time_start)
{
  end_point_ = end_pt;
  start_vel_ = start_v;
  start_acc_ = start_a;

  // 检测起点终点是否在障碍物里面
  if (isOccupied(start_pt(0), start_pt(1)))
  {
    RCLCPP_ERROR(rclcpp::get_logger("hybrid_astar"), "start in the obstacle: %.2f %.2f", start_pt[0], start_pt[1]);
    return IN_OCCUPIED;
  }
  if (isOccupied(end_pt(0), end_pt(1)))
  {
    RCLCPP_ERROR(rclcpp::get_logger("hybrid_astar"), "end in the obstacle: %.2f %.2f", end_pt[0], end_pt[1]);
    return IN_OCCUPIED;
  }

  HybridGridNodePtr cur_node = path_node_pool_[0];

  cur_node->cameFrom = NULL;
  cur_node->state.head(2) = start_pt;
  cur_node->state.tail(2) = start_v;
  cur_node->index = worldToMap(start_pt);
  cur_node->gScore = 0.0;

  VectorXd end_state(4);
  Vector2i end_index;
  double time_to_goal;

  end_state.head(2) = end_pt;
  end_state.tail(2) = end_v;
  end_index = worldToMap(end_pt);
  cur_node->fScore = lambda_heu_ * estimateHeuristic(cur_node->state, end_state, time_to_goal);
  cur_node->node_state = IN_OPEN_SET;
  open_set_.push(cur_node);
  use_node_num_ += 1;

  if (dynamic)
  {
    time_origin_ = time_start;
    cur_node->time = time_start;
    cur_node->time_idx = timeToIndex(time_start);
    expanded_nodes_.insert(cur_node->index, cur_node->time_idx, cur_node);
  }
  else
  {
    expanded_nodes_.insert(cur_node->index, cur_node);
  }

  HybridGridNodePtr terminate_node = NULL;
  bool init_search = init;
  const int tolerance = ceil(1 / resolution_);

  while (!open_set_.empty())
  {
    cur_node = open_set_.top();

    bool reach_horizon = (cur_node->state.head(2) - start_pt).norm() >= horizon_;
    bool near_end = abs(cur_node->index(0) - end_index(0)) <= tolerance &&
                    abs(cur_node->index(1) - end_index(1)) <= tolerance;

    if (reach_horizon || near_end)
    {
      terminate_node = cur_node;
      retrievePath(terminate_node);
      if (near_end)
      {
        estimateHeuristic(cur_node->state, end_state, time_to_goal);
        computeShotTraj(cur_node->state, end_state, time_to_goal);
        if (init_search)
          RCLCPP_ERROR(rclcpp::get_logger("hybrid_astar"), "Shot in first search loop!");
      }
    }

    if (reach_horizon)
    {
      if (is_shot_succ_)
      {
        std::cout << "reach end" << std::endl;
        return REACH_END;
      }
      else
      {
        std::cout << "reach horizon" << std::endl;
        return REACH_HORIZON;
      }
    }

    if (near_end)
    {
      if (is_shot_succ_)
      {
        std::cout << "reach end" << std::endl;
        return REACH_END;
      }
      else if (cur_node->cameFrom != NULL)
      {
        std::cout << "near end" << std::endl;
        return NEAR_END;
      }
      else
      {
        std::cout << "no path" << std::endl;
        return NO_PATH;
      }
    }

    open_set_.pop();
    cur_node->node_state = IN_CLOSE_SET;
    iter_num_ += 1;

    double res = 1 / 2.0, time_res = 1 / 1.0, time_res_init = 1 / 20.0;
    Matrix<double, 4, 1> cur_state = cur_node->state;
    Matrix<double, 4, 1> pro_state;
    vector<HybridGridNodePtr> tmp_expand_nodes;
    Vector2d um;
    double pro_t;
    vector<Vector2d> inputs;
    vector<double> durations;

    if (init_search)
    {
      inputs.push_back(start_acc_);
      for (double tau = time_res_init * init_max_tau_; tau <= init_max_tau_ + 1e-3;
           tau += time_res_init * init_max_tau_)
      {
        durations.push_back(tau);
      }
      init_search = false;
    }
    else
    {
      for (double ax = -max_acc_; ax <= max_acc_ + 1e-3; ax += max_acc_ * res)
      {
        for (double ay = -max_acc_; ay <= max_acc_ + 1e-3; ay += max_acc_ * res)
        {
          um << ax, ay;
          inputs.push_back(um);
        }
      }

      for (double tau = time_res * max_tau_; tau <= max_tau_; tau += time_res * max_tau_)
      {
        durations.push_back(tau);
      }
    }

    for (long unsigned int i = 0; i < inputs.size(); ++i)
    {
      for (long unsigned int j = 0; j < durations.size(); ++j)
      {
        um = inputs[i];
        double tau = durations[j];
        stateTransit(cur_state, pro_state, um, tau);
        pro_t = cur_node->time + tau;

        Vector2d pro_pos = pro_state.head(2);
        Vector2i pro_id = worldToMap(pro_pos);
        int pro_t_id = timeToIndex(pro_t);

        HybridGridNodePtr pro_node = dynamic ? expanded_nodes_.find(pro_id, pro_t_id) : expanded_nodes_.find(pro_id);

        if (pro_node != NULL && pro_node->node_state == IN_CLOSE_SET)
        {
          if (init_search)
            std::cout << "close" << std::endl;
          continue;
        }

        Vector2d pro_v = pro_state.tail(2);
        if (fabs(pro_v(0)) > max_vel_ || fabs(pro_v(1)) > max_vel_)
        {
          if (init_search)
            std::cout << "vel" << std::endl;
          continue;
        }

        Vector2i diff = pro_id - cur_node->index;
        int diff_time = pro_t_id - cur_node->time_idx;
        if (diff.norm() == 0 && ((!dynamic) || diff_time == 0))
        {
          if (init_search)
            std::cout << "same" << std::endl;
          continue;
        }

        Vector2d pos;
        Matrix<double, 4, 1> xt;
        bool is_occ = false;
        for (int k = 1; k <= check_num_; ++k)
        {
          double dt = tau * double(k) / double(check_num_);
          stateTransit(cur_state, xt, um, dt);
          pos = xt.head(2);
          Vector2i posIndex = worldToMap(pos);
          if (isOccupied(posIndex[0], posIndex[1]))
          {
            is_occ = true;
            break;
          }
        }
        if (is_occ)
        {
          if (init_search)
            std::cout << "safe" << std::endl;
          continue;
        }

        double time_to_goal, tmp_g_score, tmp_f_score;
        tmp_g_score = (um.squaredNorm() + w_time_) * tau + cur_node->gScore;
        tmp_f_score = tmp_g_score + lambda_heu_ * estimateHeuristic(pro_state, end_state, time_to_goal);

        bool prune = false;
        for (long unsigned int j = 0; j < tmp_expand_nodes.size(); ++j)
        {
          HybridGridNodePtr expanded_nodes = tmp_expand_nodes[j];
          if ((pro_id - expanded_nodes->index).norm() == 0 &&
              ((!dynamic) || pro_t_id == expanded_nodes->time_idx))
          {
            prune = true;
            if (tmp_f_score < expanded_nodes->fScore)
            {
              expanded_nodes->fScore = tmp_f_score;
              expanded_nodes->gScore = tmp_g_score;
              expanded_nodes->state = pro_state;
              expanded_nodes->input = um;
              expanded_nodes->duration = tau;
              if (dynamic)
                expanded_nodes->time = cur_node->time + tau;
            }
            break;
          }
        }

        if (!prune)
        {
          if (pro_node == NULL)
          {
            pro_node = path_node_pool_[use_node_num_];
            pro_node->index = pro_id;
            pro_node->state = pro_state;
            pro_node->fScore = tmp_f_score;
            pro_node->gScore = tmp_g_score;
            pro_node->input = um;
            pro_node->duration = tau;
            pro_node->cameFrom = cur_node;
            pro_node->node_state = IN_OPEN_SET;
            if (dynamic)
            {
              pro_node->time = cur_node->time + tau;
              pro_node->time_idx = timeToIndex(pro_node->time);
            }
            open_set_.push(pro_node);

            if (dynamic)
            {
              expanded_nodes_.insert(pro_id, pro_node->time, pro_node);
            }
            else
            {
              expanded_nodes_.insert(pro_id, pro_node);
            }

            tmp_expand_nodes.push_back(pro_node);

            use_node_num_ += 1;
            if (use_node_num_ == allocate_num_)
            {
              cout << "run out of memory." << endl;
              return NO_PATH;
            }
          }
          else if (pro_node->node_state == IN_OPEN_SET)
          {
            if (tmp_g_score < pro_node->gScore)
            {
              pro_node->state = pro_state;
              pro_node->fScore = tmp_f_score;
              pro_node->gScore = tmp_g_score;
              pro_node->input = um;
              pro_node->duration = tau;
              pro_node->cameFrom = cur_node;
              if (dynamic)
                pro_node->time = cur_node->time + tau;
            }
          }
          else
          {
            cout << "error type in searching: " << pro_node->node_state << endl;
          }
        }
      }
    }
  }

  cout << "open set empty, no path!" << endl;
  cout << "use node num: " << use_node_num_ << endl;
  cout << "iter num: " << iter_num_ << endl;
  return NO_PATH;
}

std::vector<HybridGridNodePtr> Hybrid_astar::getVisitedNodes(void)
{
  vector<HybridGridNodePtr> visited;
  visited.assign(path_node_pool_.begin(), path_node_pool_.begin() + use_node_num_ - 1);
  return visited;
}

// 计算从状态1到状态2的运动轨迹
bool Hybrid_astar::computeShotTraj(Eigen::VectorXd state1, Eigen::VectorXd state2, double time_to_goal)
{
  const Vector2d p0 = state1.head(2);
  const Vector2d dp = state2.head(2) - p0;
  const Vector2d v0 = state1.segment(2, 2);
  const Vector2d v1 = state2.segment(2, 2);
  const Vector2d dv = v1 - v0;

  double t_d = time_to_goal;

  MatrixXd coef(2, 4);

  end_vel_ = v1;

  Vector2d a = 1.0 / 6.0 * (-12.0 / (t_d * t_d * t_d) * (dp - v0 * t_d) + 6 / (t_d * t_d) * dv);
  Vector2d b = 0.5 * (6.0 / (t_d * t_d) * (dp - v0 * t_d) - 2 / t_d * dv);
  Vector2d c = v0;
  Vector2d d = p0;

  coef.col(3) = a, coef.col(2) = b, coef.col(1) = c, coef.col(0) = d;

  Vector2d coord, vel, acc;
  VectorXd poly1d, t;

  Eigen::MatrixXd Tm(4, 4);
  Tm << 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0;

  double t_delta = t_d / 10;
  for (double time = t_delta; time < t_d; time += t_delta)
  {
    t = VectorXd::Zero(4);
    for (int j = 0; j < 4; j++)
    {
      t(j) = pow(time, j);
    }

    for (int dim = 0; dim < 2; dim++)
    {
      poly1d = coef.row(dim);
      coord(dim) = poly1d.dot(t);
      vel(dim) = (Tm * poly1d).dot(t);
      acc(dim) = (Tm * Tm * poly1d).dot(t);

      if (fabs(vel(dim)) > max_vel_ || fabs(acc(dim)) > max_acc_)
      {
      }
    }

    if (coord(0) < origin_(0) || coord(0) >= map_size_2d_(0) ||
        coord(1) < origin_(1) || coord(1) >= map_size_2d_(1))
    {
      return false;
    }

    Vector2i coordindex = worldToMap(coord);
    if (isOccupied(coordindex(0), coordindex(1)))
    {
      return false;
    }
  }

  coef_shot_ = coef;
  t_shot_ = t_d;
  is_shot_succ_ = true;
  return true;
}

// 状态转移
void Hybrid_astar::stateTransit(Eigen::Matrix<double, 4, 1> &state0,
                                Eigen::Matrix<double, 4, 1> &state1,
                                Eigen::Vector2d um, double tau)
{
  for (int i = 0; i < 2; ++i)
    phi_(i, i + 2) = tau;

  Matrix<double, 4, 1> integral;
  integral.head(2) = 0.5 * pow(tau, 2) * um;
  integral.tail(2) = tau * um;

  state1 = phi_ * state0 + integral;
}