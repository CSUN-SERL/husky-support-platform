#include "UGVControl.h"

class UGVControl{

    public:
        UGVControl()
        {
            forward = 0;
            rotate = 0;
            this->InitialSetup();
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

        void InitialSetup()
        {
          //publishers
          husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
          //subscribers
          location_sub = n.subscribe("husky_velocity_controller/odom", 1000, LocationCallback);
          laser_sub = n.subscribe("scan", 1000, LaserCallback);
        }
};
