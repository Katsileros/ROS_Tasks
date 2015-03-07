#include <ros/ros.h>
#include <cstdlib>
#include <vector>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <ultra_complex_communication/UltraComplexCommunicationAction.h>

class player{
	public:
		int i,x,count;
		ultra_complex_communication::UltraComplexCommunicationGoal goal;
		ultra_complex_communication::UltraComplexCommunicationResultConstPtr result_;
	public:
		player(){
			actionlib::SimpleActionClient<ultra_complex_communication::UltraComplexCommunicationAction> ac("ucc_server", true);

			ROS_WARN("Waiting for action server to start.\n");
			ROS_WARN("Action server started.\n\n\n");

			ros::spinOnce();
			ac.waitForServer(); //will wait for infinite time
		
			count = 0;

			while(ros::ok() && (count < 9)){
				
				count++;
			 
				ROS_INFO("Player:Sending the table. \n");
			 
				x = play();
				while( (goal.table[x] != 0)  ) { 
					x=play(); 
				}
				
				
				if(goal.n == 0){
					goal.n = ((play() % 2) + 1);
				}
				else if(goal.n == 1){
					goal.n =2;
				}
				else {
					goal.n = 1;
				}
				
				goal.table[x] = goal.n;
				ac.sendGoal(goal);

				bool finished_before_timeout = ac.waitForResult(ros::Duration(3.0));
				result_=ac.getResult();
				if(result_->n==3)
					break;
				ros::spinOnce();
				}
			}
	int play();
};

int player::play()
{
	int x;
	x = rand() % 9;
	return x;
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "ucc_client");
	srand (time(NULL));
	
	player ucc_client;
	
	return 0;
}

