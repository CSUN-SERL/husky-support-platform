
/* 
 * File:   path_planning.cpp
 * Author: serl - Anthony Pichardo
 * 
 * Created on March 2, 2017, 1:23 PM
 */
#include "Obstacle.h"
#include "PathPlanning.h"

using namespace std;
PathPlanning::PathPlanning() {
}
/*Constructor with fields 
 */
PathPlanning::PathPlanning(const Point &vehicle_location, const Point &goal,
        vector<Obstacle> obstacle_list)
{
    PathPlanning::SetVehicleLocation(vehicle_location);
    PathPlanning::SetGoal(goal);
    PathPlanning::SetObstacleList(obstacle_list);
}

PathPlanning::~PathPlanning()
{
}
/*This should be a recursive function that finds the shortest path between the start
 *and goal. Calls itself whenever an obstacle appears, with new goal being 
 * an edge of the closest obstacle in the way. Add way points to list as we
 * determine the shortest path. will be added from the end to the beginning.
 * i.e: Goal -> 2nd to last -> 3rd to last ... -> start.
 * Result should be the minimum path from start to goal.
 * 
 */
vector< vector<double> >* PathPlanning::GenerateMinPath(const Point &start,
        const Point &destination)
{
    
}
//Returns closest obstacle obstructing path to goal
Obstacle PathPlanning::IsPathClear(const Point &start, const Point &destination)
{
    return Obstacle();
}
//adds way point to list of final way points #this may be unnecessary
void PathPlanning::AddNewWayPoint(std::vector<double> way_point)
{
    waypoints.push_back(way_point);
}
//returns way points 

//Sort obstacle list such that obstacles closest to curr_location are in front.
//returns list sorted while removing irrelevant obstacles
std::vector<Obstacle>* PathPlanning::SortObstacleList(const Point &start, const Point &destination,
        vector<Obstacle> obstacle_list)
{
    
}

void PathPlanning::SetVehicleLocation(const Point &vehicle_location)
{
    this->vehicle_location = vehicle_location;
}
    
PathPlanning::Point PathPlanning::GetVehicleLocation()
{
    return this->vehicle_location;
}

void PathPlanning::SetGoal(const Point &goal)
{
    this->goal = goal;
}

PathPlanning::Point PathPlanning::GetGoal()
{
    return this->goal;
}

void PathPlanning::SetObstacleList(std::vector<Obstacle> obstacles){
    this->obstacle_list = obstacles;
}

std::vector<Obstacle>* PathPlanning::GetObstacleList()
{
    return &this->obstacle_list;
}
    std::vector< std::vector<double> >* PathPlanning::GetWayPoints()
{
    return &waypoints;
}