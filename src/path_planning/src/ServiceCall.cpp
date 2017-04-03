/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServiceCall.cpp
 * Author: serl
 * 
 * Created on April 2, 2017, 9:14 PM
 */

#include "ServiceCall.h"
#include <lcar_msgs/WorldMap.h>
#include "ros/ros.h"

ServiceCall::ServiceCall() {
    //os::init(argc, argv, "world_map_client");
    
    ros::NodeHandle nh;
    this->client = nh.serviceClient<lcar_msgs::WorldMap>("world_map");
    
}

ServiceCall::ServiceCall(const ServiceCall& orig) {
}

ServiceCall::~ServiceCall() {
}
std::vector<int> ServiceCall::call()
{
    if(client.call(srv))
    {
        ROS_INFO("point x: %d point y: %d point z: %d", srv.response.world_map[0], srv.response.world_map[1], srv.response.world_map[2]);
    }
    return srv.response.world_map;
}

