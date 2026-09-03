#ifndef TRAJECTORY_GENERATOR_MATH_FUNCTION_H_
#define TRAJECTORY_GENERATOR_MATH_FUNCTION_H_

/**
 * @brief 计算非负整数的阶乘
 */
inline double Factorial(unsigned int x) {
    unsigned int fac = 1;

    for (unsigned int i = x; i > 0; --i) {
        fac = fac * i;
    }

    return static_cast<double>(fac);
}

#endif // TRAJECTORY_GENERATOR_MATH_FUNCTION_H_