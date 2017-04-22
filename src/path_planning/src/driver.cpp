/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   driver.cpp
 * Author: serl
 *
 * Created on March 5, 2017, 10:03 PM
 */

#include <cstdlib>
#include "PathPlanning.h"
#include "Obstacle.h"
#include <stdio.h>
#include "Path.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
 
#include <limits> // for numeric_limits
 
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
/*
using namespace std;


int main(int argc, char** argv) {
    Path::Point start;
    Path::Point goal;
    Path::Point midpoint;
    midpoint.x = 3.0;
    midpoint.y = 3.0;
    
    Obstacle::Marker marker1;
    Obstacle::Marker marker2;
    Obstacle::Marker marker3;
    Obstacle::Marker marker4;

    marker1.x = 2.0; marker1.y = 1.0;
    marker2.x = 4.0; marker2.y = 1.0;
    marker3.x = 2.0; marker3.y = 4.0;
    marker4.x = 4.0; marker4.y = 4.0;
    
    std::vector<Obstacle::Marker> marker_list;
    marker_list.push_back(marker1);
    marker_list.push_back(marker2);
    marker_list.push_back(marker3);
    marker_list.push_back(marker4);
    
    start.x = 0.0;
    start.y = 0.0;
    goal.x = 6.0;
    goal.y = 5.0;
    Obstacle obstacle1 = Obstacle(midpoint, marker_list);
    vector<Obstacle> obstacle_list;
    obstacle_list.push_back(obstacle1);
    
    //bool equality = (start.y == goal.y);

    //printf(equality ? "true" : "false");
        
    PathPlanning PathGen(start,goal,obstacle_list);
    //PathGen.GenerateMinPath();
    
    PathPlanning::Waypoints list = PathGen.GenerateMinPath();
    
    printf("distance is equal to %f, number of points is equal to %d \n", list.total_distance, list.number_of_points);
    for (std::vector<Path::Point>::const_iterator i = list.vector.begin();
            i != list.vector.end(); ++i){
        printf("%f , %f \n", i->x, i->y);
    }
    /*
    Graph graph = Graph(6);
    graph.addEdge(0,2,2.0,midpoint);
    graph.addEdge(0,3,3.6055,midpoint);
    graph.addEdge(0,4,4.0,midpoint);
    graph.addEdge(0,5,5.5677,midpoint);
    graph.addEdge(1,3,6.0,midpoint);
    graph.addEdge(1,4,5.916,midpoint);
    graph.addEdge(1,5,5.5677,midpoint);
    graph.addEdge(2,0,9.0,midpoint);
    graph.addEdge(2,1,10.0,midpoint);
    graph.addEdge(2,3,11.,midpoint);
    graph.addEdge(2,5,2.,midpoint);
    graph.addEdge(3,1,15.,midpoint);
    graph.addEdge(3,2,11.,midpoint);
    graph.addEdge(3,4,6.,midpoint);
    graph.addEdge(4,3,6.,midpoint);
    graph.addEdge(4,5,9.,midpoint);
    graph.addEdge(5,0,14.,midpoint);
    graph.addEdge(5,2,2.,midpoint);
    graph.addEdge(5,4,9.,midpoint);
    
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    graph.DijkstraComputePaths(0,  min_distance, previous);
    //std::cout << "Distance from 0 to 4: " << min_distance[4] << std::endl;
    std::list<vertex_t> path = graph.DijkstraGetShortestPathTo(1, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;
    
}
*/

#include <cstdlib>
#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include <std_msgs/String.h>
#include <lcar_msgs/WorldMap.h>
#include "ServiceCall.h"

using namespace std;

void ServiceCallback(const std_msgs::Empty notify)
{
    ROS_INFO("updating vector");
    ServiceCall service = ServiceCall();
    service.call();
}
void MocapCallback(const std_msgs::String str)
{
    std::vector<Obstacle> obstacle_list;
    ROS_INFO("%s\n", str.data.c_str());
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "world_map_client");
    
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<lcar_msgs::WorldMap>("world_map");
    
    lcar_msgs::WorldMap srv;
    if(client.call(srv))
    {
        ROS_INFO("point x: %f point y: %f point z: %f", srv.response.world_map[3], srv.response.world_map[4], srv.response.world_map[5]);
    }
    
    //ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    
    ros::Subscriber sub = n.subscribe("world_map_updated", 1000, ServiceCallback);
    
    ros::Subscriber mocap_sub = n.subscribe("mocap_markers", 1000, MocapCallback);
    
    ros::AsyncSpinner spinner(4);
    spinner.start();
    ros::waitForShutdown();
}
