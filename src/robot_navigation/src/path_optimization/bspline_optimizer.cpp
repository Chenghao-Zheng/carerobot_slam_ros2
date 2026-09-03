#include "path_optimization/bspline_optimizer.h"
#include <nlopt.hpp>
#include <iomanip>

using namespace std;

namespace dyn_planner
{
  void BsplineOptimizer::setControlPoints(Eigen::MatrixXd points)
  {
    this->control_points_ = points;
    // start_id 和 end_id_相当于不对最开始order和最后order点进行优化
    // 起点按照B样条优化阶数选取
    this->start_id_ = order_; // 为了保证收尾的边界条件, 不对前后各p个控制点进行优化
    // 因为控制点最后三个是起点的速度 终点的速度 和起点的加速度，所以需要-阶数
    this->end_id_ = this->control_points_.rows() - order_;
    use_guide_ = false;
  }

  void BsplineOptimizer::setOptimizationRange(int start, int end)
  {
    this->start_id_ = min(max(start, order_), int(control_points_.rows() - order_));
    this->end_id_ = min(max(end, order_), int(control_points_.rows() - order_));
    cout << "opt range:" << this->start_id_ << ", " << this->end_id_ << endl;
  }

  void BsplineOptimizer::setParam(rclcpp::Node::SharedPtr node)
  {
    node_ = node;

    lamda1_ = node_->declare_parameter<double>("optimization/lamda1", -1.0);
    lamda2_ = node_->declare_parameter<double>("optimization/lamda2", -1.0);
    lamda3_ = node_->declare_parameter<double>("optimization/lamda3", -1.0);
    lamda4_ = node_->declare_parameter<double>("optimization/lamda4", -1.0);
    lamda5_ = node_->declare_parameter<double>("optimization/lamda5", -1.0);
    dist0_ = node_->declare_parameter<double>("optimization/dist0", -1.0);
    dist1_ = node_->declare_parameter<double>("optimization/dist1", -1.0);
    max_vel_ = node_->declare_parameter<double>("optimization/max_vel", -1.0);
    max_acc_ = node_->declare_parameter<double>("optimization/max_acc", -1.0);
    max_iteration_num_ = node_->declare_parameter<int>("optimization/max_iteration_num", -1);
    algorithm_ = node_->declare_parameter<int>("optimization/algorithm", -1);
    order_ = node_->declare_parameter<int>("optimization/order", -1);

    std::cout << "lamda1: " << lamda1_ << std::endl;
    std::cout << "lamda2: " << lamda2_ << std::endl;
    std::cout << "lamda3: " << lamda3_ << std::endl;
    std::cout << "lamda4: " << lamda4_ << std::endl;

    // 控制点发布
    smoothPathpub = node_->create_publisher<nav_msgs::msg::Path>("/smooth", 10);
    obstaclePathpub = node_->create_publisher<nav_msgs::msg::Path>("/obstacle", 10);
  }

  void BsplineOptimizer::setBSplineInterval(double ts)
  {
    this->bspline_interval_ = ts;
  }

  void BsplineOptimizer::setEnvironment(const EDTEnvironment::Ptr &env)
  {
    this->edt_env_ = env;
  }

  Eigen::MatrixXd BsplineOptimizer::getControlPoints()
  {
    return this->control_points_;
  }

  /* best algorithm_ is 40: SLSQP(constrained), 11 LBFGS(unconstrained) */
  void BsplineOptimizer::optimize(int end_cons, bool dynamic, double time_start)
  {
    /* ---------- initialize solver ---------- */
    end_constrain_ = end_cons;
    dynamic_ = dynamic;
    time_traj_start_ = time_start;
    iter_num_ = 0;

    if (end_constrain_ == HARD_CONSTRAINT)
    {
      // variable_num_ 是变量数目,因为是二维的,所以用(终点-起点)*2
      variable_num_ = 2 * (end_id_ - start_id_); // 需优化的控制点数量, 约束首尾边界条件
    }
    else if (end_constrain_ == SOFT_CONSTRAINT)
    {
      // 使用方法同上
      variable_num_ = 2 * (control_points_.rows() - start_id_); // 需优化的控制点数量, 只约束起始边界条件
    }

    min_cost_ = std::numeric_limits<double>::max();

    nlopt::opt opt(nlopt::algorithm(algorithm_), variable_num_); // algorithm_ = 11 -> LBFGS

    opt.set_min_objective(BsplineOptimizer::costFunction, this); // this指针为BsplineOptimizer::costFunction提供额外数据
    opt.set_maxeval(max_iteration_num_);                         // 100

    /* ---------- init variables ---------- */
    vector<double> q(variable_num_); // 待优化变量x
    double final_cost;
    for (int i = 0; i < int(control_points_.rows()); ++i)
    {
      if (i < start_id_)
        continue;

      if (end_constrain_ == HARD_CONSTRAINT && i >= end_id_)
      {
        continue;
      }

      for (int j = 0; j < 2; j++)                           // x, y轴
        q[2 * (i - start_id_) + j] = control_points_(i, j); // 将优化变量转换为Nlopt要求的格式
    }

    // 默认给 best_variable_ 赋值，防止求解抛出异常时回写数组时内存越界崩溃
    best_variable_ = q;

    if (end_constrain_ == SOFT_CONSTRAINT) // end_pt_为最后一段B-spline的起点(t = 0), 用于惩罚软约束下轨迹末端的位置
    {
      end_pt_ = (1 / 6.0) *
                (control_points_.row(control_points_.rows() - 2) +
                 4*control_points_.row(control_points_.rows() - 1));
    }

    try
    {
      /* ---------- optimization ---------- */
      cout << "[Optimization]: begin-------------" << endl;
      cout << fixed << setprecision(7); // 设置精度
      vec_time_.clear();
      vec_cost_.clear();
      if (node_) {
        time_start_ = node_->now();
      }

      nlopt::result result = opt.optimize(q, final_cost);

      /* ---------- get results ---------- */
      std::cout << "[Optimization]: iter num: " << iter_num_ << std::endl;

      // 将Nlopt计算的最优值转换为Eigen::MatrixXd格式
      for (int i = 0; i < control_points_.rows(); ++i)
      {
        if (i < start_id_)
          continue;

        if (end_constrain_ == HARD_CONSTRAINT && i >= end_id_)
          continue;

        for (int j = 0; j < 2; j++)
          control_points_(i, j) = best_variable_[2 * (i - start_id_) + j];
      }

      cout << "[Optimization]: end-------------" << endl;
    }
    catch (std::exception &e)
    {
      cout << "[Optimization]: nlopt exception: " << e.what() << endl;
    }
  }

