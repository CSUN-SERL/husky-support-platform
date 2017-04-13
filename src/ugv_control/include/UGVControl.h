#ifndef HUSKY_MOVER_H
#define HUSKY_MOVER_H

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <iostream>
#include "Position.h"
#include "Destination.h"
#include "VectorAngleCalculator.h"
#include "Vector.h"

class UGVControl {
public:
    UGVControl();

    ~UGVControl();

    void crawl(double f);

    void turn(double r);

    void stop();

    void moveTo(double x, double y);

    bool hasArrived();

    bool arm();
    
    bool isArmed();

    int GetBattery() {
        //todo dont hard code this
        return -1;
    };

    //        void jSONFileEditorMissionStatus(std::string Stringer, std::string buffer);
    //        void jSONFileEditorBattery(std::string Stringer, std::string buffer);
    //        std::string toString(int integer);
    //        std::string jSONFileStringObject();

private:
    double autoAngularSpeed = 0.4;
    double autoLinearSpeed = 0.2;
    double angularTolerance = 5.0;
    double destinationTolerance = 10.0;
    double forward;
    double rotate;
    bool initiallyAligned;
    bool arrived;
    bool armed;
    ros::NodeHandle n;
    ros::Publisher husky_pub;
    ros::Publisher pub_events;
    ros::Timer moveTimer;
    ros::Timer moveToTimer;
    ros::Timer eventTimer;
    Position* position;
    Destination destination;
    VectorAngleCalculator angleCalc;

    void initiateAttributes();

    void initiateObjects();

    void initiatePublishers();

    void initiateSubscribers();

    void move(const ros::TimerEvent& event);

    void autoMove(const ros::TimerEvent& event);

    void moveToDestintion();

    void publishEvent(const ros::TimerEvent& event);

    void align();

    bool isAligned();

    std::vector<std::string> random_msgs;
};

#endif /* HUSKY_MOVER_H */
