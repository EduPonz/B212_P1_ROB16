cmake_minimum_required(VERSION 2.8.3)
project(nodes)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
	roscpp
	message_generation
	std_msgs
	geometry_msgs
	genmsg
	move_base_msgs
	actionlib
	)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
add_message_files(FILES Point.msg)
add_message_files(FILES PointStamped.msg)
add_message_files(FILES Quaternion.msg)
add_message_files(FILES QuaternionStamped.msg)
#add_service_files(FILES AddTwoInts.srv)

## Add message files

add_message_files(
	DIRECTORY msg
	FILES
	Point.msg
	PointStamped.msg
	Quaternion.msg
	QuaternionStamped.msg
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs geometry_msgs)

## Declare a catkin package
catkin_package()

## Build talker and lognode
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(lognode src/lognode.cpp)
target_link_libraries(lognode ${catkin_LIBRARIES})
add_dependencies(lognode nodes_generate_messages_cpp)

add_executable(interface src/interface.cpp)
target_link_libraries(interface ${catkin_LIBRARIES})
add_dependencies(interface nodes_generate_messages_cpp)

add_executable(move_to_point src/move_to_point.cpp)
target_link_libraries(move_to_point ${catkin_LIBRARIES})
#add_dependencies(move_to_point_generate_messages_cpp)

add_executable(checklist src/checklist.cpp)
target_link_libraries(checklist ${catkin_LIBRARIES})