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
    start.x = 0.0;
    start.y = 0.0;
    goal.x = 10.0;
    goal.y = 5.0;
    printf("hello world");
    vector<Obstacle> obstacle_list;
    
    
    PathPlanning PathGen(start,goal,obstacle_list);
    
    PathPlanning::Waypoints list = PathGen.GenerateMinPath();
    
    printf("%f", list.total_distance);
    return 0;
}

