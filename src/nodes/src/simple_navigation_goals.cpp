#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "sound_play/sound_play.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class checklist 
{
  private:
    string task_temp;
    std::string path_to_sounds;

    void task_func(const std_msgs::String::ConstPtr& task_msg)
    {
      task_temp = task_msg->data;
      ROS_INFO("The 'checklist' operation has been received!");
    }  

    void step1()
    {

      MoveBaseClient ac("move_base", true);

      while(!ac.waitForServer(ros::Duration(5.0)))
      {
        ROS_INFO("Waiting for the move_base action server to come up");
      }

      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id = "base_link";
      goal.target_pose.header.stamp = ros::Time::now();

      goal.target_pose.pose.position.x = 1.0;
      goal.target_pose.pose.orientation.w = 1.0;

      ROS_INFO("Sending goal");
      ac.sendGoal(goal);

      ac.waitForResult();

      std::stringstream status_ss;

      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)      
      {
        status_ss << "Hooray, the base moved 1 meter forward";
      }
      else
      {
        status_ss << "It's fucked bruv.";
      }

      check_status.data = status_ss.c_str();
      check_pub.publish(check_status);
    }

  public:
    checklist(ros::NodeHandle n) 
    {
      ros::Subscriber task_sub = n.subscribe("task", 100, task_func);
      
      sound_play::SoundClient sc;
      path_to_sounds = "";

      ros::Rate loop_rate(10);
      ros::Publisher check_pub = n.advertise<std_msgs::String>("check_status", 1000);

      if(task_temp == "checklist")
      {
        //signal operation start 
        sc.playWave(path_to_sounds+"ship_bell.wav");
        //checklist step1
        step1();
        step2();
      }
    }
    ~checklist() {};
}

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  ros::NodeHandle myNodeHandle;
  Interface myChecklist  (myNodeHandle);
  
}