
/* 
 * File:   path_planning.cpp
 * Author: serl - Anthony Pichardo
 * 
 * Created on March 2, 2017, 1:23 PM
 */
#include "obstacle.h"
#include "path_planning.h"

path_planning::path_planning() {
}
/*Constructor with fields and returns path for vehicle.
 */
path_planning::path_planning(vector<double> vehicle_location, vector<double> goal,
        vector<obstacle> obstacle_list)
{
    path_planning::set_vehicle_location(vehicle_location);
    path_planning::set_goal(goal);
    path_planning::set_obstacle_list(obstacle_list);
    
    vector< vector<double> > path = get_waypoints();
    
    return path;
}

path_planning::~path_planning()
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
vector< vector<double> > path_planning::generate_min_path(vector<double> start,
        vector<double> destination)
{
    
}
//Returns true if there is no obstacle obstructing the path from start to destin.
path_planning::is_path_clear(vector<double> start, vector<double> destination)
{
    return true;
}
//adds way point to list of final way points #this may be unnecessary
path_planning::add_new_waypoint(vector<double> destination)
{
    waypoints.insert(destination);
}
//returns way points 
path_planning::get_waypoints()
{
    return waypoints;
}
//Sort obstacle list such that obstacles closest to curr_location are in front.
//returns list sorted while removing irrelevant obstacles
path_planning::sort_obstacle_list(vector<double> start, vector<double> destination,
        vector<obstacle> obstacle_list)
{
    
}

path_planning::set_goal(vector<double> goal)
{
    this->goal = goal;
}

path_planning::set_obstacle_list(vector<obstacle> obstacles)
{
    this->obstacle_list = obstacles;
}

path_planning::set_vehicle_location(vector<double> vehicle_location)
{
    this->vehicle_location = vehicle_location;
}

path_planning::get_goal()
{
    return this->goal;
}

path_planning::get_obstacle_list()
{
    return this->obstacle_list;
}

path_planning::get_vehicle_location()
{
    return this->vehicle_location;
}
