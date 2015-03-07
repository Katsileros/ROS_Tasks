#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "streamer");
  ros::NodeHandle n;
  ros::Publisher numbers_pub = n.advertise<std_msgs::Int16>("/task1/numbers", 1000);

  ros::Rate loop_rate(1);

  while (ros::ok())
  {
	std_msgs::Int16 numb;

   	numb.data = rand() % 10;

    	ROS_INFO("Random number: [%d]", numb.data);

    	numbers_pub.publish(numb);

    	ros::spinOnce();

    	loop_rate.sleep();
  }
  return 0;
}
