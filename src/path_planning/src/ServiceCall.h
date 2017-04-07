/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServiceCall.h
 * Author: serl
 *
 * Created on April 2, 2017, 9:14 PM
 */

#ifndef SERVICECALL_H
#define SERVICECALL_H
#include <lcar_msgs/WorldMap.h>
#include "ros/ros.h"

class ServiceCall {
public:
    ServiceCall();
    lcar_msgs::WorldMap srv;
    ServiceCall(const ServiceCall& orig);
    std::vector<double> call();
    virtual ~ServiceCall();
private:

    ros::ServiceClient client;

};

#endif /* SERVICECALL_H */

