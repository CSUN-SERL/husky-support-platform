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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Path::Point start;
    Path::Point goal;
    Path::Point midpoint;
    midpoint.x = 2.0;
    midpoint.y = 2.0;
    
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
    
    printf("%f %d", list.total_distance, list.number_of_points);
    return 0;
}

