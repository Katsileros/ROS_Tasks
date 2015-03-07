#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <simple_robot_msgs/GetRobotPoseAction.h>

class robot_pos
{
	public:
		ros::NodeHandle nh_;
		actionlib::SimpleActionServer<simple_robot_msgs::GetRobotPoseAction> as_; 
		simple_robot_msgs::GetRobotPoseResult result_;
	public:
		robot_pos();
		simple_robot_msgs::GetRobotPoseResult getResult();

		robot_pos(std::string name) : as_(nh_,"/slam/get_robot_pose", boost::bind(&robot_pos::executeCB, this, _1), false)
		{
			as_.start();
			ROS_WARN("Server started");
			}
		void executeCB(const simple_robot_msgs::GetRobotPoseGoalConstPtr &goal);
};

void robot_pos::executeCB(const simple_robot_msgs::GetRobotPoseGoalConstPtr &goal)
{
	
	result_.x = (rand() % 9);
	result_.y = (rand() % 9);
	
	ROS_WARN("The robot position is: POS.x = %d , POS.y = %d .",result_.x,result_.y);
	as_.setSucceeded(result_);
	}
	
	
int main(int argc, char** argv)
{
	ros::init(argc, argv, "robot_position");

	robot_pos robot_position(ros::this_node::getName()); 
	
	ros::spin();

  return 0;
}
