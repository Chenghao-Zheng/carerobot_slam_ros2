#ifndef TRAJECTORY_GENERATOR_TYPE_H_
#define TRAJECTORY_GENERATOR_TYPE_H_

#include <Eigen/Core>
#include <vector>

template<int dim>
using TypeVectorVecd = typename std::vector<Eigen::Matrix<double, dim, 1>,
        Eigen::aligned_allocator<Eigen::Matrix<double, dim, 1>>>;

using MatXd = Eigen::MatrixXd;
using VecXd = Eigen::VectorXd;
using Vec2d = Eigen::Vector2d;

#endif // TRAJECTORY_GENERATOR_TYPE_H_