#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <iostream>

#ifndef HUSKY_MOVER_H
#define HUSKY_MOVER_H
class UGVControl{
    
    public:
        UGVControl()
        {
            forward = 0;
            rotate = 0;    
            setupPublishers();
            moveTimer = n.createTimer(ros::Duration(0.1), &UGVControl::move, this);
        }
        
        void crawl(double f){
            forward = f;
        }
        
        void turn(double r){
            rotate = r;
        }
        
        void stop(){
            forward = 0;
            rotate = 0;
        }
        
    private:
        double forward;
        double rotate;
        ros::NodeHandle n;
        ros::Publisher husky_pub;
        ros::Subscriber controller_sub;
        ros::Timer moveTimer;
                 
        void move(const ros::TimerEvent& event)
        {
            geometry_msgs::Twist msg;
            msg.linear.x = forward;
            msg.linear.y = 0.0;
            msg.linear.z = 0.0;
            msg.angular.x = 0.0;
            msg.angular.y = 0.0;
            msg.angular.z = rotate;
            husky_pub.publish(msg); 
            
        } 
        
        void setupPublishers()
        {
            husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);  
        }
        


};

#endif /* HUSKY_MOVER_H */

