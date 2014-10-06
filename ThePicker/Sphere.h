//
//  ThePicker
//  Sphere.
//
//  Header for: handles calculations to draw at sphere object
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Sphere__
#define __ThePicker__Sphere__

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

#include <fstream>
#include <iostream>
#include "Object.h"

class Sphere: public Object
{
    public:
        Sphere(float radius, unsigned int rings, unsigned int sectors);
        virtual ~Sphere();
    
        void hit();
        void unpack(float radius, unsigned int rings, unsigned int sectors);
};

#endif /* defined(__ThePicker__Sphere__) */