  // 计算是否平滑的代价
  void BsplineOptimizer::calcSmoothnessCost(const vector<Eigen::Vector2d> &q, double &cost,
                                            vector<Eigen::Vector2d> &gradient)
  {
    cost = 0.0;
    std::fill(gradient.begin(), gradient.end(), Eigen::Vector2d(0, 0));

    Eigen::Vector2d jerk;

    for (size_t i = 0; i < q.size() - order_; i++)
    {
      jerk = q[i + 3] - 3 * q[i + 2] + 3 * q[i + 1] - q[i];
      cost += jerk.squaredNorm();

      gradient[i + 0] += 2.0 * jerk * (-1.0);
      gradient[i + 1] += 2.0 * jerk * (3.0);
      gradient[i + 2] += 2.0 * jerk * (-3.0);
      gradient[i + 3] += 2.0 * jerk * (1.0);
    }
  }

  // 计算距离代价
  void BsplineOptimizer::calcDistanceCost(const vector<Eigen::Vector2d> &q, double &cost,
                                          vector<Eigen::Vector2d> &gradient)
  {
    cost = 0.0;
    std::fill(gradient.begin(), gradient.end(), Eigen::Vector2d(0, 0));

    double dist;
    Eigen::Vector2d dist_grad, g_zero(0, 0);

    int end_idx = end_constrain_ == SOFT_CONSTRAINT ? q.size() : q.size() - order_;

    for (int i = order_; i < end_idx; i++)
    {
      if (!dynamic_)
      {
        edt_env_->evaluateEDTWithGrad(q[i], -1.0, dist, dist_grad);
      }
      else
      {
        double time = double(i + 2 - order_) * bspline_interval_ + time_traj_start_;
        edt_env_->evaluateEDTWithGrad(q[i], time, dist, dist_grad);
      }

      cost += dist < dist0_ ? pow(dist - dist0_, 2) : 0.0;
      gradient[i] += dist < dist0_ ? 2.0 * (dist - dist0_) * dist_grad : g_zero;
    }
  }

  // 计算可行性代价
  void BsplineOptimizer::calcFeasibilityCost(const vector<Eigen::Vector2d> &q, double &cost,
                                             vector<Eigen::Vector2d> &gradient)
  {
    cost = 0.0;
    std::fill(gradient.begin(), gradient.end(), Eigen::Vector2d(0, 0));

    double ts, vm2, am2, ts_inv2, ts_inv4;
    vm2 = max_vel_ * max_vel_;
    am2 = max_acc_ * max_acc_;

    ts = bspline_interval_;
    ts_inv2 = 1 / ts / ts;
    ts_inv4 = ts_inv2 * ts_inv2;

    /* ---------- velocity feasibility ---------- */
    for (size_t i = 0; i < q.size() - 1; i++)
    {
      Eigen::Vector2d vi = q[i + 1] - q[i];
      for (int j = 0; j < 2; j++)
      {
        double vd = vi(j) * vi(j) * ts_inv2 - vm2;
        cost += vd > 0.0 ? pow(vd, 2) : 0.0;

        gradient[i + 0](j) += vd > 0.0 ? 2.0 * vd * ts_inv2 * (-2.0) * vi(j) : 0.0;
        gradient[i + 1](j) += vd > 0.0 ? 2.0 * vd * ts_inv2 * (2.0) * vi(j) : 0.0;
      }
    }

    /* ---------- acceleration feasibility ---------- */
    for (size_t i = 0; i < q.size() - 2; i++)
    {
      Eigen::Vector2d ai = q[i + 2] - 2 * q[i + 1] + q[i];
      for (int j = 0; j < 2; j++)
      {
        double ad = ai(j) * ai(j) * ts_inv4 - am2;
        cost += ad > 0.0 ? pow(ad, 2) : 0.0;

        gradient[i + 0](j) += ad > 0.0 ? 2.0 * ad * ts_inv4 * (2.0) * ai(j) : 0.0;
        gradient[i + 1](j) += ad > 0.0 ? 2.0 * ad * ts_inv4 * (-4.0) * ai(j) : 0.0;
        gradient[i + 2](j) += ad > 0.0 ? 2.0 * ad * ts_inv4 * (2.0) * ai(j) : 0.0;
      }
    }
  }

