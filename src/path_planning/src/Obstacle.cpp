
/* 
 * File:   obstacle.cpp
 * Author: serl
 * 
 * Created on March 2, 2017, 1:47 PM
 */

#include "Obstacle.h"
#include "Path.h"
#include <vector>

Obstacle::Obstacle() {
}

Obstacle::Obstacle( Path::Point midpoint, const std::vector< Marker > &marker_locations )
{
    SetMidpoint(midpoint);
    SetMarkerLocations(marker_locations);
}
Obstacle::~Obstacle()
{
}

bool Obstacle::IsEmpty()
{
    return marker_locations.empty();
}

void Obstacle::InitializeFreeSpaces(double vehicle_dimension)
{
    for(std::vector<Obstacle::Marker>::iterator marker = this->GetMarkerLocations()->begin();
                marker < this->GetMarkerLocations()->end(); marker++)
    {
    //for(Obstacle::Marker auto &marker : this->marker_locations){
        marker->FS_bottom.y = marker->y - (vehicle_dimension/2 + (vehicle_dimension * .15));
        marker->FS_bottom.x = marker->x;
        CheckInvalidMarker(marker->FS_bottom);
        
        marker->FS_top.y = marker->y + (vehicle_dimension/2 + (vehicle_dimension * .15));
        marker->FS_top.x = marker->x;
        CheckInvalidMarker(marker->FS_top);
        
        marker->FS_right.y = marker->y - (vehicle_dimension/2 + (vehicle_dimension * .15));
        marker->FS_right.x = marker->x + (vehicle_dimension/2 + (vehicle_dimension * .15));
        CheckInvalidMarker(marker->FS_right);
        
        marker->FS_left.y = marker->y;
        marker->FS_left.x = marker->x - (vehicle_dimension/2 + (vehicle_dimension * .15));
        CheckInvalidMarker(marker->FS_left);

    }
}

void Obstacle::CheckInvalidMarker(Path::Point &point)
{
    /*int i, j;
    bool exists;
    for (i = 0, j = this->marker_locations.size()-1; i < this->marker_locations.size(); j = i++) {
        if ( ((marker_locations.at(i).y > point.y) != (marker_locations.at(j).y > point.y)) &&
        (point.x < (marker_locations.at(j).x -marker_locations.at(i).x) * (point.y - marker_locations.at(i).y) /
                (marker_locations.at(j).y-marker_locations.at(i).y) + marker_locations.at(i).x) )
        {
            exists = !exists;
        }
    }
    //If point is invalid: meaning it is inside the object, set the position to the midpoint of object.
    if(exists){
        point.x = midpoint.x;
        point.y = midpoint.y;
    }*/

    double ob_minx = this->GetMarkerLocations()->at(0).x;
    double ob_maxx = this->GetMarkerLocations()->at(0).x;
    double ob_miny = this->GetMarkerLocations()->at(0).y;
    double ob_maxy = this->GetMarkerLocations()->at(0).y;


    for(std::vector<Obstacle::Marker>::iterator marker = this->GetMarkerLocations()->begin();
            marker < this->GetMarkerLocations()->end(); marker++){
        if(marker->x < ob_minx)
            ob_minx = marker->x;
        if(marker->x > ob_maxx)
           ob_maxx = marker->x;
        if(marker->y < ob_miny)
            ob_miny = marker->y;
        if(marker->y > ob_maxy)
            ob_maxy = marker->y;
    }
    Path::Plane obstacle_plane {ob_minx, ob_miny, ob_maxx, ob_maxy};
    
    if(point.x < obstacle_plane.min_x || point.x > obstacle_plane.max_x ||
            point.y < obstacle_plane.min_y || point.y > obstacle_plane.max_y){
        return;
    }
    
    point.x = midpoint.x;
    point.y = midpoint.y;
}

void Obstacle::SetMidpoint(Path::Point midpoint)
{
    this->midpoint = midpoint;
}

void Obstacle::SetCorner(Marker corner)
{
    this->corner_in_path = corner;
}

void Obstacle::SetMarkerLocations(const std::vector< Marker > &marker_locations)
{
    this->marker_locations = marker_locations;
}

Path::Point Obstacle::GetMidpoint()
{
   return midpoint; 
}

Obstacle::Marker Obstacle::GetCorner()
{
   return corner_in_path; 
}


std::vector< Obstacle::Marker >* Obstacle::GetMarkerLocations()
{
    return &this->marker_locations;
}



