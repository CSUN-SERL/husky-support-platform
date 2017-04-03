cmake_minimum_required(VERSION 2.8.3)
project(path_planning)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg message_generation lcar_msgs)

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
   src/Graph.cpp
   src/ServiceCall.cpp
 )

add_dependencies(${PROJECT_NAME}
                ${catkin_EXPORTED_TARGETS})

add_executable(driver src/driver.cpp)
target_link_libraries(driver ${catkin_LIBRARIES} ${PROJECT_NAME})

add_executable(driverServer src/driverServer.cpp)
target_link_libraries(driverServer ${catkin_LIBRARIES} ${PROJECT_NAME})

