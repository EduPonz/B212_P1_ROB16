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
using namespace ros;

/*float x_cor;
float y_cor;
float z_cor;*/


void coord_func(const geometry_msgs::Point::ConstPtr& msg)
{
  ROS_INFO("The operation has been received for these coordinates: x: %f y: %f", msg->x, msg->y);
}

void task_func(const std_msgs::String::ConstPtr& task_msg)
{
  ROS_INFO("The '%s' operation has been received!", task_msg->data.c_str());
}

void status_func(const std_msgs::String::ConstPtr& status_msg)
{
  ROS_INFO("%s", status_msg->data.c_str());
}

/*
void actsrvr_func(const std_msgs::String::ConstPtr& actsrvr_msg)
{
  ROS_INFO("Waiting for action server. Please be patient...");
}

*/
/*void rviz_click(const geometry_msgs::PointStamped::ConstPtr& msg)
{
  //goal = *msg;
  //ROS_INFO("Picked points from rviz: %f, %f, %f", msg->point.x, msg->point.y, msg->point.z);
  x_cor = msg->point.x;
  y_cor = msg->point.y;
  z_cor = msg->point.z;
  ROS_INFO("Picked points from rviz: %f, %f, %f", x_cor, y_cor, z_cor);

      //get_coordinates(goal, x, y, z);
}*/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lognode");
  ros::NodeHandle n;
  ros::Subscriber click_sub = n.subscribe("coordinates", 100, coord_func);
  ros::Subscriber task_sub = n.subscribe("task", 100, task_func);
  ros::Subscriber status_sub = n.subscribe("status", 100, status_func);
  //ros::Subscriber actionsrv_sub = n.subscribe("action_server", 100, actsrvr_func);

  ros::spin();
    

  return 0;
}
