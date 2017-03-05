
/* 
 * File:   obstacle.h
 * Author: serl
 *
 * Created on March 2, 2017, 1:47 PM
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <vector>

class Obstacle 
{
public:
    struct Point
    {
        double x;
        double y;
    };
    Obstacle();
    
    Obstacle( const std::vector< Point > &marker_locations );
    
    virtual ~Obstacle();
    
    void SetMarkerLocations(const std::vector< Point > &marker_locations);
    
    std::vector< Point >* GetMarkerLocations();
    
private:
    std::vector< Point > marker_locations;

};

#endif /* OBSTACLE_H */

