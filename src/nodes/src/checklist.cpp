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
//#include "sound_play/sound_play.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace std;

class Checklist 
{
  private:
    ros::Subscriber task_sub;
    ros::Publisher check_pub;
    std::string task_temp;
    // Callback function for the /task subscription, after this function calls on the next
    // operation steps that are all functions themselfs (_stepOne)
    void _taskFunc(const std_msgs::String::ConstPtr& task_msg) {
      task_temp = task_msg->data;
      if(task_temp == "Checklist") {
        _stepOne(check_pub);
        _stepTwo(check_pub);
        _stepThree(check_pub);
        _stepFour(check_pub);
      }
    }
    // Publishing function to publish the status of the checklist operation
    void _publishStatus (string s, ros::Publisher check_pub) {
      string status = s;
      std_msgs::String status_msg;
      status_msg.data = status;
      check_pub.publish(status_msg);
      
      ros::spinOnce(); 
    }
    // Step one of the checklist operation
    void _stepOne(ros::Publisher check_pub) {

      MoveBaseClient ac("move_base", true);
      string s;

      while(!ac.waitForServer(ros::Duration(5.0))) {
        s = "Waiting for the move_base action server to come up";
        _publishStatus(s, check_pub);
      }
      
      move_base_msgs::MoveBaseGoal goal;
      // In this case base_link was use as the frame ID so the robot does not use the map generated
      // and can perform the operations in adequte space
      goal.target_pose.header.frame_id = "base_link";
      goal.target_pose.header.stamp = ros::Time::now();
      // Target positions from the starting point
      goal.target_pose.pose.position.x = 2.0;
      goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.position.z = 0.0;
      // Orienation as quaternion coordinates
      goal.target_pose.pose.orientation.x = 0.0;
      goal.target_pose.pose.orientation.y = 0.0;
      goal.target_pose.pose.orientation.z = 0.0;
      goal.target_pose.pose.orientation.w = 1.0;

      s = "Sending checklist goal";
      _publishStatus(s, check_pub);
      ac.sendGoal(goal);
      ac.waitForResult();
      // Publishing the success status of the operation
      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        s = "Step 1 has been completed. Arrived to origin.";
        _publishStatus(s, check_pub);
      }else { // Publishing the failure status of the operation
        s = "Step 1 failed";
        _publishStatus(s, check_pub);
      }
    }
    // Same function as before but using different coordinates
    void _stepTwo(ros::Publisher check_pub) {

      MoveBaseClient ac("move_base", true);
      string s;

      while(!ac.waitForServer(ros::Duration(5.0))) {
        s = "Waiting for the move_base action server to come up";
        _publishStatus(s, check_pub);
      }

      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id = "base_link";
      goal.target_pose.header.stamp = ros::Time::now();

      goal.target_pose.pose.position.x = 0.0;
      goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.position.z = 0.0;

      goal.target_pose.pose.orientation.x = 0.0;
      goal.target_pose.pose.orientation.y = 0.0;
      goal.target_pose.pose.orientation.z = 0.0;
      goal.target_pose.pose.orientation.w = -1.0;

      s = "Sending checklist goal";
      _publishStatus(s, check_pub);
      ac.sendGoal(goal);

      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        s = "Step 2 has been completed, the base moved 1 meter forward";
        _publishStatus(s, check_pub);
      }else {
        s = "Step 2 failed";
        _publishStatus(s, check_pub);
      }
    }
    // Same function as before but using different coordinates
    void _stepThree(ros::Publisher check_pub) {

      MoveBaseClient ac("move_base", true);
      string s;

      while(!ac.waitForServer(ros::Duration(5.0))) {
        s = "Waiting for the move_base action server to come up";
        _publishStatus(s, check_pub);
      }

      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id = "base_link";
      goal.target_pose.header.stamp = ros::Time::now();

      goal.target_pose.pose.position.x = 0.0;
      goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.position.z = 0.0;

      goal.target_pose.pose.orientation.x = 0.0;
      goal.target_pose.pose.orientation.y = 0.0;
      goal.target_pose.pose.orientation.z = 0.0;
      goal.target_pose.pose.orientation.w = 1.0;

      s = "Sending checklist goal";
      _publishStatus(s, check_pub);
      ac.sendGoal(goal);

      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        s = "Step 3 has been completed, the base moved 1 meter backwards";
        _publishStatus(s, check_pub);
      }else {
        s = "Step 3 failed";
        _publishStatus(s, check_pub);
      }
    }
    // Same function as before but using different coordinates
    void _stepFour(ros::Publisher check_pub) {
      MoveBaseClient ac("move_base", true);
      string s;

      while(!ac.waitForServer(ros::Duration(5.0))) {
        s = "Waiting for the move_base action server to come up";
        _publishStatus(s, check_pub);
      }

      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id = "base_link";
      goal.target_pose.header.stamp = ros::Time::now();

      goal.target_pose.pose.position.x = 0.0;
      goal.target_pose.pose.position.y = 0.0;
      goal.target_pose.pose.position.z = 0.0;

      goal.target_pose.pose.orientation.x = 0.0;
      goal.target_pose.pose.orientation.y = 0.0;
      goal.target_pose.pose.orientation.z = 1.0;
      goal.target_pose.pose.orientation.w = 0.0;

      s = "Sending checklist goal";
      _publishStatus(s, check_pub);
      ac.sendGoal(goal);

      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        s = "Step 4 has been completed, the base turned 180 degrees";
        _publishStatus(s, check_pub);
      }else {
        s = "Step 4 failed";
        _publishStatus(s, check_pub);
      }
    }

  public:
  // Checklist class construction
    Checklist(ros::NodeHandle n) {
      ros::Subscriber task_sub = n.subscribe("task", 100, &Checklist::_taskFunc, this);
      check_pub = n.advertise<std_msgs::String>("checklist_status", 100);
      ros::spin();
    };
    ~Checklist() {};
};

int main(int argc, char** argv){
  ros::init(argc, argv, "checklist");
  ros::NodeHandle myNodeHandle;
  Checklist myChecklist  (myNodeHandle);
  return 0;
}
