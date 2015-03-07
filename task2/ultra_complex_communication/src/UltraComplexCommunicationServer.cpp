#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ultra_complex_communication/UltraComplexCommunicationAction.h>

class server
{
protected:
	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<ultra_complex_communication::UltraComplexCommunicationAction> as_; 

	ultra_complex_communication::UltraComplexCommunicationResult result_;
	ultra_complex_communication::UltraComplexCommunicationResult goal;
public:
	std::vector<int> table;
	int n,count;

	server(std::string name) : as_(nh_, name, boost::bind(&server::executeCB, this, _1), false)
	{
		int i;
		
		for(i=0;i<9;i++){
			table.push_back(0);
		}
		
		as_.start();
		ROS_WARN("Server started");
	}
	void executeCB(const ultra_complex_communication::UltraComplexCommunicationGoalConstPtr &goal);
	bool check_table();
	int winner_check();
 };

 
void server::executeCB(const ultra_complex_communication::UltraComplexCommunicationGoalConstPtr &goal)
  {
	int winner,i,n;
	count++;

	if( (winner_check() != 1) && (winner_check() != 2) && (count < 9) ){
		if(check_table()){
			ros::Rate r(10.0);
			ROS_INFO("Server:sending the table.");
			for(i=0;i<9;i++)
			{
				table[i]=goal->table[i];
				result_.table[i] = table[i];
				ROS_INFO("%d",result_.table[i]);
			}
			n = goal->n;
			ROS_INFO("Previous player: %d .",n);
			if(n == 1){
				n = 2;
				result_.n = n;
			}
			else{
				n = 1;
				result_.n = n;
			}
			ROS_INFO("Next player: %d .",result_.n);

			as_.setSucceeded(result_);
			ROS_INFO("Result sent.\n");
			r.sleep();
		}
	}
	else{
		winner = winner_check();
		
		if( winner == 0 ){
			ROS_WARN("There was no winner.\n");
		}
		else{
			ROS_WARN("The winner is player:%d .\n",winner);
		}	 
		result_.n=3;
		as_.setSucceeded(result_);
		exit(0);
	}
	ros::spinOnce();
}		

	
bool server::check_table()
{
	int i;
	bool flag;
	
	flag = false;
	for(i=0;i<9;i++)
		{
			if(table[i] == 0){flag = true;}
			}
	return flag;
	}	

int server::winner_check()
{
	int i,winner;
	
	if((table[0] == table[1]) && (table[1] == table[2]) && (table[0] != 0))
		{
			winner = table[0];
		}
	else if((table[3] == table[4]) && (table[4] == table[5]) && (table[3] != 0))
		{
			winner = table[3];
		}
	else if((table[6] == table[7]) && (table[7] == table[8]) && (table[6] != 0))
		{
			winner = table[6];
		}
	else if((table[0] == table[3]) && (table[3] == table[6]) && (table[0] != 0))
		{
			winner = table[0];
		}
	else if((table[1] == table[4]) && (table[4] == table[7]) && (table[1] != 0))
		{
			winner = table[1];
		}
	else if((table[2] == table[5]) && (table[5] == table[8]) && (table[2] != 0))
		{
			winner = table[2];
		}
	else if((table[0] == table[4]) && (table[4] == table[8]) && (table[0] != 0))
		{
			winner = table[0];
		}
	else if((table[2] == table[4]) && (table[4] == table[6]) && (table[2] != 0))
		{
			winner = table[2];
		}
	else
		{
			winner = 0;
		}
	return winner;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "ucc_server");
	int i,winner;

	server ucc_server(ros::this_node::getName()); 
	
	ros::spin();

  return 0;
}
