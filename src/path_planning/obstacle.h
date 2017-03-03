
/* 
 * File:   obstacle.h
 * Author: serl
 *
 * Created on March 2, 2017, 1:47 PM
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H
using namespace std;
class obstacle 
{
public:
    obstacle();
    obstacle(vector< vector<double> > marker_locations);
    virtual ~obstacle();
    set_marker_locations(vector< vector<double> > marker_locations);
    get_marker_locations();
private:
    vector< vector<double> > marker_locations;

};

#endif /* OBSTACLE_H */

