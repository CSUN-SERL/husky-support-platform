
/* 
 * File:   obstacle.cpp
 * Author: serl
 * 
 * Created on March 2, 2017, 1:47 PM
 */

#include "obstacle.h"


obstacle::obstacle() {
}

obstacle::obstacle(vector< vector<double> > marker_locations) {
    set_marker_locations(marker_locations);
}

obstacle::get_marker_locations()
{
    return marker_locations;
}

obstacle::set_marker_locations(vector<vector<double> > marker_locations)
{
    this->marker_locations = marker_locations;
}

obstacle::~obstacle() {
}

