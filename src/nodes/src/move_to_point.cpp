#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include "std_msgs/String.h"
#include <actionlib/client/simple_action_client.h>
#include "geometry_msgs/Point.h"
#include <iostream>
#include <string.h>
#include <string>

//declaring global floats to take on coordinate values
float xcoord = 0;
float ycoord = 0;


/** function declarations **/
void moveToGoal(float xGoal, float yGoal, ros::Publisher status_pub); 

void coord_func(const geometry_msgs::Point::ConstPtr& msg);

// Main function
int main(int argc, char** argv){
	ros::init(argc, argv, "move_to_point"); 
	ros::NodeHandle n;
	ros::spinOnce();

	ros::Publisher status_pub = n.advertise<std_msgs::String>("success_fail", 1000); //initializing publisher to advertise status to lognode

	ros::Subscriber click_sub = n.subscribe("coordinates", 100, coord_func); //initialising subscriber to receive coordinates published by interface

	while(xcoord == 0) // will continue to call the callback function until a set of coordinates has been published
            {
              ros::spinOnce(); 
            }

	moveToGoal(xcoord, ycoord, status_pub); //call to function moveToGoal (see below)

	return 0;
}


void moveToGoal(float xGoal, float yGoal, ros::Publisher status_pub){ 

	//define a client to send goal requests to the move_base server through a SimpleActionClient
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
	std_msgs::String msg;
    std::stringstream action_ss;
    std::stringstream status_ss;

	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(5.0))){
		action_ss << "Waiting for the move_base action server to come up";
		msg.data = action_ss.str();
		status_pub.publish(msg);
		ros::spinOnce();
	}

	//declaring varible 'goal' as type move_bas_msgs::MoveBaseGoal
	move_base_msgs::MoveBaseGoal goal;

	//set up the frame parameters
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();


	/* moving towards the goal*/
	goal.target_pose.pose.position.x =  xGoal;
	goal.target_pose.pose.position.y =  yGoal;
	goal.target_pose.pose.position.z =  0.0;
	goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = 0.0;
	goal.target_pose.pose.orientation.w = 1.0;

		//ROS_INFO("Sending goal location ...");
	ac.sendGoal(goal);

	ac.waitForResult();

	//if else statement for whether or not the robot succeeded in motion operation.
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		
      status_ss << "The robot has reached the destination";
      msg.data = status_ss.str();
      
	}
	else{
	  status_ss << "The robot failed to reach the destination";
      msg.data = status_ss.str();

	}
	status_pub.publish(msg);

     ros::spinOnce();
}


void coord_func(const geometry_msgs::Point::ConstPtr& msg)
{
//assigning the values pointed to to the global variables so they can be used in the main function.
  xcoord = msg->x;
  ycoord = msg->y;
}



