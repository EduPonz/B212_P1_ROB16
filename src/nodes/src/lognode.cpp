#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
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

void coord_func(const geometry_msgs::Point::ConstPtr& msg) {
  ROS_INFO("The operation has been received for these coordinates: x: %f y: %f", msg->x, msg->y);
}

void task_func(const std_msgs::String::ConstPtr& task_msg) {
  ROS_INFO("The '%s' operation has been received!", task_msg->data.c_str());
}

void status_func(const std_msgs::String::ConstPtr& status_msg) {
  ROS_INFO("%s", status_msg->data.c_str());
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "lognode");
  ros::NodeHandle n;
  ros::Subscriber click_sub = n.subscribe("coordinates", 100, coord_func);
  ros::Subscriber task_sub = n.subscribe("task", 100, task_func);
  ros::Subscriber status_sub = n.subscribe("status", 100, status_func);
  ros::spin();
  return 0;
}