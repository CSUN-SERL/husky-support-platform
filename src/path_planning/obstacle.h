
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
    Obstacle();
    
    Obstacle( const std::vector< std::vector<double> > &marker_locations );
    
    virtual ~Obstacle();
    
    void SetMarkerLocations(const std::vector< std::vector<double> > &marker_locations);
    
    std::vector<std::vector<double> >* GetMarkerLocations();
    
private:
    std::vector<std::vector<double> > marker_locations;

};

#endif /* OBSTACLE_H */

