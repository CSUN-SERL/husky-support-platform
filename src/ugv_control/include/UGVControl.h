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
#include <husky_msgs/HuskyStatus.h>
#include <fstream>

class UGVControl {
public:
    struct Point
    {
        double x;
        double y;
    };
    
    UGVControl();

    ~UGVControl();
    void setBatteryStatus(int battery);
    void BatteryPub();
    std::string jSONFileStringObject();
    void jSONFileEditorBattery(std::string Stringer, std::string buffer);

    void statusCallBack(const husky_msgs::HuskyStatusConstPtr& msg);
    void setMission(const std::vector<Point>& waypoints);
    std::string toString(int integer);
    void jSONFileEditorMissionStatusFalse();
    void jSONFileEditorMissionStatusTrue();
    void startMission();
    
    void pauseMission();
    
    void resumeMission();
    
    void cancelMission();
    
    void crawl(double f);

    void turn(double r);

    void stop();


    bool hasArrived();

    bool arm(bool arm);
    
    bool isArmed();

    bool isOnMission();
    
    int GetBattery() {
        //todo dont hard code this
        return battery_percentage;
    };

    //        void jSONFileEditorMissionStatus(std::string Stringer, std::string buffer);
    //        void jSONFileEditorBattery(std::string Stringer, std::string buffer);
    //        std::string toString(int integer);
    //        std::string jSONFileStringObject();

private:
    int missionStatus;
    std::string buffer=UGVControl::jSONFileStringObject();

    std_msgs::String jsonMsg;
    int battery_percentage;
    double autoAngularSpeed = 0.4;
    double autoLinearSpeed = 0.2;
    double angularTolerance = 5.0;
    double destinationTolerance = 50.0;
    double forward;
    double rotate;
    bool initiallyAligned;
    bool arrived;
    bool armed;
    bool onMission;
    ros::NodeHandle n;
    ros::Subscriber huskyStatusSubscriber;
    ros::Publisher husky_pub;
    ros::Publisher pub_events;
    ros::Publisher status_pub;
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
    
    void moveTo(double x, double y);

    void autoMove(const ros::TimerEvent& event);

    void moveToDestintion();

    void publishEvent(const ros::TimerEvent& event);

    void align();

    bool isAligned();

    double calcAutoAngularSpeed(double vectorsAngle);
    
    void removeMission();
    
    void moveToNextWayPoint();
    
    int currentWaypoint;
    
    std::vector<std::string> random_msgs;
    
    std::vector<Point> waypoints;
    
    
};

#endif /* HUSKY_MOVER_H */
