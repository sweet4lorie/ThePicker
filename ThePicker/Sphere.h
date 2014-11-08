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

#include <fstream>
#include <iostream>
#include "Object.h"

class Sphere
{
    public:
        Sphere(float radius, unsigned int rings, unsigned int sectors);
        virtual ~Sphere();
    
        void hit();
        void unpack(float radius, unsigned int rings, unsigned int sectors);
};

#endif /* defined(__ThePicker__Sphere__) */
