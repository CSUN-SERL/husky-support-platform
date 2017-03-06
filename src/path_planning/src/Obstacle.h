
/* 
 * File:   obstacle.h
 * Author: serl
 *
 * Created on March 2, 2017, 1:47 PM
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Path.h"
#include <vector>


class Obstacle 
{
public:
    struct Marker
    {
        double x;
        double y;
        //FS = Free Space
        Path::Point FS_top;
        Path::Point FS_bottom;
        Path::Point FS_left;
        Path::Point FS_right;
    };

    Obstacle();
    
    Obstacle(Path::Point midpoint, const std::vector< Marker > &marker_locations );
    
    virtual ~Obstacle();
    
    void SetMarkerLocations(const std::vector< Marker > &marker_locations);
    
    void SetMidpoint(Path::Point midpoint);
    
    void SetCorner(Marker corner);
    
    bool IsEmpty();
    
    void InitializeFreeSpaces(double vehicle_dimension);
    
    void CheckInvalidMarker(Path::Point point);
    
    Path::Point GetMidpoint();
    
    Marker GetCorner();
    
    std::vector< Marker >* GetMarkerLocations();
    
private:
    std::vector< Marker > marker_locations;
    Path::Point midpoint;
    Marker corner_in_path;

};

#endif /* OBSTACLE_H */

