#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <vector>
#include <algorithm>

ros::Publisher *p_pub;
std::vector<float> laser_data;


void laserCallback(const sensor_msgs::LaserScan msg) {
  laser_data = msg.ranges;
}

void commandCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  geometry_msgs::Twist updated_msg;

  if(laser_data.size() == 0) {
    return;
  }

  float min_forward = std::numeric_limits<float>::infinity();
  float min_backward = std::numeric_limits<float>::infinity();
  for(int i = 0; i < laser_data.size(); i++) {
    if(i >= 45 && i < 225) { // The middle 2/3 of the lasers are facing forward
      min_forward = std::min(min_forward, laser_data[i]);
    } else {
      min_backward = std::min(min_backward, laser_data[i]);
    }
  }

  if((min_forward < 0.5 && msg->linear.x > 0) || (min_backward < 0.5 && msg->linear.x < 0)) {
    updated_msg.linear.x = 0;
  } else {
    updated_msg.linear.x = msg->linear.x;
  }
  updated_msg.angular.z = msg->angular.z;

  p_pub->publish(updated_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "collisionAvoidance");

  ros::NodeHandle n;

  ros::Publisher command_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  p_pub = &command_pub;
  ROS_INFO_STREAM("Publishing on topic " << command_pub.getTopic());

  ros::Subscriber command_sub = n.subscribe("des_vel", 1000, commandCallback);
  ROS_INFO_STREAM("Listening on topic " << command_sub.getTopic());

  ros::Subscriber laser_sub = n.subscribe("laser_1", 1000, laserCallback);
  ROS_INFO_STREAM("Listening on topic " << laser_sub.getTopic());

  ros::spin();

  return 0;
}
