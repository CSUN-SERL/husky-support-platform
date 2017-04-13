#include "Vector.h"

Vector::Vector(double x, double y) {
    this->x = x;
    this->y = y;
    double x2 = pow(this->x, 2);
    double y2 = pow(this->y, 2);
    double powerSum = x2 + y2;
    this->mag = sqrt(powerSum);
}



