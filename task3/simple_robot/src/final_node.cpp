#include <ros/ros.h>
#include <simple_robot_msgs/VictimFound.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <simple_robot_msgs/GetRobotPoseAction.h>

class final_node{
		public:
			ros::NodeHandle n;
			ros::Subscriber final_node_sub;
			simple_robot_msgs::GetRobotPoseGoal goal;
			simple_robot_msgs::GetRobotPoseResultConstPtr result_;
			actionlib::SimpleActionClient<simple_robot_msgs::GetRobotPoseAction> ac;
			
		public:
			final_node() : ac("/slam/get_robot_pose", true)
				{			
					final_node_sub = n.subscribe("/data_fusion/victim_found", 1000, &final_node::final_nodeCallback,this);
						
					ac.waitForServer(); //will wait for infinite time
					ROS_WARN("Server up");
					}
		void final_nodeCallback(const simple_robot_msgs::VictimFoundConstPtr& msg);
};

void final_node::final_nodeCallback(const simple_robot_msgs::VictimFoundConstPtr& msg)
	{
		ac.sendGoal(goal);
		result_ = ac.getResult();
		ac.waitForResult();
		result_ = ac.getResult();
		ROS_ERROR("I receive message about a victim from sensor %s",msg->data.c_str());
		ROS_ERROR("Victim found! Robot pose(<x>,<y>) = (<%d>,<%d>)",result_->x,result_->y);

		}
		
int main (int argc, char **argv)
{
	ros::init(argc, argv, "final_node");
	
	final_node x;
	
	ros::spin();
	return 0;
}

