#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"

double x_actual;

void odometryCallback(const nav_msgs::Odometry::ConstPtr &msg) {
  ROS_INFO("X: [%f]", msg->pose.pose.position.x);
  x_actual = msg->pose.pose.position.x;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "pub_odom");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/odom", 1000, odometryCallback);
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  double dt = 1/10;
  ros::Rate loop_rate(1/dt);

  double x_deseado = 2.0;
  double kp = 0.2;
  double ki = 0;
  double kd = 0.1;
  double integral = 0;
  double derivativa = 0;
  double error_previo = 0;

  while (ros::ok()) {
    geometry_msgs::Twist vel;

    double error = x_deseado - x_actual;
    ROS_INFO("error: [%f]", error);
    integral = integral + error*dt;
    derivativa = (error - error_previo)/dt;
    double u = kp * error + ki*integral + kd*derivativa;

    error_previo = error;

    vel.linear.x = u;
    cmd_vel_pub.publish(vel);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}