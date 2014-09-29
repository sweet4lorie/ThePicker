//
//  BoundingObject.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/28/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "BoundingObject.h"

Bounding::Bounding()
{
}

void Bounding::setValues(std::vector<vec> * in_objectList, std::vector<unsigned short> * in_objectIndices)
{
    objectList = in_objectList;
    objectIndices = in_objectIndices;
}

void Bounding::sphere(float & maxValue, vec & center)
{
    //std::cout << center.x << " " << center.y << " " << center.z << std::endl;
    unpackSphere(objectList, objectIndices, maxValue/2, 10, 10);
}

/*
void Bounding::box(vec & in_min, vec & in_max, vec & in_center)
{
}
*/

bool Bounding::hitSphere()
{
    return false;
}

Bounding::~Bounding()
{
}
