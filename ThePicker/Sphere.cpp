//
//  ThePicker
//  Sphere.cpp
//
//  Handles calculations to draw at sphere object
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Sphere.h"

Sphere::Sphere(float radius, unsigned int rings, unsigned int sectors)
{
    type = "quad";
    bound = "sphere";
    unpackSphere(&model, radius, rings, sectors);
    initBuffer();
}

void Sphere::hit()
{
    std::cout << "Check Hit" << std::endl;
}

Sphere::~Sphere()
{
}
