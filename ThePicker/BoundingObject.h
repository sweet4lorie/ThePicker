//
//  BoundingObject.h
//  ThePicker
//
//  Created by Emily Chiang on 9/28/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__BoundingObject__
#define __ThePicker__BoundingObject__

#include <iostream>
#include "Object.h"

class Bounding: public Object
{
    public:
        Bounding(vec & in_min, vec & in_max, vec & in_center, float & in_maxValue, std::string & in_type);
        ~Bounding();
    
        void sphere();
        //void cube();
    
        void hit();
    
    private:
        vec min;
        vec max;
        vec center;
        float maxValue;
        std::string type;

};


#endif /* defined(__ThePicker__BoundingObject__) */
