"""
Self Balancing Robot
PID Controller (parameterized)
"""
import math
import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist
from tf_transformations import euler_from_quaternion


class SelfBalancingBot(Node):
    def __init__(self):
        super().__init__('self_balancer')

        self.declare_parameter('Kp', 3.0)
        self.declare_parameter('Ki', 0.0)
        self.declare_parameter('Kd', 25.0)
        self.declare_parameter('output_scale', 1.0)
        self.declare_parameter('deadband', 0.03)
        self.declare_parameter('tilt_axis', 'pitch')
        self.declare_parameter('invert', True)
        self.declare_parameter('max_speed', 1.5)

        self.Kp = self.get_parameter('Kp').value
        self.Ki = self.get_parameter('Ki').value
        self.Kd = self.get_parameter('Kd').value
        self.scale = self.get_parameter('output_scale').value
        self.deadband = self.get_parameter('deadband').value
        self.tilt_axis = self.get_parameter('tilt_axis').value
        self.invert = self.get_parameter('invert').value
        self.max_speed = self.get_parameter('max_speed').value

        self.get_logger().info(
            f'PID: Kp={self.Kp}, Kd={self.Kd}, scale={self.scale}, '
            f'axis={self.tilt_axis}, invert={self.invert}, max_speed={self.max_speed}')

        self.set_pos = 0.0
        self.prev_error = 0.0
        self.error_sum = 0.0

        self.publisher = self.create_publisher(Twist, '/cmd_vel', 1)
        self.create_subscription(Odometry, '/odom', self.pos_callback, 1)

        self.velocity = Twist()
        self.velocity.linear.x = 0.0
        self.velocity.linear.y = 0.0
        self.velocity.linear.z = 0.0
        self.velocity.angular.x = 0.0
        self.velocity.angular.y = 0.0
        self.velocity.angular.z = 0.0

    def pos_callback(self, msg):
        orientation_list = [
            msg.pose.pose.orientation.x,
            msg.pose.pose.orientation.y,
            msg.pose.pose.orientation.z,
            msg.pose.pose.orientation.w,
        ]

        r, p, _y = euler_from_quaternion(orientation_list)
        tilt = r if self.tilt_axis == 'roll' else p
        self.curr_pos = -tilt if self.invert else tilt

        self.error = self.curr_pos - self.set_pos
        self.change_in_error = self.error - self.prev_error
        self.error_sum += self.error

        if abs(self.error) > self.deadband:
            p_term = self.Kp * self.error
            i_term = self.Ki * self.error_sum
            d_term = self.Kd * self.change_in_error
            pid = p_term + i_term + d_term
            raw = pid * self.scale
            self.velocity.linear.x = max(-self.max_speed,
                                         min(self.max_speed, raw))
        else:
            self.error_sum = 0.0
            self.change_in_error = 0.0
            self.prev_error = 0.0
            self.error = 0.0
            self.velocity.linear.x = 0.0

        self.velocity.angular.z = 0.0
        self.publisher.publish(self.velocity)

        self.get_logger().info(
            f'r={math.degrees(r):7.2f}  p={math.degrees(p):7.2f}  '
            f'tilt={math.degrees(self.curr_pos):7.2f}deg  '
            f'out={self.velocity.linear.x:+.3f}',
            throttle_duration_sec=0.5,
        )

        self.prev_error = self.error


def main(args=None):
    rclpy.init(args=args)
    try:
        node = SelfBalancingBot()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass


if __name__ == '__main__':
    main()