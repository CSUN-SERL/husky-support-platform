#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <iostream>

#ifndef HUSKY_MOVER_H
#define HUSKY_MOVER_H
class UGVControl{

    public:
        UGVControl(){}

        void crawl(double f){}

        void turn(double r){}

        void stop(){}

    private:
        double forward;
        double rotate;
        ros::NodeHandle n;
        ros::Publisher husky_pub;
        ros::Subscriber controller_sub,
                        location_sub,
                        laser_sub;
        ros::Timer moveTimer;
        sensor_msgs::LaserScan laser;

        void InitialSetup(){}

        void move(const ros::TimerEvent& event){}

        void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
        {
            laser=*scan;
            for(int i = 0; i < laser.ranges.size(); i++){
            	ROS_INFO("point_of_ranges=[%f] \n", laser.ranges[i]); // this works
           }
        }

        void LocationCallback(const nav_msgs::Odometry::ConstPtr& msg)
        {
          ROS_INFO("Seq: [%d]", msg->header.seq);
          ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
          ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
          ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
        }
};

#endif /* HUSKY_MOVER_H */
