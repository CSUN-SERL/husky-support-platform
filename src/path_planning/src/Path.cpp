/*
 * File:   path.cpp
 * Author: serl - Anthony Pichardo
 * 
 * Created on March 3, 2017, 1:23 PM
 */

#include "Path.h"
#include "Obstacle.h"
#include <math.h>

Path::Path()
{
    
}
Path::Path(int width_of_vehicle)
{
    Path::SetVehicleDimension(width_of_vehicle);
}
Path::~Path()
{
    
}

//Calculates Distance between two points
double Path::CalcDistBetweenPoints(Path::Point a, Path::Point b)
{
  int distancex = (b.x - a.x) * (b.x - a.x);
  int distancey = (b.y - a.y) * (b.y - a.y);

  double distance = sqrt (distancex - distancey);
  
  return distance;
}

/*Calculates distance between curLocation and intermediateGoal and
 * the distance between intermediateGoal and endGoal
 * then averages the two values
 */
double Path::AverageDistance(Path::Point start, Path::Point end_goal, Path::Point inter_goal)
{
    double distance_a = Path::CalcDistBetweenPoints(start, inter_goal);
    
    double distance_b = Path::CalcDistBetweenPoints(inter_goal, end_goal);
    
    double average = (distance_a + distance_b)/2;
    
    return average;
}

//Calculates slope given two points
double Path::CalcSlope(Path::Point a, Path::Point b)
{
    double slope = (b.y - a.y)/(b.x -a.x);
    
    return slope;
}

//returns reduced obstacle list with obstacle furthest from vehicle first.
//If object doesnt have a marker within the min - max x/y values it can't be in the way
//so we eliminate it from the list of obstacles to check.
std::vector <Obstacle> Path::ReduceObstacleList(std::vector<Obstacle> obstacle_list,
        Path::Plane vehicle_plane)
{
    //initialize new list of obstacles
    std::vector<Obstacle> reduced_list;
    
    //Iterate through markers in obstacle list checking for which values fall in plane
    for(Obstacle auto &obstacle : obstacle_list){
        for(Obstacle::Marker auto &marker : obstacle.GetMarkerLocations()){
            if(marker.x < vehicle_plane.min_x || marker.x > vehicle_plane.max_x ||
                    marker.y < vehicle_plane.min_y || marker.y > vehicle_plane.max_y)
            ; //Marker not in plane do nothing
            else //Marker does exist within plane
            {
                //if marker exists within range add to obstacle list to check
                reduced_list.push_back(obstacle);
                //move to next object
                break;
            }
            
        }
    }
}
/*Determines if an object_marker exists in the plane defined by:
 * vehicle_size, start, end
 * Returns object closest to vehicle
 */
Obstacle Path::PointInPlane(std::vector<Obstacle> obstacle_list, Path::Point start, Path::Point goal)
{
    Obstacle closest_obstacle;
    
    Obstacle furthest_obstacle;
    
    double minX = start.x < goal.x ? start.x - (vehicle_dimension)/2: goal.x -(vehicle_dimension)/2;
    double maxX = start.x > goal.x ? start.x + (vehicle_dimension)/2: goal.x +(vehicle_dimension)/2;
    double minY = start.y;
    double maxY = goal.y;
    
    Path::Point top_left = {goal.x - (vehicle_dimension)/2, goal.y};
    Path::Point top_right = {goal.x + (vehicle_dimension)/2, goal.y};
    Path::Point bottom_left = {start.x + (vehicle_dimension)/2, start.y};
    Path::Point bottom_right = {start.x + (vehicle_dimension)/2, start.y};
    
    Point vertices[] = {top_left,top_right,bottom_left,bottom_right};
    
    Path::Plane vehicle_plane {minX, minY, maxX, maxY};
    
    //List returned is in order from furthest to closest
    std::vector<Obstacle> reduced_list = Path::ReduceObstacleList(obstacle_list, vehicle_plane);
    for(Obstacle auto &obstacle : reduced_list){
        for(Obstacle::Marker auto &marker : obstacle.GetMarkerLocations()){
            int array_length = sizeof(vertices) / sizeof(vertices);
            bool inside = false;
            for (int i = 0, j = array_length-1; i < array_length; j = i++)
            {
                if ( ((vertices[i].y>marker.y) != (vertices[j].y>marker.y)) &&
                  (marker.x < (vertices[j].x-vertices[i].x) * (marker.y-vertices[i].y) /
                    (vertices[j].y-vertices[i].y) + vertices[i].x) )
                {
                    inside = !inside;
                }
            }
            if(inside){
                /*//whenever obstacle is found reset closest_obstacle because list is in reverse order
                //closest_obstacle = obstacle;               
                //move on to next obstacle
                break;
                 */
                //return furthest obstacle from start as opposed to closest.
                obstacle.SetCorner(marker);
                furthest_obstacle = obstacle;
                return furthest_obstacle;
            }
        }
    }
    
    
    return closest_obstacle;
}

void Path::SetVehicleDimension(int size)
{
    this->vehicle_dimension = size;
}

