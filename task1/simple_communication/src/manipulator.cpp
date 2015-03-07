#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

void numbersCallback(const std_msgs::Int16::ConstPtr& numb)
{
  ROS_INFO("Squared incoming number: [%d]", ( (numb->data)*(numb->data) ) );
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "manipulator");

  ros::NodeHandle n;

  ros::Subscriber numbers_sub = n.subscribe("/task1/numbers", 1000, numbersCallback);

  ros::spin();

  return 0;
}
