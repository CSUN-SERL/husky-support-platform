#include "PosDesAligner.h"

PosDesAligner::PosDesAligner(){
    
}

PosDesAligner::PosDesAligner(Position* pos, Destination* des, UGVControl* controller){
    this->pos = pos;
    this->des = des;
    this->vAngleClac = VectorAngleCalculator();
    this->controller = controller;
    alignTimer = nodeHandle.createTimer(ros::Duration(0.1), &PosDesAligner::align, this);
    alignTimer.stop();
}

void PosDesAligner::align(){
    ROS_INFO("Align Called");
    controller->turn(10);
}

void PosDesAligner::align(const ros::TimerEvent& event){
    ROS_INFO("Align Called");
}
        
        
