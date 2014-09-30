//
//  Compound.h
//  ThePicker
//
//  Created by Emily Chiang on 9/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
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
