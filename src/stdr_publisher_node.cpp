#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>

ros::Publisher *p_pub;
float global_min;
geometry_msgs::Twist des_vel;
geometry_msgs::Twist cmd_vel;

void desiredVelCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  des_vel = *msg;  // Read input value from rqt_gui as des_vel
}

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  float min = 4.0;
  float max = 0.0;
  int maxindex;

  for (int i=0; i<20; i++)
  {
    if (min > msg->ranges[125 + i])
    {
      min = msg->ranges[125 + i];
    }
    if (max < msg->ranges[125 + i])
    {
      max = msg->ranges[125 + i];
      maxindex = i;
    }
  }

  global_min = min;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Publisher log_pub = n.advertise<std_msgs::String>("mylog", 1000);
  
  ros::Subscriber sub = n.subscribe("des_vel", 1000, desiredVelCallback);
  ros::Subscriber lasersub = n.subscribe("laser_1", 1000, laserScanCallback);
  
  p_pub = &cmd_vel_pub;

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    std_msgs::String log;
    log.data = std::to_string(global_min);

    if (global_min > 2) {
      cmd_vel.linear.x = des_vel.linear.x;
      cmd_vel.angular.z = des_vel.angular.z;
    }
    else {
      cmd_vel.linear.x = 0;
      cmd_vel.angular.z = 0.5;
    }

    log_pub.publish(log);


    cmd_vel_pub.publish(cmd_vel);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
