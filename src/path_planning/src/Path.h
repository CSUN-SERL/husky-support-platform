/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Path.h
 * Author: serl
 *
 * Created on March 4, 2017, 4:37 PM
 */

#ifndef PATH_H
#define PATH_H
#include <vector>

class Obstacle;

class Path
{
public:
    struct Point
    {
        double x;
        double y;
    };
    struct Plane
    {
        double min_x;
        double min_y;
        double max_x;
        double max_y;
    };
    Path();
    Path(double width_of_vehicle);
    virtual ~Path();
    
    //Calculates Distance between two points
    static double CalcDistBetweenPoints(Point a, Point b);
    
    /*Calculates distance between curLocation and intermediateGoal and
     * the distance between intermediateGoal and endGoal
     * then averages the two values
     */
    static double AverageDistance(Point start, Point end_goal, Point inter_goal);
    
    //returns reduced obstacle list
    //If object doesnt have a marker within the min - max x/y values it can't be in the way
    //so we eliminate it from the list of obstacles to check.
    std::vector <Obstacle> ReduceObstacleList(std::vector<Obstacle> obstacle_list, Plane vehicle_plane);
    
    /*Determines if an object_marker exists in the plane defined by:
     * vehicle_size, start, end
     * 
     */
    Obstacle PointInPlane(std::vector<Obstacle> obstacle_list, Point start, Point goal);
    
    
    void SetVehicleDimension(double size);
    
    
private:
    double vehicle_dimension; //vehicle will be defined as a square for now
    
    //Calculates slope given two points
    double CalcSlope(Point a, Point b);

};

#endif /* PATH_H */

