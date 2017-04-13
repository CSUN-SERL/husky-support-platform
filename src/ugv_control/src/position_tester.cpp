#include "ros/ros.h"
#include "Demo.h"



int main(int argc, char **argv) {
    ros::init(argc, argv, "husky");
    Demo d;
    ros::spin();     
}


