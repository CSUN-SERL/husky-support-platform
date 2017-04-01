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
Path::Path(double width_of_vehicle)
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

  double distance = sqrt(distancex - distancey);
  
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
    
    for(std::vector<Obstacle>::iterator it = obstacle_list.begin(); it < obstacle_list.end(); it++){
        for(std::vector<Obstacle::Marker>::iterator marker = it->GetMarkerLocations()->begin();
                marker < it->GetMarkerLocations()->end(); marker++){
            if(marker->x < vehicle_plane.min_x || marker->x > vehicle_plane.max_x ||
                    marker->y < vehicle_plane.min_y || marker->y > vehicle_plane.max_y)
            ; //Marker not in plane do nothing
            else //Marker does exist within plane
            {
                //if marker exists within range add to obstacle list to check
                reduced_list.push_back(*it);
                //move to next object
                break;
            }
            
        }
    }
    return reduced_list;
}
//returns true if planes do not intersect
bool Path::NoPlaneIntersection(Path::Plane obstacle_plane, Path::Plane vehicle_plane)
{
    if(obstacle_plane.min_x < vehicle_plane.max_x && obstacle_plane.max_x > vehicle_plane.min_x
            && obstacle_plane.min_y < vehicle_plane.max_y && obstacle_plane.max_y > vehicle_plane.min_y )
        return true;
}

/*Determines if an edge exists between two nodes.
 * edge exists if there is no obstacle between two nodes
 */
bool Path::EdgeExists(std::vector<Obstacle> obstacle_list, Path::Point start, Path::Point goal)
{
    if(obstacle_list.empty())
    {
        return true;
    }
    
    
    double minX = start.x < goal.x ? start.x - (vehicle_dimension)/2: goal.x -(vehicle_dimension)/2;
    double maxX = start.x > goal.x ? start.x + (vehicle_dimension)/2: goal.x +(vehicle_dimension)/2;
    double minY = start.y < goal.y ? start.y - (vehicle_dimension)/2: goal.y -(vehicle_dimension)/2;;
    double maxY = goal.y > goal.y ? start.y + (vehicle_dimension)/2: goal.y +(vehicle_dimension)/2;;
    
    Path::Point top_left = {minX, maxY};
    Path::Point top_right = {maxX, maxY};
    Path::Point bottom_left = {minX, minY};
    Path::Point bottom_right = {maxX, minY};
    
    Point vertices[] = {top_left,top_right,bottom_left,bottom_right};
    
    Path::Plane vehicle_plane {minX, minY, maxX, maxY};
    
    //List returned is in order from furthest to closest
    std::vector<Obstacle> reduced_list = Path::ReduceObstacleList(obstacle_list, vehicle_plane);

    
    for(std::vector<Obstacle>::iterator it = reduced_list.begin(); it < reduced_list.end(); it++){
        double ob_minx = it->GetMarkerLocations()->at(0).x;
        double ob_maxx = it->GetMarkerLocations()->at(0).x;
        double ob_miny = it->GetMarkerLocations()->at(0).y;
        double ob_maxy = it->GetMarkerLocations()->at(0).y;
        

        for(std::vector<Obstacle::Marker>::iterator marker = it->GetMarkerLocations()->begin();
                marker < it->GetMarkerLocations()->end(); marker++){
            if(marker->x < ob_minx)
                ob_minx = marker->x;
            if(marker->x > ob_maxx)
               ob_maxx = marker->x;
            if(marker->y < ob_miny)
                ob_miny = marker->y;
            if(marker->y > ob_maxy)
                ob_maxy = marker->y;
        }
        Path::Plane obstacle_plane {ob_minx, ob_miny, ob_maxx, ob_maxy};
        if(NoPlaneIntersection(obstacle_plane, vehicle_plane)){
            return true;
        }
    }
    
    
    return false;
}


/*Determines if an object_marker exists in the plane defined by:
 * vehicle_size, start, end
 * Returns object closest to vehicle

Obstacle Path::PointInPlane(std::vector<Obstacle> obstacle_list, Path::Point start, Path::Point goal)
{
    if(obstacle_list.empty())
    {
        std::vector<Obstacle::Marker> empty;
        return Obstacle({0,0}, empty);
    }
    Obstacle closest_obstacle;
    
    Obstacle furthest_obstacle;
    
    double minX = start.x < goal.x ? start.x - (vehicle_dimension)/2: goal.x -(vehicle_dimension)/2;
    double maxX = start.x > goal.x ? start.x + (vehicle_dimension)/2: goal.x +(vehicle_dimension)/2;
    double minY = start.y;
    double maxY = goal.y;
    
    Path::Point top_left = {goal.x - (vehicle_dimension)/2, goal.y + (vehicle_dimension)/2};
    Path::Point top_right = {goal.x + (vehicle_dimension)/2, goal.y + (vehicle_dimension)/2};
    Path::Point bottom_left = {start.x - (vehicle_dimension)/2, start.y - (vehicle_dimension)/2};
    Path::Point bottom_right = {start.x + (vehicle_dimension)/2, start.y - (vehicle_dimension)/2};
    
    Point vertices[] = {top_left,top_right,bottom_left,bottom_right};
    
    Path::Plane vehicle_plane {minX, minY, maxX, maxY};
    
    //List returned is in order from furthest to closest
    std::vector<Obstacle> reduced_list = Path::ReduceObstacleList(obstacle_list, vehicle_plane);

    
    for(std::vector<Obstacle>::iterator it = reduced_list.begin(); it < reduced_list.end(); it++){
        for(std::vector<Obstacle::Marker>::iterator marker = it->GetMarkerLocations()->begin();
                marker < it->GetMarkerLocations()->end(); marker++){
            int array_length = sizeof(vertices) / sizeof(vertices[0]);
            bool inside = false;
            for (int i = 0, j = array_length-1; i < array_length; j = i++)
            {
                if ( ((vertices[i].y > marker->y) != (vertices[j].y > marker->y)) &&
                  (marker->x < (vertices[j].x-vertices[i].x) * (marker->y-vertices[i].y) /
                    (vertices[j].y-vertices[i].y) + vertices[i].x) )
                {
                    inside = !inside;
                }
            }
            if(inside){
                //whenever obstacle is found reset closest_obstacle because list is in reverse order
                //closest_obstacle = obstacle;               
                //move on to next obstacle
                //break;
                 
                //return furthest obstacle from start as opposed to closest.
                it->SetCorner(*marker);
                furthest_obstacle = *it;
                return furthest_obstacle;
            }
        }
    }
    
    return closest_obstacle;
}
*/
void Path::SetVehicleDimension(double size)
{
    this->vehicle_dimension = size;
}

