#ifndef POSITION_H
#define POSITION_H

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "Vector.h"

class UGVControl;

class Position {
public:
    Position();
    Position(bool debugMode);
    double getCenterX();
    double getCenterY();
    Vector getVector();
       
private:    
    bool debugMode;
    double centerX;
    double centerY;
    double headX;
    double headY;
    ros::NodeHandle nodeHandle;
    ros::Subscriber bodySubscriber;
    ros::Subscriber headSubscriber;
    
    void debug(bool mode);
    void initiate();
    void bodyPositionCallback(const geometry_msgs::PoseStampedConstPtr & msg);
    void headPositionCallback(const geometry_msgs::PoseStampedConstPtr & msg);
};

#endif /* POSITION_H */

