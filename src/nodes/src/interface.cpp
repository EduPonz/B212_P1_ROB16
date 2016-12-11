#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"
//#include "geometry_msgs/Quaternion.h"
//#include "geometry_msgs/QuaternionStamped.h"
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
#include <math.h>
#include <time.h>

using namespace std;

class Interface {
  private:
    ros::Subscriber click_sub;
    // Variable to store coordinates from rViz
    float x_cor;
    float y_cor;
    float z_cor;
    float w_cor;
    // receiving coordinates
    float receivingx = -4.43;
    float receivingy = -1.1;
    float receivingd = 45;
    // Shipping coordinates
    float shippingx = 0.621;
    float shippingy = -1.86;
    float shippingd = 60;

    int robot_choice = 0;

    //Robot choosing function #sodynamic
    void _chooseRobot(int &robot_choice) {
      srand(time(NULL));
      int i = rand()%9+1;
      cout << endl << " The robot " << i << " has been assigned for this task." << endl;
    }

    void _publishTask (int t, ros::Publisher task_pub) {
        string task;
        switch (t){
            case 1:
                task = "Checklist";
                break;
            case 2:
                task = "Move";
                break;
        }

        std_msgs::String task_msg;
        // Sending task to lognode
        task_msg.data = task;
        // Publishing task to topic 
        task_pub.publish(task_msg);
        // Spin used to initialize the callback function in publishing
        ros::spinOnce(); 
    }

    void _databaseInterface (int &databaseOption) {
        cout << endl <<" Which product would you like to pick?" << endl
             << "   Carlsberg---> 1" << endl
             << "   Tuborg------> 2" << endl
             << "   NewCastle---> 3" << endl
             << "   Guinness----> 4" << endl
             << "   Pepsi-------> 5" << endl
             << "   Coca-Cola---> 6" << endl
             << "   Fanta-------> 7" << endl
             << "   Sprite------> 8" << endl
             << "   Squash------> 9" << endl
             << "   Cocio-------> 10" << endl
             << "   Red Bull----> 11" << endl
             << "   Nestea------> 12" << endl
             << " Your choice: ";
        cin >> databaseOption;
    }

    void _publishPoint (float x, float y, float z, ros::Publisher coordPublisher){
        geometry_msgs::Point point_msg;
        point_msg.x = x;
        point_msg.y = y;
        point_msg.z = z;
        //quaternion_msg.w = w;
        coordPublisher.publish(point_msg); 
        ros::spinOnce();
    }

    void _moveInterface (ros::Publisher coord_pub, ros::NodeHandle n) {
        int choice = 0;
        //dynamic stuff lata

        cout << endl << " Where do you want the robot to go?" << endl
             << "  Press 1 for Receiving" " (" << receivingx  << ", " << receivingy << ", " << receivingd << ")" << endl
             << "  Press 2 for Shipping" " ("  << shippingx   << ", " << shippingy  << ", " << shippingd << ")" << endl
             << "  Press 3 for Database"      << endl
             << "  Press 4 for Dynamic Point" << endl << " Your choice: ";
        geometry_msgs::Point point_msg;
        cin >> choice;        

        switch(choice){
              case 1:
                _publishPoint (receivingx, receivingy, receivingd, coord_pub);
                break;
              case 2:
                _publishPoint (shippingx, shippingy, shippingd, coord_pub);
                break;
              case 3:
                int databaseOption;
                _databaseInterface (databaseOption);
                _orderProcessing (databaseOption, coord_pub);
                break;
              case 4:
                // Making a subscription to the rviz coordinate topic "clicked point"
                click_sub = n.subscribe("clicked_point", 100, &Interface::_rvizClick, this);                   
              
                // Will continue to initialize the callback function until a set of coordinates
                // has been published from rviz. i.e. the value of x coordinate changes.
                while( (x_cor == 0) && (y_cor == 0)) {
                    // Initialize call back function in a loop that will end when coordinates are found.
                    ros::spinOnce();  
                }
                point_msg.x = x_cor;  
                point_msg.y = y_cor;
                coord_pub.publish(point_msg); 
                ros::spinOnce();
                break;

              default:
                cout << " Sorry, I didn't understand that. Please insert a new location command:" << endl;
                cin >> choice;
                break;
          } 
            // Publishing coordinates to topic
            
            x_cor = 0;
            y_cor = 0;
    }

    float _numberBuild(ifstream &file) {
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

    void _readFunc(float &xval, float &yval, float &zval, int lineNumb) {

        ifstream file("data.txt");
        string line;
        for (int i = 1; i < lineNumb; i++){
            getline (file, line);
        }
        file.ignore(256,' ');
        xval = _numberBuild(file);
        yval = _numberBuild(file);
        zval = _numberBuild(file);
        //wval = _numberBuild(file);
        file.close();
    }

    void _orderProcessing (int order, ros::Publisher coordPublisher) {
        float xval;
        float yval;
        float zval;
        //float wval;
        _readFunc(xval, yval, zval, order);
        _publishPoint(xval, yval, zval, coordPublisher);
    }

    string _getFile (std::ifstream& File) {
        string Lines = "";       
        if (File.good ()) {
        while (File.good ()) {
            string TempLine;               
            std::getline (File , TempLine);
            TempLine += "\n";          
            Lines += TempLine;         
        }
            return Lines;
        }else {
            return "\n ERROR File does not exist.";
        }
    }

    void _owlBotInterface (ros::Publisher coord_pub, ros::Publisher task_pub, ros::NodeHandle n) {
        int task;
        _owlBotFront();
        do {
            cout << endl << " Which task do you want to perfom?" << endl
                 << "   Press 1 for Checklist" << endl
                 << "   Press 2 for Move"      << endl
                 << "   Press 3 for Quit"      << endl
                 << " Your choice: ";
            cin >> task;
            switch (task){
                case 1:
                    _chooseRobot(robot_choice);
                    _publishTask (task, task_pub);
                    break;
                case 2:
                    _publishTask (task, task_pub);
                    _moveInterface (coord_pub, n);
                    _chooseRobot(robot_choice);
                    break;
                case 3:
                    cout << endl << " Thanks for helping us with our hard work!" << endl;
                    _owlBotFront();
                    break;
                default:
                    cout << endl << " Sorry, I couldn't understand that, try again!" << endl;
                    break;
            }
        // Will continue to run the program as long as 3 is not the input for the variable "task"
        }while(task != 3);
    }

    void _owlBotFront () {
        ifstream Reader ("ascii.txt");
        string Art = _getFile (Reader);    
        cout << Art << std::endl;              
        Reader.close ();
    }

    // Callback equation for getting rViz coordinates 
    void _rvizClick(const geometry_msgs::PointStamped::ConstPtr& msg) {
  
      x_cor = msg->point.x;
      y_cor = msg->point.y;
      z_cor = msg->point.z;
      ROS_INFO(" The picked points from rViz are: %f, %f, %f", x_cor, y_cor, z_cor);
    }
    
  public:
    // Class constructor
    Interface(ros::NodeHandle n) {

      // Making publisher coord_pub to advertise the coordinates to topic "coordinates" for lognode and the goto node
        ros::Publisher coordPublisher = n.advertise<geometry_msgs::Point>("point_coordinates", 1000);
        ros::Publisher taskPublisher = n.advertise<std_msgs::String>("task", 1000);
        _owlBotInterface (coordPublisher, taskPublisher, n);
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