  // 计算到终点的代价
  void BsplineOptimizer::calcEndpointCost(const vector<Eigen::Vector2d> &q, double &cost,
                                          vector<Eigen::Vector2d> &gradient)
  {
    cost = 0.0;
    std::fill(gradient.begin(), gradient.end(), Eigen::Vector2d(0, 0));

    if (end_constrain_ == SOFT_CONSTRAINT)
    {
      Eigen::Vector2d q_3, q_2, q_1, qd;
      q_3 = q[q.size() - 3];
      q_2 = q[q.size() - 2];
      q_1 = q[q.size() - 1];

      qd = 1 / 6.0 * (q_3 + 4 * q_2 + q_1) - end_pt_;
      cost += qd.squaredNorm();

      gradient[q.size() - 3] += 2 * qd * (1 / 6.0);
      gradient[q.size() - 2] += 2 * qd * (4 / 6.0);
      gradient[q.size() - 1] += 2 * qd * (1 / 6.0);
    }
  }

  void BsplineOptimizer::combineCost(const std::vector<double> &x, std::vector<double> &grad, double &f_combine)
  {
    vector<Eigen::Vector2d> q;
    q.reserve(control_points_.rows());

    /* first p points */
    for (int i = 0; i < order_; i++)
      q.push_back(control_points_.row(i));

    /* optimized control points */
    for (int i = 0; i < variable_num_ / 2; i++)
    {
      Eigen::Vector2d qi(x[2 * i], x[2 * i + 1]);
      q.push_back(qi);
    }

    /* last p points */
    if (end_constrain_ == END_CONSTRAINT::HARD_CONSTRAINT)
    {
      for (int i = 0; i < order_; i++)
        q.push_back(control_points_.row(control_points_.rows() - order_ + i));
    }

    double f_smoothness, f_distance, f_feasibility, f_endpoint;

    vector<Eigen::Vector2d> g_smoothness, g_distance, g_feasibility, g_endpoint;
    g_smoothness.resize(control_points_.rows());
    g_distance.resize(control_points_.rows());
    g_feasibility.resize(control_points_.rows());
    g_endpoint.resize(control_points_.rows());

    calcSmoothnessCost(q, f_smoothness, g_smoothness);
    calcDistanceCost(q, f_distance, g_distance);
    calcFeasibilityCost(q, f_feasibility, g_feasibility);
    calcEndpointCost(q, f_endpoint, g_endpoint);

    grad.resize(variable_num_);

    f_combine = lamda1_ * f_smoothness + lamda2_ * f_distance + lamda3_ * f_feasibility + lamda4_ * f_endpoint;

    for (int i = 0; i < variable_num_ / 2; i++)
      for (int j = 0; j < 2; j++)
      {
        grad[2 * i + j] = lamda1_ * g_smoothness[i + order_](j) + lamda2_ * g_distance[i + order_](j) +
                          lamda3_ * g_feasibility[i + order_](j) + lamda4_ * g_endpoint[i + order_](j);
      }

    iter_num_ += 1;
  }

  double BsplineOptimizer::costFunction(const std::vector<double> &x, std::vector<double> &grad, void *func_data)
  {
    BsplineOptimizer *opt = reinterpret_cast<BsplineOptimizer *>(func_data);

    double cost;
    opt->combineCost(x, grad, cost);

    if (cost < opt->min_cost_)
    {
      opt->min_cost_ = cost;
      opt->best_variable_ = x;
    }

    return cost;
  }

  void BsplineOptimizer::PublishPath(rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr pathPublish, std::vector<Eigen::Vector2d> path)
  {
    nav_msgs::msg::Path pathTopic;
    pathTopic.header.frame_id = "map";
    for (unsigned int i = 0; i < path.size(); i++)
    {
      geometry_msgs::msg::PoseStamped pathPose;
      pathPose.pose.position.x = path[i][0];
      pathPose.pose.position.y = path[i][1];
      pathPose.pose.position.z = 0;

      if (node_) {
        pathTopic.header.stamp = node_->now();
      }
      pathTopic.poses.push_back(pathPose);
    }
    pathPublish->publish(pathTopic);
  }

} // namespace dyn_planner