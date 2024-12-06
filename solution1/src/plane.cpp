#include<iostream>

#include "plane.h"

Plane::Plane(double nx, double ny, double nz) {
    norm_vector[0] = nx;
    norm_vector[1] = ny;
    norm_vector[2] = nz;
}

void Plane::print() {
    for(const double el: norm_vector){
        std::cout<<el<<" ";
    }
    std::cout<<"\n";
    std::cout << "Plane print function called." << std::endl;
}

double* Plane::getNormalVector(){
    return norm_vector;
}
