#include "ros/ros.h"
#include "complex_communication/table.h"
#include <cstdlib>
using namespace std;

class player_2{
	 public:
		ros::NodeHandle n;
		ros::Subscriber sub;
		ros::Publisher pub;
		complex_communication::table tmp;
	public:
		player_2();
		int play();
		void player_2Callback(const complex_communication::table& msg);
};

player_2::player_2(){
		sub = n.subscribe("table", 100,&player_2::player_2Callback,this);
		pub = n.advertise<complex_communication::table>("move",100);
	}

int player_2::play()
{
	int x,i;

	srand (time(NULL));
	x = rand() % 9;
	return x;
	}

void player_2::player_2Callback(const complex_communication::table& msg)
{
  int i,x;
  
  if(msg.num == 2){
  tmp.num = msg.num;
  
   for(i=0;i<9;i++)
    {tmp.matrix[i] = msg.matrix[i];}
   
	x = play();
	while((tmp.matrix[x] != 0)){x = play();}
	tmp.matrix[x] = 2;
	  
    pub.publish(tmp);
	}
	
	else if (msg.num == 0)  {	
	  cout << "GAME IS OVER.\n";  
	  exit;
     }
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "player_2");
	int i,k;
	player_2 x;

	ros::spin();
	return 0;
}
