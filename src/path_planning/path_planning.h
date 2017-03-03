
/* 
 * File:   path_planning.h
 * Author: serl - Anthony Pichardo
 *
 * Created on March 2, 2017, 1:23 PM
 */

#include "obstacle.h"

#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

using namespace std;
class path_planning {
public:
    path_planning();
    vector< vector<double> > path_planning(vector<double> start,
    vector<double> goal, vector<obstacle> obstacle_list);
    virtual ~path_planning();
    vector< vector<double> > waypoints;
    
    set_vehicle_location(vector<double> vehicle_location);
    vector<double> get_vehicle_location();
    
    set_goal(vector<double> goal);
    vector<double> get_goal();
    
    set_obstacle_list(vector<obstacle> obstacles);
    vector<obstacle> get_obstacle_list();
private:
    vector<double> goal,
            vehicle_location;
    vector<obstacle> obstacle_list;
    
    vector< vector<double> > generate_min_path(vector<double> start,
    vector<double> destination);
    
    vector<obstacle> sort_obstacle_list(vector<double> start,
    vector<double> destination,vector<obstacle> obstacle_list);
    
    bool is_path_clear(vector<double> start, vector<double> destination);
    
    add_new_waypoint(vector<double> destination);
    
    vector< vector<double> > get_waypoints();

};

#endif /* PATH_PLANNING_H */

