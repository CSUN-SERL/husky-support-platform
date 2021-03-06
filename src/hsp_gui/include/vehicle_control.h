/* 
 * File:   vehicle_control.h
 * Author: n8
 *
 * Created on September 7, 2016, 5:09 PM
 */

#ifndef VEHICLECONTROL_H
#define VEHICLECONTROL_H

#include <string>
#include <sensor_msgs/NavSatFix.h>

//#include <vehicle/data_types.h>
#include <data_types.h>
#include<std_msgs/Int32.h>
namespace gcs
{

class VehicleControl
{
    
public:
    const int id; // child classes provide id to this class' constructor
    
    VehicleControl(int id): id(id){};
    virtual ~VehicleControl(){};
    
    virtual void Arm(bool value) = 0;
    virtual bool IsArmed() = 0;
    virtual void SetMode(std::string)=0;
//    virtual void SetWayPoint(const sensor_msgs::NavSatFix& location){}; // for global
//    virtual void SetWayPoint(double lat, double lng, double alt){}; // overload for global
    virtual void SetTarget(geometry_msgs::Pose&)=0; 
    virtual void SetTarget(double lat, double lng, double alt) = 0;
    virtual int GetDistanceToWP() = 0;
//    virtual sensor_msgs::NavSatFix GetLocation()=0;
    virtual void SetRTL() = 0; //makes the drone go home immediately when called
    virtual void StartMission() = 0;//{ mission_mode = active; }; // todo make pure virtual and add override implementation to UAVControl
    virtual void PauseMission() = 0;//{ mission_mode = paused; };
    virtual void ResumeMission() = 0;//{ mission_mode = active; };
    virtual void StopMission() = 0;//{ mission_mode = stopped; };
    virtual MissionMode GetMissionMode(){ /*return mission_mode;*/ };
    virtual float GetMissiontProgress() { return -1; };
    virtual int GetBattery() { return battery; };
    virtual std::string GetMode() { return  mode; };
    
    bool RecievedHeartbeat() { return heartbeat_recieved; };
    bool MissionComplete() { 
        if(mission_mode == stopped){
            return true;
        }
        else if(mission_mode == MissionMode::invalid)
        {
            return false;
        }
        
        return mission_completed;
    };
    
protected:

    virtual void Run()=0;
    virtual void RunLocal()=0;
    virtual void RunGlobal()=0;
    
    ros::Timer run_timer;
    MissionMode mission_mode = stopped;
    int battery = 0;
    std::string mode; // flight mode or related
    
    ros::Publisher                  pub_heartbeat;
    bool                            connection_dropped = false,
                                    heartbeat_recieved = true,
                                    mission_completed = false;
    ros::Timer                      timer_heartbeat_uav,
                                    timer_heartbeat_gcs;
    std_msgs::Int32                 gcs_heartbeat,
                                    uav_heartbeat;
    
};

}
#endif /* VEHICLECONTROL_H */
