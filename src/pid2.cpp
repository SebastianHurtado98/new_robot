#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok()) {
    geometry_msgs::Twist vel;
    vel.linear.x = 0.2;
    cmd_vel_pub.publish(vel);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}