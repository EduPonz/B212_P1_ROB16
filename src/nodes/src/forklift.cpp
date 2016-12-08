#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/QuaternionStamped.h"
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/console.h>
#include <iostream>
#include <string.h>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <fstream>  //for opening, reading and writing
#include <math.h>

using namespace std;

class Forklift {
	
	private:
		ros::Publisher fork_status_pub;
	    ros::Subscriber movement_sub;
	    std::string receivedMessage;

		void _succFailFunc(const std_msgs::String::ConstPtr& msg) {

		  receivedMessage = msg->data.c_str();
		  ROS_INFO("The operation has been received!");

		}

		void _publishStatus (string s, ros::Publisher fork_status_pub){

	      string status = s;
	      std_msgs::String fork_status_msg;
	      fork_status_msg.data = status;
	      fork_status_pub.publish(fork_status_msg);
	      
	      ros::spinOnce(); 
	    }

		void _runScript(ros::Publisher fork_status_pub){

			system("forklift.sh");
			cout << "Ive run the script!" << endl;

			ros::Duration ten_seconds(10.0);			
			cout << "Ishould only appear after 5 seconds" << endl;

			string s = "I have finished lifting the pallet!";
			//_publishStatus(s, fork_status_pub);


		}

	public:
		Forklift(ros::NodeHandle n) {
			
			/*do {
				ros::Subscriber movement_sub = n.subscribe("succ_fail", 1000, &Forklift::_succFailFunc, this);
				ros::spinOnce ();
			}while (receivedMessage != "succ");*/

			_runScript(fork_status_pub);
		};
		~Forklift() {};
};

int main(int argc, char **argv) {	
	ros::init(argc, argv, "forklift");

	ros::NodeHandle myNodeHandle;
  	Forklift myForklift  (myNodeHandle);
	
	return 0;
}