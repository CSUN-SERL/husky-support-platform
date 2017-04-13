#ifndef DESTINATION_H
#define DESTINATION_H

#include "Vector.h"
#include "Position.h"
#include "ros/ros.h"

class Destination{
public:
    Destination();
    Destination(double x, double y , Position* position);
    double getX();
    double getY();
    Vector getVector();
private:
    double x;
    double y;
    Position* position;
};


#endif /* DESTINATION_H */

