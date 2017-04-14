#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sstream>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <std_msgs/Float64.h>
#include <vehicle_control.h>
#ifndef HUSKY_MOVER_H
#define HUSKY_MOVER_H
#include <string>
#include <husky_msgs/HuskyStatus.h>
#include <fstream>
#include <data_types.h>
//namespace gcs{
class UGVControl: public gcs::VehicleControl {

    public:
         const int id=gcs::VehicleType_::ugv;
        UGVControl(int id):VehicleControl(id){
            vehicleInfo.id=id;
            vehicleInfo.state.armed=false;
            
         
            forward = 0;
            rotate = 0;
            this->InitialSetup();
            moveTimer = n.createTimer(ros::Duration(0.1), &UGVControl::move, this);};

        ~UGVControl();

        void crawl(double f);

        void turn(double r);

        void stop();
        void statusCallBack(const husky_msgs::HuskyStatusConstPtr& msg);
        //void statusCallBack(const std_msgs::Float64::ConstPtr& msg);
        void BatteryPub();
        void setBatteryStatus(int battery);
        //vehicle_control GetBattery()
        //int getBatteryStatus();
        
        
        void jSONFileEditorMissionStatus(std::string Stringer, std::string buffer);
        void jSONFileEditorBattery(std::string Stringer, std::string buffer);
        std::string toString(int integer);
        std::string jSONFileStringObject();
        
        //vehicle control methods:
        void Arm(bool value);
         bool IsArmed();
     void SetMode(std::string){};
//     void SetWayPoint(const sensor_msgs::NavSatFix& location){}; // for global
//     void SetWayPoint(double lat, double lng, double alt){}; // overload for global
     void SetTarget(geometry_msgs::Pose&){}; 
     void SetTarget(double lat, double lng, double alt){};
     int GetDistanceToWP(){return 0;};
//     sensor_msgs::NavSatFix GetLocation()=0;
     void SetRTL(){}; //makes the drone go home immediately when called
     void StartMission(){ mission_mode = gcs::active; }; // todo make pure virtual and add override implementation to UAVControl
     void PauseMission(){ mission_mode = gcs::paused; };
     void ResumeMission(){ mission_mode = gcs::active; };
     void StopMission(){ mission_mode = gcs::stopped; };
     gcs::MissionMode GetMissionMode(){ return mission_mode;};
     //MissionMode GetMissionMode(){ return mission_mode; };
     float GetMissiontProgress() { return -1; };
     int GetBattery() { return vehicleInfo.state.battery; };
     std::string GetMode() { return  mode; };

    private:
        //varibles required for overriding
        //bool armedStatus;
        //std::string mission_mode=
        gcs::VehicleInfo vehicleInfo;
        //gcs::State state;
        std_msgs::String jsonMsg;
        
        
        
        //varibes required for UGV
        double forward;
        double rotate;
        //batteryStatus or percentage is found using the state object
        //int batteryStatus;
        ros::NodeHandle n;
        ros::Publisher husky_pub,status_pub;
        ros::Subscriber controller_sub,
                        location_sub,
                        laser_sub, huskyStatusSubscriber;
        ros::Timer moveTimer;
        sensor_msgs::LaserScan laser;
         
        

        void InitialSetup();

        void move(const ros::TimerEvent& event);

        void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

        void LocationCallback(const nav_msgs::Odometry::ConstPtr& msg);
        protected:
             void Run(){};
             void RunLocal(){};
             void RunGlobal(){};

};
//}
#endif /* HUSKY_MOVER_H */