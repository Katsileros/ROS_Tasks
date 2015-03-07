#include "ros/ros.h"
#include "complex_communication/table.h"
#include <cstdlib>
using namespace std;

class player_1{
	 public:
		ros::NodeHandle n;
		ros::Subscriber sub;
		ros::Publisher pub;
		complex_communication::table tmp;
	public:
		player_1();
		int play();
		void player_1Callback(const complex_communication::table& msg);
};

player_1::player_1(){
		sub = n.subscribe("table", 100,&player_1::player_1Callback,this);
		pub = n.advertise<complex_communication::table>("move",100);
	}

int player_1::play()
{
	int x;
	srand (time(NULL));
	x = rand() % 9;
	return x;
	}

void player_1::player_1Callback(const complex_communication::table& msg)
{
  int i,x;
  
  if(msg.num == 1){
  tmp.num = msg.num;
  
   for(i=0;i<9;i++)
    {tmp.matrix[i] = msg.matrix[i];}
   
	x = play();
	while((tmp.matrix[x] != 0)){x = play();}
	tmp.matrix[x] = 1;
  
     pub.publish(tmp);}
     
	else if (msg.num == 0)  {	
	  cout << "GAME IS OVER.\n";  
	  exit;
     }
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "player_1");
	int i,k;
	player_1 x;

	ros::spin();
	return 0;
}
