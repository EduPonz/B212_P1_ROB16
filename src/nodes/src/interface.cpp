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
#include <fstream>  //for opening, reading and writing
#include <math.h>

using namespace std;

class Interface {
  private:
    ros::Subscriber click_sub;
    // Variable to storage coordinates from rViz
    float x_cor;
    float y_cor;
    float z_cor;
    // Input Point
    float inputx = -4.43;
    float inputy = -1.1;
    // Shipping Point
    float shippingx = 0.621;
    float shippingy = -1.86;

    string task = "";
    string robot_choice = "";

    //Robot choosing function #sodynamic
    void chooseRobot(string& robot_choice) {
      int num_of_bots = 2;
   
      //Possibility of creating a dynamic table that registers whether a robot is available
      string robots_available[num_of_bots][2] = {
        { "robot1", "notavailable"},
        { "robot2", "available"   }
      };

      bool available = false;

      do {
        cout << "Which robot do you want to do the task with? List of current robots: \n";
        for (int i = 0; i < num_of_bots; i++) {
          cout << "'" << robots_available[i][0] << "' \n";
        }

        cin >> robot_choice;
        
        for (int i(0); i < num_of_bots; i++) {
          if (robots_available[i][0] == robot_choice) {
            if (robots_available[i][1] == "notavailable") {
              cout << "Sorry, '" << robot_choice << "' is not available at this time." << endl;
              break;
            }else {
              cout << "You have chosen '" << robot_choice << "'." << endl;
              available = true;
              break;
            }
          }
        }
      }while(available == false);
    } 

    void publishTask (string task, ros::Publisher task_pub) {
      std_msgs::String task_msg;
      // Sending task to lognode
      task_msg.data = task;
      // Publishing task to topic 
      task_pub.publish(task_msg);
      // Spin used to initialize the callback function in publishing
      ros::spinOnce(); 
    }

    void databaseInterface () {
        cout << "Which product would you like to pick?" << endl;
        cout << "  Carlsberg---> 1" << endl;
        cout << "  Tuborg------> 2" << endl;
        cout << "  NewCastle---> 3" << endl;
        cout << "  Guinness----> 4" << endl;
        cout << "  Pepsi-------> 5" << endl;
        cout << "  Coca-Cola---> 6" << endl;
        cout << "  Fanta-------> 7" << endl;
        cout << "  Sprite------> 8" << endl;
        cout << "Press the number for choosing an option: ";
    }

    float numberBuild(ifstream &file) {
        float n = 0;
        int sgn = 1;
        char temp;
        int c = file.peek();
        // Checking for a -
       if (c == 45){
            sgn = -1;
            file.get(temp);
      }
        c = file.peek();
        // Checking for numbers
        while((48 <= c) && (c <= 57)){
            n=10*n + (c-48);
            file.get(temp);
            c = file.peek();
        }
        //check for comma or dot
        if ((c == 46) || (c == 44)){
            file.get(temp);
            float k = 1;
            c = file.peek();
            while((48 <= c) && (c <= 57)){
                n = n + ((c-48)/(pow(10, k)));
                k = k+1;
                file.get(temp);
                c = file.peek();
            }
        }
        file.get(temp);
        n = n*sgn;
        return n;
    }

    void readfunc(float &xval, float &yval, float &zval, float &wval, int lineNumb) {

        ifstream file("data.txt");
        string line;
        for (int i = 1; i < lineNumb; i++){
            getline (file, line);
        }
        file.ignore(256,' ');
        xval = numberBuild(file);
        yval = numberBuild(file);
        zval = numberBuild(file);
        wval = numberBuild(file);
        file.close();
    }

    void orderProcessing (int order) {
        float xval;
        float yval;
        float zval;
        float wval;
        readfunc(xval, yval, zval, wval, order);
        cout << "THE COORDINATES ARE" << endl;
        cout << " 1st coord " << xval << " " << endl
             << " 2nd coord " << yval << " " << endl
             << " 3rd coord " << zval << " " << endl
             << " 4th coord " << wval << " " << endl;
    }

