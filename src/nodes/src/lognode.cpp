#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/QuaternionStamped.h"
#include <ros/console.h>
#include <iostream>
#include <string.h>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <fstream> 

using namespace std;

ofstream myfile ("data_saved.txt");

class LogNode{
    private: 
//////Declaring Global variables//////
      float quatx;
      float quaty;
      float quatz;
      float quatw;
      string message;

////////////Functions//////////////

//This function converts a float into a string
      string _floatToString(float val){
        string s;
        stringstream ss (stringstream::in | stringstream::out);
        ss << val;
        s = ss.str();
        return s;
      }

//This function prints the text "The operation has been received 
//for the coordinates: " and the chosen coordinates to a txt.file
      void _saveCoordFunc(float x, float y, ofstream &myfile){
        myfile << "The operation has been received for the coordinates: (" 
               << _floatToString(x) << ") (" << _floatToString(y) << ")" << endl;
      }

//This function receives the coordinates from the interface and calls on the "_saveCoordFunc"
//while printing "The operation has been received for the coordinates: " and the coordinates 
//in a ros terminal
      void _coordFunc(const geometry_msgs::Point::ConstPtr& point_msg) {
        cout << endl;
        ROS_INFO("The operation has been received for the coordinates: x: %f y: %f", 
                  point_msg->x, point_msg->y);
        quatx = point_msg->x;
        quaty = point_msg->y;
        _saveCoordFunc(quatx, quaty, myfile);
      }

//This function prints the text "The 'the task' operation has been received!" 
//to a txt.file
      void _saveTaskFunc(string x, ofstream &myfile) {
        myfile << "The '" << x << "' operation has been received! " << endl;
      }

//This function receives the "task" text from the interface and calls on the "_saveTaskFunc"
//while printing the "task" text in a ros terminal
      void _taskFunc(const std_msgs::String::ConstPtr& task_msg) {
        cout << endl;
        ROS_INFO("The '%s' operation has been received! ", task_msg->data.c_str());
        message = task_msg->data.c_str();
        _saveTaskFunc(message, myfile);
      }

//This function prints the "status" text 
//to a txt.file
      void _saveStatusFunc(string x, ofstream &myfile){
        myfile << x << endl;
      }

//This function receives the status from the interface and calls on the "_saveStatusFunc"
//while printing the "status" text in a ros terminal
      void _statusFunc(const std_msgs::String::ConstPtr& status_msg){
        cout << endl;
        ROS_INFO("%s", status_msg->data.c_str());
        message = status_msg->data.c_str();
        _saveStatusFunc(message, myfile);
      }

//This function prints the text "The operation has been received 
//for the coordinates" and the chosen coordinates to a txt.file
      void _saveQuatFunc(float x, float y, float z, float w, ofstream &myfile){
        myfile << "The operation has been received for the coordinates: ("
         << _floatToString(x) << ") (" << _floatToString(y)
         << ") (" << _floatToString(z) << ") (" << _floatToString(w) << ")" << endl;     
      }

//This function receives the coordinates from the interface and calls on the "_saveQuatFunc"
//while printing "The operation has been received for the coordinates: " and the coordinates 
//in a ros terminal
      void _quatFunc(const geometry_msgs::Quaternion::ConstPtr& quaternion_msg){
        cout << endl;
        ROS_INFO("The operation has been received for the coordinates: x: %f y: %f z: %f w: %f",
                  quaternion_msg->x, quaternion_msg->y, quaternion_msg->z, quaternion_msg->w);
        quatx = quaternion_msg->x; 
        quaty = quaternion_msg->y;
        quatz = quaternion_msg->z;
        quatw = quaternion_msg->w;
        _saveQuatFunc(quatx, quaty, quatz, quatw, myfile);
      }
    public:

      LogNode(ros::NodeHandle n){
        ros::Subscriber click_sub = n.subscribe("point_coordinates", 100, &LogNode::_coordFunc, this);
        ros::Subscriber quat_sub = n.subscribe("quat_coordinates", 100, &LogNode::_quatFunc, this);
        ros::Subscriber task_sub = n.subscribe("task", 100, &LogNode::_taskFunc, this);
        ros::Subscriber status_sub = n.subscribe("fork_status", 100, &LogNode::_statusFunc, this);
        ros::Subscriber move_status = n.subscribe("success_fail", 100, &LogNode::_statusFunc, this);
        ros::Subscriber check_pub = n.subscribe("check_status", 100, &LogNode::_statusFunc, this);
        ros::Subscriber checklist_status_pub = n.subscribe("checklist_status", 100, &LogNode::_statusFunc, this);
        ros::spin();
      };
      ~LogNode() {};
 };


int main(int argc, char **argv) {

  ros::init(argc, argv, "lognode");
  ros::NodeHandle myNodeHandle;
  LogNode myLogNode (myNodeHandle);
  myfile.close();
  return 0;
}
