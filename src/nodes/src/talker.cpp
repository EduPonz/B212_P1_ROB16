#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/console.h>
#include "geometry_msgs/Point.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;

  //ros::Publisher coord_pub = n.advertise<geometry_msgs::Point>("coordinates", 1000); 
  ros::Publisher coord_pub = n.advertise<std_msgs::String>("success_fail", 1000);
  /*ros::Rate poll_rate(100);
  while(coord_pub.getNumSubscribers() == 0)
    poll_rate.sleep();*/

  ros::Rate loop_rate(1);

  while (ros::ok())
  {
      std_msgs::String msg;
      std::stringstream ss;
      ss << "Successful ";
      msg.data = ss.str();

      coord_pub.publish(msg);

      ros::spinOnce();
      loop_rate.sleep();
    }

  return 0;
}
