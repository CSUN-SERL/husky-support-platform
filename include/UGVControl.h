#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <iostream>
//#include <std_msgs/Float64.h>

#ifndef HUSKY_MOVER_H
#define HUSKY_MOVER_H
class UGVControl{
    
    public:
        UGVControl();

        ~UGVControl();

        void crawl(double f);

        void turn(double r);

        void stop();
        
        /*Everything under here will be my own test code*/
        
        //std_msgs::Float64 battery();

    private:
        double forward;
        double rotate;
        /*My own variables */
       // std_msgs::Float64 direction_x_;
        float batt;
        
        ros::NodeHandle n;
        ros::Publisher husky_pub;
        ros::Subscriber controller_sub,
                        location_sub,
                        laser_sub;
        ros::Timer moveTimer;
        sensor_msgs::LaserScan laser;

        void InitialSetup();

        void move(const ros::TimerEvent& event);

        void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

        void LocationCallback(const nav_msgs::Odometry::ConstPtr& msg);

};

#endif /* HUSKY_MOVER_H */