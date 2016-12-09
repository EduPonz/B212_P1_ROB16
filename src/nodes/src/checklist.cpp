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
    std::string task_temp;
    //std::string path_to_sounds;

    void _taskFunc(const std_msgs::String::ConstPtr& task_msg) {
      task_temp = task_msg->data;
    }

    void _publishStatus (string s, ros::Publisher check_pub) {
      string status = s;
      std_msgs::String status_msg;
      status_msg.data = status;
      check_pub.publish(status_msg);
      
      ros::spinOnce(); 
    }

    void _stepOne(ros::Publisher check_pub) {

      MoveBaseClient ac("move_base", true);
      string s;

      while(!ac.waitForServer(ros::Duration(5.0))) {
        s = "Waiting for the move_base action server to come up";
        _publishStatus(s, check_pub);
      }

      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id = "base_link";
      goal.target_pose.header.stamp = ros::Time::now();

      goal.target_pose.pose.position.x = 1.0;
      goal.target_pose.pose.orientation.w = 1.0;

      s = "Sending goal";
      _publishStatus(s, check_pub);
      ac.sendGoal(goal);

      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        s = "Step 1 has been completed, the base moved 1 meter forward";
        _publishStatus(s, check_pub);
      }else {
        s = "Step 1 failed";
        _publishStatus(s, check_pub);
      }
    }

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

      goal.target_pose.pose.position.x = 1.0;
      goal.target_pose.pose.orientation.w = 0.0;

      s = "Sending goal";
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
      goal.target_pose.pose.orientation.w = 0.0;

      s = "Sending goal";
      _publishStatus(s, check_pub);
      ac.sendGoal(goal);

      ac.waitForResult();

      if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        s = "Step 3 has been completed, the base moved 1 meter forward";
        _publishStatus(s, check_pub);
      }else {
        s = "Step 3 failed";
        _publishStatus(s, check_pub);
      }
    }

  public:
    Checklist(ros::NodeHandle n) {
      ros::Subscriber task_sub = n.subscribe("task", 100, &Checklist::_taskFunc, this);

      ros::Rate loop_rate(10);
      ros::Publisher check_pub = n.advertise<std_msgs::String>("checklist_status", 100);

      if(task_temp == "Checklist") {
        //signal operation start 
        //sc.playWave(path_to_sounds+"ship_bell.wav");
        _stepOne(check_pub);
        _stepTwo(check_pub);
        _stepThree(check_pub);
        //step2();
      }
    };
    ~Checklist() {};
};

int main(int argc, char** argv){
  ros::init(argc, argv, "checklist");

  ros::NodeHandle myNodeHandle;
  Checklist myChecklist  (myNodeHandle);
  return 0;
  
}