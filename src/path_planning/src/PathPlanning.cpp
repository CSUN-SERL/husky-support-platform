
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
#include <iterator>
#include <Graph.h>

using namespace std;
double vehicle_width = 1.5;
std::vector<Path::Point> nodes;
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
    
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;    
    graph.DijkstraComputePaths(0,  min_distance, previous);
    
    std::list<vertex_t> path = graph.DijkstraGetShortestPathTo(1, previous);
    
    //total distance to destination. distance = 0 if not reachable
    points.total_distance = min_distance[1];
    
    points.number_of_points = path.size();
    //retrieve waypoints from shortest path
    for(std::list<vertex_t>::const_iterator iterator = path.begin(), end = path.end(); iterator != end; ++iterator){
        points.vector.push_back(nodes.at(*iterator));
    }
    
    return points;
}

Graph PathPlanning::GenerateGraph()
{
    int number_of_nodes = 2; //by default we have start and finish nodes
    //Calculate rest of nodes by totaling number of markers
    Path graph_path = Path(vehicle_width);
    nodes.push_back(vehicle_location);
    nodes.push_back(goal);
    for(std::vector<Obstacle>::iterator it = obstacle_list.begin(); it < obstacle_list.end(); it++){
        it->InitializeFreeSpaces(vehicle_width);
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
   
   for(int i = 0; i < nodes.size()-1; i++){
        for(int j = i+1; j < nodes.size(); j++){
            if(graph_path.EdgeExists(obstacle_list, nodes.at(i), nodes.at(j))){
                if(Path::CalcDistBetweenPoints(nodes.at(i),nodes.at(j)) != 0){
                    graph.addEdge(i,j,Path::CalcDistBetweenPoints(nodes.at(i),nodes.at(j)), nodes.at(j));
                    graph.addEdge(j,i,Path::CalcDistBetweenPoints(nodes.at(i),nodes.at(j)), nodes.at(i));
                }
            }
        }
   }

   return graph;
}

bool PathPlanning::PointsAreEqual(const Path::Point& a, const Path::Point& b)
{
    if((a.x == b.x) && (a.y == b.y))
            return true;
    return false;
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