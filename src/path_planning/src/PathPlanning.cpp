
/* 
 * File:   path_planning.cpp
 * Author: serl - Anthony Pichardo
 * 
 * Created on March 2, 2017, 1:23 PM
 */
#include "Obstacle.h"
#include "PathPlanning.h"
#include "Path.h"
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <Graph.h>

using namespace std;
double vehicle_width = 2.5;
Path::Point PathPlanning::goal;
Path::Point PathPlanning::vehicle_location;

PathPlanning::PathPlanning() {
}
/*Constructor with fields 
 */
PathPlanning::PathPlanning(const Path::Point &vehicle_location, const Path::Point &goal,
        vector<Obstacle> obstacle_list)
{
    PathPlanning::SetVehicleLocation(vehicle_location);
    PathPlanning::SetGoal(goal);
    PathPlanning::SetObstacleList(obstacle_list);
}

PathPlanning::~PathPlanning()
{
}

PathPlanning::Waypoints PathPlanning::GenerateMinPath(){
    PathPlanning::Waypoints points;
    Graph graph = PathPlanning::GenerateGraph();
    points = GenerateMinPath(vehicle_location,goal);
    return points;
}

Graph PathPlanning::GenerateGraph()
{
    int number_of_nodes = 2; //by default we have start and finish nodes
    //Calculate rest of nodes by totaling number of markers
    std::vector<Path::Point> nodes;
    nodes.push_back(vehicle_location);
    nodes.push_back(goal);
    for(std::vector<Obstacle>::iterator it = obstacle_list.begin(); it < obstacle_list.end(); it++){
        for(std::vector<Obstacle::Marker>::iterator marker = it->GetMarkerLocations()->begin();
                marker < it->GetMarkerLocations()->end(); marker++){
            number_of_nodes += 4;
            nodes.push_back(marker->FS_top);
            nodes.push_back(marker->FS_bottom);
            nodes.push_back(marker->FS_left);
            nodes.push_back(marker->FS_right);
        }
    }
    //create graph
   Graph graph = Graph(number_of_nodes);
   
   //iterate through each node and check for path to other nodes if path exists;
    //add edges to graph
}
/*This should be a recursive function that finds the shortest path between the start
 *and goal. Calls itself whenever an obstacle appears, with new goal being 
 * an edge of the furthest obstacle in the way. Add way points to list as we
 * determine the shortest path. will be added from the end to the beginning.
 * i.e: Goal -> 2nd to last -> 3rd to last ... -> start.
 * Result should be the minimum path from start to goal.
 * 
 */
PathPlanning::Waypoints PathPlanning::GenerateMinPath(Path::Point start,
        Path::Point destination)
{
    Path::Point cur_location = start;
    Path current_path = Path(2.5);
    
    std::vector<Obstacle> sorted_list(obstacle_list);
    sorted_list = SortObstacleList(start, sorted_list);
    
    PathPlanning::Waypoints points = {{},0.0,0};

    /*while(PointsAreEqual(cur_location, destination) == false)
    {
        //returns obstacle closest to goal
        Obstacle object_in_path = current_path.PointInPlane(sorted_list, cur_location, destination);
        
        if(object_in_path.IsEmpty())
        {
            cur_location = destination;
            AddNewWayPoint(points, destination);
        }
        else
        {
            Path::Point intermediate_goal = ChooseGreedyPathAround(cur_location, object_in_path, destination);
            MergeWaypoints(points, GenerateMinPath(cur_location, intermediate_goal));
            cur_location = intermediate_goal;
        }
    }*/
    //delete &current_path;
    return points;
}
// Merge two lists of waypoints where a becomes a U b
void PathPlanning::MergeWaypoints(Waypoints a, Waypoints b)
{
    a.vector.insert(a.vector.end(), b.vector.begin(), b.vector.end());
    a.total_distance += b.total_distance;
    a.number_of_points += b.number_of_points;
}

bool PathPlanning::PointsAreEqual(const Path::Point& a, const Path::Point& b)
{
    if((a.x == b.x) && (a.y == b.y))
            return true;
    return false;
}

//Makes the greedy choice to navigate around obstacle. Picks Marker_FS with preference to goal.
Path::Point PathPlanning::ChooseGreedyPathAround(Path::Point cur_location, Obstacle object, Path::Point destination)
{
    object.InitializeFreeSpaces(vehicle_width);
    Obstacle::Marker navigate_around = object.GetCorner();
    //Find free space with the closest average distance from start and goal.
    double min_distance = Path::AverageDistance(cur_location, destination, navigate_around.FS_bottom);
    Path::Point greedy_point = navigate_around.FS_bottom;
    
    if(min_distance > Path::AverageDistance(cur_location, destination, navigate_around.FS_top))
        greedy_point = navigate_around.FS_top;
    
    if(min_distance > Path::AverageDistance(cur_location, destination, navigate_around.FS_left))
        greedy_point = navigate_around.FS_left;
    
    if(min_distance > Path::AverageDistance(cur_location, destination, navigate_around.FS_right))
        greedy_point = navigate_around.FS_right;
    
    return greedy_point;
    
}

//adds way point to list  way points #this may be unnecessary
void PathPlanning::AddNewWayPoint(Waypoints &list_of_points, Path::Point way_point)
{
    if(list_of_points.number_of_points != 0)
    {
        list_of_points.total_distance += Path::CalcDistBetweenPoints(list_of_points.vector.back(), way_point);
        list_of_points.number_of_points++;
    }
    else
    {
        list_of_points.total_distance = Path::CalcDistBetweenPoints(vehicle_location, way_point);
        list_of_points.number_of_points++;
    }
    list_of_points.vector.push_back(way_point);
}
//Compartors to facilitate sorting.
bool PathPlanning::CompareX (Obstacle a,  Obstacle b)
{
    return ( fabs(a.GetMidpoint().x - vehicle_location.x) < fabs(b.GetMidpoint().x - vehicle_location.x) );
}

bool PathPlanning::CompareY (Obstacle a,  Obstacle b)
{
    return (fabs(a.GetMidpoint().y - vehicle_location.y) < fabs(b.GetMidpoint().y - vehicle_location.y) );
}

//Sort obstacle list such that obstacles closest to curr_location are in front.
//returns list sorted while removing irrelevant obstacles
std::vector<Obstacle> PathPlanning::SortObstacleList(const Path::Point &start,
        vector<Obstacle> obstacle_list)
{
    std::vector<Obstacle> sorted_list(obstacle_list);
    std::stable_sort(sorted_list.begin(), sorted_list.end(), CompareX);
    std::stable_sort(sorted_list.begin(), sorted_list.end(), CompareY);
    
    return sorted_list;
    
}

void PathPlanning::SetVehicleLocation(const Path::Point &vehicle_location)
{
    this->vehicle_location = vehicle_location;
}
    
Path::Point PathPlanning::GetVehicleLocation()
{
    return this->vehicle_location;
}

void PathPlanning::SetGoal(const Path::Point &goal)
{
    this->goal = goal;
}

Path::Point PathPlanning::GetGoal()
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

std::vector< Path::Point >* PathPlanning::GetWayPoints()
{
    return &waypoints;
}