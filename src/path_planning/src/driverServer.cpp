/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include "ros/ros.h"
#include <lcar_msgs/WorldMap.h>

bool WorldMapRequested(lcar_msgs::WorldMap::Request& req, lcar_msgs::WorldMap::Response& res)
{
    std::vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(15);
    res.world_map = vector;
    return true;
}

using namespace std;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "world_map_server");
    ros::NodeHandle n;
    
    ros::ServiceServer service = n.advertiseService("world_map", &WorldMapRequested);
    ROS_INFO("Ready to broadcast");
    ros::spin();
}