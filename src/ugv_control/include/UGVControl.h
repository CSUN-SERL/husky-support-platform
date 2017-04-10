#ifndef HUSKY_MOVER_H
#define HUSKY_MOVER_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <std_msgs/Float64.h>
#include <HuskyStatus.h>

class UGVControl{

    public:
        UGVControl();
        
        ~UGVControl();

        void crawl(double f);

        void turn(double r);

        void stop();
        void statusCallBack(const husky_msgs::HuskyStatusConstPtr& msg);
        //void statusCallBack(const std_msgs::Float64ConstPtr& msg);
        void setBatteryStatus(int battery);
        int getBatteryStatus();

    private:
        double forward;
        double rotate;
        int batteryStatus;
        ros::NodeHandle n;
        ros::Publisher husky_pub;
        ros::Subscriber controller_sub,
                        location_sub,
                        laser_sub,huskyStatusSubscriber;
        ros::Timer moveTimer;
        sensor_msgs::LaserScan laser;

        void InitialSetup();

        void move(const ros::TimerEvent& event);

        void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

        void LocationCallback(const nav_msgs::Odometry::ConstPtr& msg);
        
};

#endif /* HUSKY_MOVER_H */
