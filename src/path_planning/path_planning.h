
/* 
 * File:   path_planning.h
 * Author: serl - Anthony Pichardo
 *
 * Created on March 2, 2017, 1:23 PM
 */

#include "obstacle.h"

#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H
#include <vector>

class PathPlanning{
public:
    struct Point
    {
        double x;
        double y;
    };
    PathPlanning();
    
    PathPlanning(const Point & start, const Point & goal,
        std::vector<Obstacle> obstacle_list);
    
    virtual ~PathPlanning();
    
    std::vector< std::vector<double> > waypoints;
    
    void SetVehicleLocation(const Point &vehicle_location);
    
    Point GetVehicleLocation();
    
    void SetGoal(const Point & goal);
    
    Point GetGoal();
    
    void SetObstacleList(std::vector<Obstacle> obstacles);
    
    std::vector<Obstacle>* GetObstacleList();

private:

    
    Point goal,
          vehicle_location;
    std::vector<Obstacle> obstacle_list;
    
    std::vector< std::vector<double> >* GenerateMinPath(const Point & start,
        const Point & destination);
    
    std::vector<Obstacle>* SortObstacleList(const Point & start,
        const Point & destination,std::vector<Obstacle> obstacle_list);
    
    Obstacle IsPathClear(const Point & start, const Point & destination);
    
    void AddNewWayPoint(std::vector<double> way_point);
    
    std::vector< std::vector<double> >* GetWayPoints();

};

#endif /* PATH_PLANNING_H */

