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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*Path::Point start;
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
    return 0;*/
    
    Graph graph = Graph(6);
    graph.addEdge(0,1,7);
    graph.addEdge(0,2,9);
    graph.addEdge(0,5,14);
    graph.addEdge(1,0,7);
    graph.addEdge(1,2,10);
    graph.addEdge(1,3,15);
    graph.addEdge(2,0,9);
    graph.addEdge(2,1,10);
    graph.addEdge(2,3,11);
    graph.addEdge(2,5,2);
    graph.addEdge(3,1,15);
    graph.addEdge(3,2,11);
    graph.addEdge(3,4,6);
    graph.addEdge(4,3,6);
    graph.addEdge(4,5,9);
    graph.addEdge(5,0,14);
    graph.addEdge(5,2,2);
    graph.addEdge(5,4,9);
    
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    graph.DijkstraComputePaths(0,  min_distance, previous);
    std::cout << "Distance from 0 to 4: " << min_distance[4] << std::endl;
    std::list<vertex_t> path = graph.DijkstraGetShortestPathTo(4, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;
    
}

