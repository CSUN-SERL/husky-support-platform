#include "Destination.h"

Destination::Destination(){}

Destination::Destination(double x, double y, Position* position) {
    this->x = x;
    this->y = y;
    this->position = position;
}

double Destination::getX(){
    return this->x;
}

double Destination::getY(){
    return this->y;
}

Vector Destination::getVector(){
    double pCenterX = position->getCenterX();
    double pCenterY = position->getCenterY();
    double vectorX = this->x - pCenterX;
    double vectorY = this->y - pCenterY;
    Vector dVector = Vector(vectorX, vectorY);
    ROS_INFO("Destination Vector: pX:%f, pY:%f, vX:%f, vY:%f, X:%f, Y:%f, Mag:%f", pCenterX, pCenterY, vectorX, vectorY, this->x, this->y, dVector.mag);
    return dVector;
}

