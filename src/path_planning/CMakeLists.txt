cmake_minimum_required(VERSION 2.8.3)
project(path_planning)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg message_generation)

set(path_planning_INCLUDE_DIRECTORIES
        src
	 )

include_directories(${path_planning_INCLUDE_DIRECTORIES}
                    
                    ${catkin_INCLUDE_DIRS} )
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES husky
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)



## Declare a C++ library
 add_library(${PROJECT_NAME}
   src/Obstacle.cpp
   src/PathPlanning.cpp
   src/Path.cpp
 )

