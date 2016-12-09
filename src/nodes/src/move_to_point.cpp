#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "std_msgs/String.h"
#include <actionlib/client/simple_action_client.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/QuaternionStamped.h"
#include <iostream>
#include <string.h>
#include <string>

class MoveToPoint {
	private:
		float xcoord = 0;
		float ycoord = 0;
		float zcoord = 0;
		float wcoord = 0;

		void _moveToGoal(float xGoal, float yGoal, float zGoal, float wGoal, ros::Publisher status_pub) { 
			// Define a client to send goal requests to the move_base server through a SimpleActionClient
			actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
			std_msgs::String msg;
	    	std::stringstream action_ss;
    		std::stringstream status_ss;

			// Wait for the action server to come up
			while(!ac.waitForServer(ros::Duration(5.0))){
				action_ss << "Waiting for the move_base action server to come up";
				msg.data = action_ss.str();
				status_pub.publish(msg);
				ros::spinOnce();
			}

			// Declaring varible 'goal' as type move_bas_msgs::MoveBaseGoal
			move_base_msgs::MoveBaseGoal goal;

			// Set up the frame parameters
			goal.target_pose.header.frame_id = "map";
			goal.target_pose.header.stamp = ros::Time::now();

			// Moving towards the goal
			goal.target_pose.pose.position.x =  xGoal;
			goal.target_pose.pose.position.y =  yGoal;
			goal.target_pose.pose.position.z =  0.0;
			goal.target_pose.pose.orientation.x = 0.0;
			goal.target_pose.pose.orientation.y = 0.0;
			goal.target_pose.pose.orientation.z = zGoal;
			goal.target_pose.pose.orientation.w = wGoal;

			ac.sendGoal(goal);
			ac.waitForResult();

			// If else statement for whether or not the robot succeeded in motion operation.
			if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      			status_ss << "The robot reached the destination";
      			msg.data = status_ss.str(); 
			}else {
		  		status_ss << "The robot failed to reach the destination";
 			    msg.data = status_ss.str();
			}
			status_pub.publish(msg);
			ros::spinOnce();
		}

		void _coordFunc(const geometry_msgs::Point::ConstPtr& msg) {
			// Assigning the values pointed to to the global variables so they can be used in the main function.
			xcoord = msg->x;
			ycoord = msg->y;
		}

		void _quatFunc(const geometry_msgs::Quaternion::ConstPtr& quaternion_msg) {
			// Assigning the values pointed to to the global variables so they can be used in the main function.
			xcoord = quaternion_msg->x;
			ycoord = quaternion_msg->y;
			zcoord = quaternion_msg->z;
			wcoord = quaternion_msg->w;
		}
	public:
		MoveToPoint(ros::NodeHandle n) {
			ros::Publisher status_pub = n.advertise<std_msgs::String>("success_fail", 1000);
			ros::Subscriber quat_sub = n.subscribe("quat_coordinates", 100, &MoveToPoint::_quatFunc, this);
			ros::Subscriber click_sub = n.subscribe("point_coordinates", 100, &MoveToPoint::_coordFunc, this);
			while((xcoord == 0) && (ycoord == 0) && (zcoord == 0) && (wcoord == 0)) {
    	    	ros::spinOnce(); 
    		}
			// Call to function moveToGoal (see below)
			_moveToGoal(xcoord, ycoord, zcoord, wcoord, status_pub);
		};
		~MoveToPoint() {};
};

int main(int argc, char** argv) {

	ros::init(argc, argv, "move_to_point"); 
	ros::NodeHandle myNodeHandle;
	MoveToPoint myMoveToPoint (myNodeHandle);
	return 0;
}