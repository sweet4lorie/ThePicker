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

void Bounding::setValues(std::vector<vec> * in_vertexList, std::vector<unsigned short> * in_vertexIndices,
                std::vector<vec> * in_vertexNormalList, std::vector<vec> * in_textureCoordList)
{
    vertexList = in_vertexList;
    vertexIndices = in_vertexIndices;
    vertexNormalList = in_vertexNormalList;
    textureCoordList = in_textureCoordList;
}

void Bounding::sphere(float & maxValue, vec & center)
{
    //std::cout << center.x << " " << center.y << " " << center.z << std::endl;
    unpackSphere(vertexList, vertexIndices, vertexNormalList, textureCoordList, maxValue, 10, 10);
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
