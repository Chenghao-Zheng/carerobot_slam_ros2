/*
 * @Author: your name
 * @Date: 2023-08-16 10:37:04
 * @LastEditTime: 2026-08-31
 * @Description: BSpline header (No ROS dependency)
 */
#ifndef __BSPLINE_H
#define __BSPLINE_H
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using namespace Eigen;

class BSpline
{
private:
  /* data */
public:
  double baseFunction(int i, int k, double u, vector<double>node_vector);

  vector<double> u_quasi_uniform(int n,int k);
  vector<double> u_piecewise_B_Spline(int n,int k);

  BSpline(/* args */);
  ~BSpline();
};

#endif //CHHROBOTICS_CPP_BSPLINE_H