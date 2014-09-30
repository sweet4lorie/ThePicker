//
//  Utilities.h
//  ThePicker
//
//  Created by Emily Chiang on 9/23/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__File__
#define __ThePicker__File__

#include <iostream>
#include <cmath>
#include <vector>

typedef struct
{
    float x, y, z;
} vec;

typedef struct
{
    std::vector<vec> vertex;
    std::vector<vec> normal;
} modelPackage;

void translateUtil(float x, float y, float z, std::vector<vec> *vertexList);
void scaleUtil(float num, std::vector<vec> * vertexList);
vec getFaceNormal(vec pt1, vec pt2, vec pt3);
vec getDifference(vec head, vec tail);
vec getCross(vec vector1, vec vector2);
vec getNormalize(vec vector);

#endif /* defined(__ThePicker__File__) */
