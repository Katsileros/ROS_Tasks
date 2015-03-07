#include "ros/ros.h"
#include "complex_communication/table.h"
using namespace std;

class server{	    
	 public:
			ros::NodeHandle n;
			ros::Publisher server_pub;
			ros::Subscriber server_sub;
			complex_communication::table tmp;
			int count;
	public:
		server();
		void serverCallback(const complex_communication::table& msg);
		int winner_check();
};

server::server(){
			server_pub = n.advertise<complex_communication::table>("table", 100);
			server_sub = n.subscribe("move",100,&server::serverCallback,this);
			count = 0;
			ros::Rate loop_rate(0.2);
			int i;
			tmp.num = 1;
			for(i=0;i<9;i++)
				{
					tmp.matrix[i] = 0;
					}
		cout << "I'm gonna publish the first (0) board to the player. \n";
			loop_rate.sleep();
			server_pub.publish(tmp);
		}

void server::serverCallback(const complex_communication::table& msg)
{
	int i;
	count++;
	ros::Rate loop_rate(0.2);
	cout << "Server: I took the table from player: " << msg.num << ".\n";
	
	if(msg.num == 1){tmp.num = 2;}
	else if(msg.num == 2){tmp.num = 1;}
	
	for(i=0;i<9;i++)
		{
			tmp.matrix[i] = msg.matrix[i];
			cout << msg.matrix[i] << "\t";
			}
		cout << "\n";
		
	if((winner_check() != 1) && (winner_check() != 2) && (count < 9))
		{
		cout << "I'm gonna publish the new board: \n";
		for(i=0;i<9;i++)
		  {cout << tmp.matrix[i] << "\t";}
		cout << "\n\n";
		server_pub.publish(tmp);
		}
	else if((count == 9) && (winner_check() == 0))
	{
		cout << "There is no winner. \n"; 
		tmp.num = 0;
		server_pub.publish(tmp);
		}
	else
	{
		cout << "The winner is player: " << winner_check() << "\n"; 
		tmp.num = 0;
		server_pub.publish(tmp);
		exit;
		}
		
	loop_rate.sleep();
	ros::spinOnce();
}

int server::winner_check()
{
	int i,flag;
	
	if((tmp.matrix[0] == tmp.matrix[1]) && (tmp.matrix[1] == tmp.matrix[2]) && (tmp.matrix[0] != 0))
		{
			flag = tmp.matrix[0];
		}
	else if((tmp.matrix[3] == tmp.matrix[4]) && (tmp.matrix[4] == tmp.matrix[5]) && (tmp.matrix[3] != 0))
		{
			flag = tmp.matrix[3];
		}
	else if((tmp.matrix[6] == tmp.matrix[7]) && (tmp.matrix[7] == tmp.matrix[8]) && (tmp.matrix[6] != 0))
		{
			flag = tmp.matrix[6];
		}
	else if((tmp.matrix[0] == tmp.matrix[3]) && (tmp.matrix[3] == tmp.matrix[6]) && (tmp.matrix[0] != 0))
		{
			flag = tmp.matrix[0];
		}
	else if((tmp.matrix[1] == tmp.matrix[4]) && (tmp.matrix[4] == tmp.matrix[7]) && (tmp.matrix[1] != 0))
		{
			flag = tmp.matrix[1];
		}
	else if((tmp.matrix[2] == tmp.matrix[5]) && (tmp.matrix[5] == tmp.matrix[8]) && (tmp.matrix[2] != 0))
		{
			flag = tmp.matrix[2];
		}
	else if((tmp.matrix[0] == tmp.matrix[4]) && (tmp.matrix[4] == tmp.matrix[8]) && (tmp.matrix[0] != 0))
		{
			flag = tmp.matrix[0];
		}
	else if((tmp.matrix[2] == tmp.matrix[4]) && (tmp.matrix[4] == tmp.matrix[6]) && (tmp.matrix[2] != 0))
		{
			flag = tmp.matrix[2];
		}
	else
		{
			flag = 0;
		}
	return flag;
}

int main(int argc, char **argv)
{
	int i;
	
	ros::init(argc, argv, "server");
	server y;

	ros::spin();
	
  return 0;
}
