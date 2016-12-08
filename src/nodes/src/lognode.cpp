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

//////Declaring Global variables//////
float quatx;
float quaty;
float quatz;
float quatw;
string message;
ofstream myfile ("Data_Saved.txt");

////////////Functions//////////////

//This function converts a float into a string
string float_to_sting(float val){
  string s;
  stringstream ss (stringstream::in | stringstream::out);
  ss << val;
  s = ss.str();
  return s;
}

//This function prints the text "The operation has been received 
//for the coordinates: " and the chosen coordinates to a txt.file
void save_coord_func(float x, float y, ofstream &myfile){
  myfile << "The operation has been received for the coordinates: (" 
         << float_to_sting(x) << ") (" << float_to_sting(y) << ")" << endl;
}

//This function receives the coordinates from the interface and calls on the "save_coord_func"
//while printing "The operation has been received for the coordinates: " and the coordinates 
//in a ros terminal
void coord_func(const geometry_msgs::Point::ConstPtr& point_msg) {
  cout << endl;
  ROS_INFO("The operation has been received for the coordinates: x: %f y: %f", 
            point_msg->x, point_msg->y);
  quatx = point_msg->x;
  quaty = point_msg->y;
  save_coord_func(quatx, quaty, myfile);
}

//This function prints the text "The 'the task' operation has been received!" 
//to a txt.file
void save_task_func(string x, ofstream &myfile){
  myfile << "The " << x << " operation has been received! " << endl;
}

//This function receives the "task" text from the interface and calls on the "save_task_func"
//while printing the "task" text in a ros terminal
void task_func(const std_msgs::String::ConstPtr& task_msg) {
  cout << endl;
  ROS_INFO("The '%s' operation has been received! ", task_msg->data.c_str());
  message = task_msg->data.c_str();
  save_task_func(message, myfile);
}

//This function prints the "status" text 
//to a txt.file
void save_status_func(string x, ofstream &myfile){
  myfile << x << endl;
}

//This function receives the status from the interface and calls on the "save_status_func"
//while printing the "status" text in a ros terminal
void status_func(const std_msgs::String::ConstPtr& status_msg){
  cout << endl;
  ROS_INFO("%s", status_msg->data.c_str());
  message = status_msg->data.c_str();
  save_status_func(message, myfile);
}

//This function prints the text "The operation has been received 
//for the coordinates" and the chosen coordinates to a txt.file
void save_quat_func(float x, float y, float z, float w, ofstream &myfile){
  myfile << "The operation has been received for the coordinates: ("
   << float_to_sting(x) << ") (" << float_to_sting(y)
   << ") (" << float_to_sting(z) << ") (" << float_to_sting(w) << ")" << endl;     
}

//This function receives the coordinates from the interface and calls on the "save_quat_func"
//while printing "The operation has been received for the coordinates: " and the coordinates 
//in a ros terminal
void quat_func(const geometry_msgs::Quaternion::ConstPtr& quaternion_msg){
  cout << endl;
  ROS_INFO("The operation has been received for the coordinates: x: %f y: %f z: %f w: %f",
            quaternion_msg->x, quaternion_msg->y, quaternion_msg->z, quaternion_msg->w);
  quatx = quaternion_msg->x; 
  quaty = quaternion_msg->y;
  quatz = quaternion_msg->z;
  quatw = quaternion_msg->w;
  save_quat_func(quatx, quaty, quatz, quatw, myfile);
}
 


int main(int argc, char **argv) {

  ros::init(argc, argv, "lognode");
  ros::NodeHandle n;

  ros::Subscriber click_sub = n.subscribe("point_coordinates", 100, coord_func);
  ros::Subscriber quat_sub = n.subscribe("quat_coordinates", 100, quat_func);
  ros::Subscriber task_sub = n.subscribe("task", 100, task_func);
  ros::Subscriber status_sub = n.subscribe("status", 100, status_func);

  ros::spin();
  myfile.close();
  return 0;
}
