#ifndef PLANE_H
#define PLANE_H



#include <iostream>

class Plane {
private:
    double norm_vector[3];
public:
    Plane(double nx, double ny, double nz);

    double* getNormalVector();
    void print();
};


#endif