    void _owlBot_interface (ros::Publisher coord_pub, ros::Publisher task_pub, ros::NodeHandle n) {
        do { 
            cout << "Which task: 'checklist', 'move' or 'quit'?" << endl;
            cin >> task;

            if (task == "checklist" || task == "Checklist") {

                chooseRobot(robot_choice);
                cout << "The checklist command is being sent to '" << robot_choice << "'.\n";
                publishTask (task, task_pub);
      
            }else if (task == "move" || task == "Move") {

                chooseRobot(robot_choice);
                publishTask (task, task_pub);

                //dynamic stuff lata    
                cout << "OK, where do you want the robot to go? I have these locations:" << endl;
                cout << "Input ("     << inputx      << ", " << inputy    << ") "        << endl
                << "Shipping ("  << shippingx   << ", " << shippingy << ") "        << endl
                << "Database"                                                       << endl
                << "Or you can choose a 'dynamic' point from 'rviz'."               << endl;
    
                geometry_msgs::Point msg;
                string choice;
                cin >> choice;        

                do{
                    if (choice == "input" || choice == "Input") {
            
                        msg.x = inputx;
                        msg.y = inputy;
                        choice = "";
                        cout << "The '" << choice << "' coordinates are being sent to '" << robot_choice << "'." << endl;

                    }else if (choice == "shipping" || choice == "Shipping") {

                        msg.x = shippingx;
                        msg.y = shippingy;
                        choice = "";
                        cout << "The '" << choice << "' coordinates are being sent to '" << robot_choice << "'." << endl;

                    }else if (choice == "Database" || choice == "database") {

                        int databaseOption;
                        databaseInterface ();
                        cin >> databaseOption;
                        cout << "You chose: " << databaseOption << endl;
                        orderProcessing (databaseOption);
                        choice = "";

                    }else if (choice == "dynamic" || choice == "Dynamic") {

                        // Making a subscription to the rviz coordinate topic "clicked point"
                        click_sub = n.subscribe("clicked_point", 100, &Interface::rviz_click, this);                   
              
                        // Will continue to initialize the callback function until a set of coordinates
                        // has been published from rviz. i.e. the value of x coordinate changes.
                        while( (x_cor == 0) && (y_cor == 0)) {
                        // Initialize call back function in a loop that will end when coordinates are found.
                        ros::spinOnce();  
                        }
          
                    choice = "";     
                    msg.x = x_cor;  
                    msg.y = y_cor;

                    }else {
                        cout << "Sorry, I didn't understand that. Please insert a new location command:" << endl;
                        cin >> choice;
                    }
                }while(choice != "");   
    
                // Publishing coordinates to topic
                coord_pub.publish(msg); 
                ros::spinOnce();

                x_cor = 0;
                y_cor = 0;
    
                // Break from while loop. ending program.
            }else if (task == "quit") {
                cout << "Thanks for helping us with our hard work!" << endl;
                break;

            }else {
                cout << "Sorry, I couldn't understand that, try again!" << endl;
            }

        // Will continue to run the program as long as quit is never the input for the variable "task"
        }while(task != "quit");
    }

    // Callback equation for getting rViz coordinates 
    void rviz_click(const geometry_msgs::PointStamped::ConstPtr& msg) {
  
      x_cor = msg->point.x;
      y_cor = msg->point.y;
      z_cor = msg->point.z;
      ROS_INFO("The picked points from rViz are: %f, %f, %f", x_cor, y_cor, z_cor);
    }
  public:
    // Class constructor
    Interface(ros::NodeHandle n) {
      // Making publisher coord_pub to advertise the coordinates to topic "coordinates" for lognode and the goto node
      ros::Publisher coordPublisher = n.advertise<geometry_msgs::Point>("coordinates", 1000);
      ros::Publisher taskPublisher = n.advertise<std_msgs::String>("task", 1000);
      //ros::Rate loop_rate(10); //the hz it will use to push the data through the topic
      // Beginning of interface: requesting what action to take
      _owlBot_interface (coordPublisher, taskPublisher, n);
    };

    // Call Destructor
    ~Interface() {};
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "interface");
  ros::NodeHandle myNodeHandle;
  Interface myInterface (myNodeHandle);
  return 0;
}