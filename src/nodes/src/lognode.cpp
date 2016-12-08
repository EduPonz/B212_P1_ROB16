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

using namespace std;

void coord_func(const geometry_msgs::Point::ConstPtr& point_msg) {
  ROS_INFO("The operation has been received for the coordinates: x: %f y: %f", point_msg->x, point_msg->y);
}

void task_func(const std_msgs::String::ConstPtr& task_msg) {
  ROS_INFO("The '%s' operation has been received!", task_msg->data.c_str());
}

void status_func(const std_msgs::String::ConstPtr& status_msg) {
  ROS_INFO("%s", status_msg->data.c_str());
}

void quat_func(const geometry_msgs::Quaternion::ConstPtr& quaternion_msg){
  ROS_INFO("The operation has been received for the coordinates: x: %f y: %f z: %f w: %f",
            quaternion_msg->x, quaternion_msg->y, quaternion_msg->z, quaternion_msg->w);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "lognode");
  ros::NodeHandle n;
  ros::Subscriber click_sub = n.subscribe("point_coordinates", 100, coord_func);
  ros::Subscriber quat_sub = n.subscribe("quat_coordinates", 100, quat_func);
  ros::Subscriber task_sub = n.subscribe("task", 100, task_func);
  ros::Subscriber status_sub = n.subscribe("status", 100, status_func);
  ros::spin();
  return 0;
}