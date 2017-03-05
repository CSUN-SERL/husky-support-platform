
/* 
 * File:   obstacle.cpp
 * Author: serl
 * 
 * Created on March 2, 2017, 1:47 PM
 */

#include "Obstacle.h"
#include <vector>

Obstacle::Obstacle() {
}

Obstacle::Obstacle( const std::vector< Point > &marker_locations )
{
    SetMarkerLocations(marker_locations);
}
Obstacle::~Obstacle() {
}

void Obstacle::SetMarkerLocations(const std::vector< Point > &marker_locations)
{
    this->marker_locations = marker_locations;
}

std::vector< Obstacle::Point >* Obstacle::GetMarkerLocations()
{
    return &this->marker_locations;
}



