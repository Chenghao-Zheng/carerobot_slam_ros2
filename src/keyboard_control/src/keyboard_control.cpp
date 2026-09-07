/*
 * @Author: Keyboard Control for Differential Drive Robot (ROS 2 Version)
 * @Description: 通过键盘控制二轮差速机器人在 Gazebo / ROS 2 仿真中移动
 */

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// 键盘输入配置
struct termios initial_settings, new_settings;
int keyboard_fd;

// 速度参数
double MAX_LINEAR_SPEED = 1.0;      // 最大线速度 (m/s)
double MAX_ANGULAR_SPEED = 2.0;     // 最大角速度 (rad/s)
const double LINEAR_STEP = 0.05;     // 线速度步进
const double ANGULAR_STEP = 0.1;     // 角速度步进

// 当前速度指令
double current_linear = 0.0;
double current_angular = 0.0;

// 显示控制信息
void printHelp()
{
    cout << "\n============================================\n";
    cout << "      二轮差速机器人键盘控制 (ROS 2)\n";
    cout << "============================================\n";
    cout << "  按键               功能\n";
    cout << "  ----------------------------------------\n";
    cout << "    W                前进 (加速)\n";
    cout << "    S                后退 (加速)\n";
    cout << "    A                左转 (加速)\n";
    cout << "    D                右转 (加速)\n";
    cout << "    Q                左转 + 前进 (漂移)\n";
    cout << "    E                右转 + 前进 (漂移)\n";
    cout << "    X                急停 (速度归零)\n";
    cout << "    Space            松手刹车 (惯性减速)\n";
    cout << "    +/-              速度倍率增减\n";
    cout << "    H                显示帮助\n";
    cout << "    Ctrl+C           退出程序\n";
    cout << "============================================\n";
    cout << "  当前速度: 线速度=0.00 m/s  角速度=0.00 rad/s\n";
    cout << "  速度倍率: 1.00x\n";
    cout << "============================================\n";
}

// 显示当前状态
void printStatus()
{
    static int counter = 0;
    counter++;
    if (counter % 10 == 0) {  // 每10次更新一次显示
        cout << "\r当前速度: 线速度=" << fixed << setprecision(2) << current_linear 
             << " m/s  角速度=" << current_angular << " rad/s  ";
        cout.flush();
    }
}

// 初始化键盘输入
int initKeyboard()
{
    keyboard_fd = 0;  // 标准输入
    tcgetattr(keyboard_fd, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;  // 非标准模式
    new_settings.c_lflag &= ~ECHO;    // 不回显
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(keyboard_fd, TCSANOW, &new_settings);
    
    // 设置非阻塞模式
    int flags = fcntl(keyboard_fd, F_GETFL, 0);
    fcntl(keyboard_fd, F_SETFL, flags | O_NONBLOCK);
    
    return keyboard_fd;
}

// 恢复终端设置
void restoreKeyboard()
{
    tcsetattr(keyboard_fd, TCSANOW, &initial_settings);
    fcntl(keyboard_fd, F_SETFL, fcntl(keyboard_fd, F_GETFL, 0) & ~O_NONBLOCK);
}

// 获取键盘输入
char getKey()
{
    char ch;
    int nread = read(keyboard_fd, &ch, 1);
    if (nread == 1) {
        return ch;
    }
    return 0;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("keyboard_control");

    // 创建 ROS 2 发布者
    auto cmd_vel_pub = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    // 声明并获取参数
    node->declare_parameter<double>("max_linear_speed", 1.0);
    node->declare_parameter<double>("max_angular_speed", 2.0);

    node->get_parameter("max_linear_speed", MAX_LINEAR_SPEED);
    node->get_parameter("max_angular_speed", MAX_ANGULAR_SPEED);

    RCLCPP_INFO(node->get_logger(), "Max linear speed: %.2f m/s", MAX_LINEAR_SPEED);
    RCLCPP_INFO(node->get_logger(), "Max angular speed: %.2f rad/s", MAX_ANGULAR_SPEED);

    initKeyboard();
    printHelp();

    rclcpp::WallRate loop_rate(50);  // 50Hz
    bool running = true;
    bool space_pressed = false;
    double speed_scale = 1.0;
    double linear_decay = 0.98;
    double angular_decay = 0.95;

    cout << "按 Ctrl+C 退出程序" << endl;
    cout << "提示: 按 H 显示帮助" << endl;

    while (rclcpp::ok() && running) {
        char key = getKey();

        if (key != 0) {
            switch (key) {
                case 'w':
                case 'W':
                    current_linear += LINEAR_STEP * speed_scale;
                    current_linear = min(current_linear, MAX_LINEAR_SPEED * speed_scale);
                    break;

                case 's':
                case 'S':
                    current_linear -= LINEAR_STEP * speed_scale;
                    current_linear = max(current_linear, -MAX_LINEAR_SPEED * speed_scale);
                    break;

                case 'a':
                case 'A':
                    current_angular += ANGULAR_STEP * speed_scale;
                    current_angular = min(current_angular, MAX_ANGULAR_SPEED * speed_scale);
                    break;

                case 'd':
                case 'D':
                    current_angular -= ANGULAR_STEP * speed_scale;
                    current_angular = max(current_angular, -MAX_ANGULAR_SPEED * speed_scale);
                    break;

                case 'q':
                case 'Q':
                    current_linear = MAX_LINEAR_SPEED * 0.5 * speed_scale;
                    current_angular = MAX_ANGULAR_SPEED * 0.5 * speed_scale;
                    break;

                case 'e':
                case 'E':
                    current_linear = MAX_LINEAR_SPEED * 0.5 * speed_scale;
                    current_angular = -MAX_ANGULAR_SPEED * 0.5 * speed_scale;
                    break;

                case 'x':
                case 'X':
                    current_linear = 0.0;
                    current_angular = 0.0;
                    cout << "\n⚠️ 急停！速度归零" << endl;
                    break;

                case ' ':
                    space_pressed = true;
                    break;

                case '+':
                case '=':
                    speed_scale = min(speed_scale + 0.1, 2.0);
                    cout << "\r速度倍率: " << fixed << setprecision(2) << speed_scale << "x  ";
                    break;

                case '-':
                case '_':
                    speed_scale = max(speed_scale - 0.1, 0.1);
                    cout << "\r速度倍率: " << fixed << setprecision(2) << speed_scale << "x  ";
                    break;

                case 'h':
                case 'H':
                    printHelp();
                    break;

                case 3:  // Ctrl+C
                    running = false;
                    break;

                default:
                    break;
            }
        }

        if (space_pressed) {
            current_linear *= linear_decay;
            current_angular *= angular_decay;

            if (fabs(current_linear) < 0.001) current_linear = 0.0;
            if (fabs(current_angular) < 0.001) current_angular = 0.0;
            space_pressed = false;
        }

        auto cmd = geometry_msgs::msg::Twist();
        cmd.linear.x = current_linear;
        cmd.linear.y = 0.0;
        cmd.linear.z = 0.0;
        cmd.angular.x = 0.0;
        cmd.angular.y = 0.0;
        cmd.angular.z = current_angular;

        cmd_vel_pub->publish(cmd);

        printStatus();

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    // 退出前发送停车指令
    auto stop_cmd = geometry_msgs::msg::Twist();
    cmd_vel_pub->publish(stop_cmd);

    restoreKeyboard();
    cout << "\n\n程序退出\n" << endl;

    rclcpp::shutdown();
    return 0;
}