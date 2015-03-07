#include <ros/ros.h>
#include <simple_robot_msgs/TemperatureReading.h>

class thermal_sernsor{
	public:
			ros::NodeHandle n;
			ros::Publisher thermal_pub;
			simple_robot_msgs::TemperatureReading msg;
	public:
		thermal_sernsor(){
					  thermal_pub = n.advertise<simple_robot_msgs::TemperatureReading>("/sensors/temperature", 1000);
					  ros::Rate loop_rate(1);

					  while (ros::ok())
					  {
							msg.temp = (rand()% 20 ) + 20;
							thermal_pub.publish(msg);

							loop_rate.sleep();
							ROS_INFO("Thermal sensor,temperature sent: %d",msg.temp);
							
							ros::spinOnce();
					  }			
				}
	
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "thermal_sensor");
  srand (time(NULL));
  
  thermal_sernsor x;
  
  ros::spin();
  
  return 0;
  
}
