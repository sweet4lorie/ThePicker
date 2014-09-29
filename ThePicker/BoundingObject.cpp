//
//  BoundingObject.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/28/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "BoundingObject.h"

Bounding::Bounding(vec & in_min, vec & in_max, vec & in_center, float & in_maxValue, std::string & in_type)
{
    type = in_type;
    min = in_min;
    max = in_max;
    center = in_center;
    maxValue = in_maxValue;
}

void Bounding::sphere()
{
    
    
}
