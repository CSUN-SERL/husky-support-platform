#ifndef POSDESALIGNER_H
#define POSDESALIGNER_H

#include "Destination.h"
#include "Position.h"
#include "VectorAngleCalculator.h"
#include "ros/ros.h"

class PosDesAligner {
public:
    PosDesAligner();
    PosDesAligner(Position* pos, Destination* des, UGVControl* controller);
    void align();
    void align(const ros::TimerEvent& event);
private:
    Destination* des;
    Position* pos;
    VectorAngleCalculator vAngleClac;
    UGVControl* controller;
    ros::NodeHandle nodeHandle;
    ros::Timer alignTimer;
    
};
#endif /* POSDESALIGNER_H */