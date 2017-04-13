#include "VectorAngleCalculator.h"

#define PI 3.14159265

VectorAngleCalculator::VectorAngleCalculator() {

}

double VectorAngleCalculator::degree(Vector* v1, Vector* v2) {
    double dotProduct = this->calcDotProduct(v1, v2);
    double magMult = this->magMult(v1, v2);
    if (magMult == 0) {
        return 0.0;
    } else {
        float vCos = dotProduct / magMult;
        return (acos(vCos) * 180.0 / PI) * this->angleSign(v1, v2);
    }
}

double VectorAngleCalculator::calcDotProduct(Vector* v1, Vector* v2) {
    return (v1->x * v2->x) + (v1->y * v2->y);
}

double VectorAngleCalculator::magMult(Vector* v1, Vector* v2) {
    return v1->mag * v2->mag;
}

double VectorAngleCalculator::angleSign(Vector* v1, Vector* v2){
    Vector rotatedVector = Vector(-1.0 * v1->y, v1->x);
    double rotatedDotPorduct = this->calcDotProduct(&rotatedVector, v2);
    if(rotatedDotPorduct >= 0){
        return 1.0;
    }else{
        return -1.0;
    }
}



