#include <ros/ros.h>
#include <simple_robot_msgs/VictimFound.h>
#include <simple_robot_msgs/TemperatureReading.h>

class data_fusion{
	public:
			ros::NodeHandle n;
			ros::Publisher data_fusion_pub;
			ros::Subscriber data_fusion_sub;
			simple_robot_msgs::VictimFound victim;
	public:
		data_fusion();
		void data_fusionCallback(const simple_robot_msgs::TemperatureReadingConstPtr& numb);
};

data_fusion::data_fusion(){
					data_fusion_sub = n.subscribe("/sensors/temperature", 1000, &data_fusion::data_fusionCallback,this);
					data_fusion_pub = n.advertise<simple_robot_msgs::VictimFound>("/data_fusion/victim_found", 1000);
			}
			
void data_fusion::data_fusionCallback(const simple_robot_msgs::TemperatureReadingConstPtr& numb){
				if((numb->temp) >= 36){
				ROS_WARN("Data_fusion,i receive temperature = %d",numb->temp);
				victim.data = "thermal";
				ROS_WARN("I'm gonna sent,a victim message: %s",victim.data.c_str());
				data_fusion_pub.publish(victim);
			}
		}
		
		
int main(int argc, char **argv)
{
	ros::init(argc, argv, "data_fusion");

	data_fusion x;
	
	ros::spin();

  return 0;
}
