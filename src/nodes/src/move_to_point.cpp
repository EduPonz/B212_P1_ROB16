#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "std_msgs/String.h"
#include <actionlib/client/simple_action_client.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>

class MoveToPoint {
	private:
		float xGoal = 0;
		float yGoal = 0;
		float zGoal = 0;
		float wGoal = 0;
		float thetaRad = 0;

		void _moveToGoal(float xGoal, float yGoal, float zGoal, float wGoal, ros::Publisher status_pub) { 
			// Define a client to send goal requests to the move_base server through a SimpleActionClient
			actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
			std_msgs::String move_status_msg;
	    	std::stringstream action_ss;
    		std::stringstream status_ss;

			// Wait for the action server to come up
			action_ss << "Waiting for the move_base action server to come up";
			move_status_msg.data = action_ss.str();
			status_pub.publish(move_status_msg);
			ros::spinOnce();
			usleep(3*pow(10, 6));

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
      			move_status_msg.data = status_ss.str(); 
			}else {
		  		status_ss << "The robot failed to reach the destination";
 			    move_status_msg.data = status_ss.str();
			}
			status_pub.publish(move_status_msg);
			ros::spinOnce();
		}

		void _coordToQuat(const geometry_msgs::Point::ConstPtr& msg){
	        thetaRad = (msg->z / 180) * M_PI;
	        xGoal = msg->x;
	        yGoal = msg->y;
	        zGoal = sin(thetaRad / 2);
	        wGoal = cos(thetaRad / 2);

    }

	public:
		MoveToPoint(ros::NodeHandle n) {
			ros::Publisher status_pub = n.advertise<std_msgs::String>("success_fail", 1000);
			ros::Subscriber click_sub = n.subscribe("point_coordinates", 100, &MoveToPoint::_coordToQuat, this);
			while((xGoal == 0) && (yGoal == 0) && (zGoal == 0) && (wGoal == 0)) {
    	    	ros::spinOnce(); 
    		}
			// Call to function moveToGoal (see below)
			_moveToGoal(xGoal, yGoal, zGoal, wGoal, status_pub);
		};
		~MoveToPoint() {};
};

int main(int argc, char** argv) {

	ros::init(argc, argv, "move_to_point"); 
	ros::NodeHandle myNodeHandle;
	while (ros::ok()){
		MoveToPoint myMoveToPoint (myNodeHandle);
	}
	return 0;
}
