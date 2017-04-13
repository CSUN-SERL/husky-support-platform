#ifndef VECTORANGLECALCULATOR_H
#define VECTORANGLECALCULATOR_H

#include <math.h>
#include <Vector.h>
#include "ros/ros.h"

class VectorAngleCalculator{
public:
    VectorAngleCalculator();
    double degree(Vector* v1, Vector* v2);
private:
    double calcDotProduct(Vector* v1, Vector* v2);
    double magMult(Vector* v1, Vector* v2);
    double angleSign(Vector* v1, Vector* v2);
};

#endif /* VECTORANGLECALCULATOR_H */

