
/* 
 * File:   path_planning.h
 * Author: serl - Anthony Pichardo
 *
 * Created on March 2, 2017, 1:23 PM
 */

#include "Obstacle.h"
#include "Path.h"
#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H
#include <vector>
#include "Graph.h"

class PathPlanning{
public:
    static Path::Point goal,
          vehicle_location;
    struct Waypoints
    {
        std::vector<Path::Point> vector;
        double total_distance;
        int number_of_points;
    };
    PathPlanning();
    
    PathPlanning(const Path::Point & start, const Path::Point & goal,
        std::vector<Obstacle> obstacle_list);
    
    virtual ~PathPlanning();
    
    bool PointsAreEqual(const Path::Point& a, const Path::Point& b);
    
    Waypoints GenerateMinPath();
    
    void MergeWaypoints(Waypoints a, Waypoints b);
    
    Path::Point ChooseGreedyPathAround(Path::Point cur_location, Obstacle object,
        Path::Point destination);
    
    void SetVehicleLocation(const Path::Point &vehicle_location);
    
    Path::Point GetVehicleLocation();
    
    void SetGoal(const Path::Point & goal);
    
    Path::Point GetGoal();
    
    void SetObstacleList(std::vector<Obstacle> obstacles);
    
    std::vector<Obstacle>* GetObstacleList();
    

private:

    std::vector< Path::Point > waypoints;
    

    std::vector<Obstacle> obstacle_list;
    
    std::vector<Obstacle> SortObstacleList(const Path::Point & start,
        std::vector<Obstacle> obstacle_list);
    
    Graph GenerateGraph();
    
    Waypoints GenerateMinPath(Path::Point start,
        Path::Point destination);
    
    static bool CompareX (Obstacle a,  Obstacle b);
    static bool CompareY (Obstacle a, Obstacle b);
    
    void AddNewWayPoint(Waypoints &list_of_points, Path::Point way_point);
    
    std::vector< Path::Point >* GetWayPoints();

};

#endif /* PATH_PLANNING_H */

