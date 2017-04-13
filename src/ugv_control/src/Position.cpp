#include "Position.h"

Position::Position() {
    this->debugMode = false;
    this->initiate();
}

Position::Position(bool debugMode) {
    // Remove After Test    
    this->debugMode = debugMode;
    this->initiate();
}

void Position::initiate() {
    bodySubscriber = nodeHandle.subscribe("vrpn_client_node/body/pose", 1000, &Position::bodyPositionCallback, this);
    headSubscriber = nodeHandle.subscribe("vrpn_client_node/head/pose", 1000, &Position::headPositionCallback, this);
}

void Position::bodyPositionCallback(const geometry_msgs::PoseStampedConstPtr & msg) {
    centerX = msg->pose.position.x * 1000;
    centerY = msg->pose.position.z * 1000;
}


void Position::headPositionCallback(const geometry_msgs::PoseStampedConstPtr & msg) {
    this->headX = msg->pose.position.x * 1000;
    this->headY = msg->pose.position.z * 1000;
    //ROS_INFO("Head: %f, %f" , this->headX, this->headY);
}

double Position::getCenterX(){
    return centerX;
}

double Position::getCenterY(){
    return centerY;
}

Vector Position::getVector(){  
    return Vector(headX - centerX, headY - centerY); 
}