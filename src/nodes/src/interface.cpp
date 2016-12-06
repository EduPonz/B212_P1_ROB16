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

//setting global varibales for coordinates from rviz
float x_cor;
float y_cor;
float z_cor;


//Robot choosing function #sodynamic
 void chooseRobot(string& robot_choice)
  {
    int num_of_bots = 2;
   
//Possibility of creating a dynamic table that registers whether a robot is available
     string robots_available[num_of_bots][2] = {
      { "robot1", "notavailable"},
      { "robot2", "available"}
     };

      bool available = false;

      do
      {
       cout << "Which robot do you want to do the task with? List of current robots: \n";
       for (int i = 0; i < num_of_bots; i++)
       {
         cout << "'" << robots_available[i][0] << "' \n";
       }
       

        cin >> robot_choice;
        
        for (int i(0); i < num_of_bots; i++)
        {
          if (robots_available[i][0] == robot_choice)
          {
            if (robots_available[i][1] == "notavailable")
            {
              cout << "Sorry, '" << robot_choice << "' is not available at this time." << endl;
              break;
            }
            else
            {
              cout << "You have chosen '" << robot_choice << "'." << endl;
              available = true;
              break;
            }
          }

        }

      }while(available == false);

    } 
    
void ctrlcstopper(int sig)
{

  ros::shutdown();
}



//Callback equation for getting rviz coordinates 
void rviz_click(const geometry_msgs::PointStamped::ConstPtr& msg)
{
  
  //ROS_INFO("Picked points from rviz: %f, %f, %f", msg->point.x, msg->point.y, msg->point.z);
  x_cor = msg->point.x;
  y_cor = msg->point.y;
  z_cor = msg->point.z;
  ROS_INFO("Picked points from rviz: %f, %f, %f", x_cor, y_cor, z_cor);
}


int main(int argc, char **argv)
{
  // PUBLISHING CODE
  init(argc, argv, "interface", ros::init_options::NoSigintHandler);
  NodeHandle n;


  //making publisher coord_pub to advertise the coordinates to topic "coordinates" for lognode and the goto node
  ros::Publisher coord_pub = n.advertise<geometry_msgs::Point>("coordinates", 1000);
  ros::Publisher task_pub = n.advertise<std_msgs::String>("task", 1000);

  
  signal(SIGINT, ctrlcstopper);

  ros::Rate loop_rate(10); //the hz it will use to push the data through the topic

  double inputx = -4.43;
  double inputy = -1.1;
  
  double shippingx = 0.621;
  double shippingy = -1.86;

  double aislex = -0.889;
  double aisley = -1.2;

  string task;
  string robot_choice = "";

// beginning of interface: requesting what action to take
  do
  { 
    cout << "Which task: 'checklist', 'move' or 'quit'?" << endl;
    cin >> task;

    if (task == "checklist" || task == "Checklist")
    {

      chooseRobot(robot_choice);

      cout << "The checklist command is being sent to '" << robot_choice << "'.\n";

      //sending task to lognode
      std_msgs::String task_msg;
      task_msg.data = task;
      task_pub.publish(task_msg); //publishing coordinates to topic 

      ros::spinOnce(); // spin used to initialize the callback function in publishing 
      

    }
    else if (task == "move" || task == "Move")
    {


      // choice of robot/
      chooseRobot(robot_choice);

      // sending task to lognode
      std_msgs::String task_msg;
      task_msg.data = task;
      
      task_pub.publish(task_msg); //publishing coordinates to topic 

      ros::spinOnce(); // spin used to initialize the callback function in publishing

        cout << "OK, where do you want the robot to go? I have these locations:" << endl; //dynamic stuff lata    

        cout << "Input(" << inputx << ", " << inputy << ") " <<
                "Shipping(" << shippingx << ", " << shippingy << ") " <<
                "Aisle(" << aislex << ", " << aisley << ") " << "Or you could choose a 'dynamic' point from 'rviz'." << endl;


        
      geometry_msgs::Point msg;
      string choice;
        cin >> choice;        
         
          if (!(choice == "dynamic" || choice == "Dynamic")) //downside of this is that gibberish gets in too
          {
            cout << "The '" << choice << "' coordinates are being sent to '" << robot_choice << "'." << endl;
          }

        do{

          if (choice == "input" || choice == "Input") 
          {
            
            msg.x = inputx;
            msg.y = inputy;

            choice = "";
          }
          else if (choice == "shipping" || choice == "Shipping")
          {

            msg.x = shippingx;
            msg.y = shippingy;

            choice = "";
          }
          else if (choice == "aisle" || choice == "Aisle")
          {

            msg.x = aislex;
            msg.y = aisley;

            choice = "";

          }
          else if (choice == "dynamic" || choice == "Dynamic")
          {

            ros::Subscriber click_sub = n.subscribe("clicked_point", 100, rviz_click); // making a subscription to the rviz coordinate topic "clicked point"                   
            while(x_cor == 0) // will continue to initialize the callback function until a set of coordinates has been published from rviz. i.e. te value of x coordinate changes.
            {
              ros::spinOnce(); // initialize call back function in a loop that will end when coordinates are found. 
            }
            
            choice = "";     
            msg.x = x_cor;  
            msg.y = y_cor;
          }
          else
          {
            cout << "Sorry, I didn't understand that. Please insert a new location command:" << endl;
            cin >> choice;
          }

        }while(choice != "");
           
    

        coord_pub.publish(msg); //publishing coordinates to topic 

        ros::spinOnce(); // spin used to initialize the callback function in publishing
        loop_rate.sleep(); //setting ros rate to sleep 
        
    }
    else if (task == "quit") //break from while loop. ending program.
    {
      cout << "Thanks for helping us with our hard work!" << endl;
      break;
    }

    else
    {
      cout << "Sorry, I couldn't understand that, try again!" << endl;
    }

}while(task != "quit"); // will continue to run the program as long as quit is never the input for the variable "choice"

  return 0;
}
