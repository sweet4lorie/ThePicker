//
//  ThePicker
//  Compound.cpp
//
//  Header for: Handles calculations to draw from an obj file
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __BunnyModel__getPlyModel__
#define __BunnyModel__getPlyModel__

#include <fstream>
#include <cassert>
#include <iostream>
#include "Object.h"

class Compound: public Object
{
    public:
        Compound(const std::string file);
        ~Compound();
    
        void unpack(const std::string file);
};

#endif /* defined(__BunnyModel__getPlyModel__) */
