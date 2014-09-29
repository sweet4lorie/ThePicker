//
//  Utilities.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/23/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "Utilities.h"

bool VVvecComp(vec comp1, vec comp2)
{
    bool check = true;
    
    if (comp1.x != comp2.x)
        check = false;
    if (comp1.y != comp2.y)
        check = false;
    if (comp1.z != comp2.z)
        check = false;
    
    return check;
}

void scaleUtil(float num, std::vector<vec> * objectList)
{
    for(int i = 0; i < objectList->size(); i++)
    {
        if(i % 3 == 0)
        {
            objectList->at(i).x *= num;
            objectList->at(i).y *= num;
            objectList->at(i).z *= num;
        }
    }
}

void translateUtil(float x, float y, float z, std::vector<vec> * objectList)
{
    for(int i = 0; i < objectList->size(); i++)
    {
        if(i % 3 == 0)
        {
            objectList->at(i).x += x;
            objectList->at(i).y += y;
            objectList->at(i).z += z;
        }
    }
}

vec getFaceNormal(vec pt1, vec pt2, vec pt3)
{
    vec norm;
    norm = getCross(getDifference(pt1, pt3), getDifference(pt1, pt2));
    norm = getNormalize(norm);
    //std::cout << norm.x << " " << norm.y << " " << norm.z << std::endl;
    return norm;
}

vec getNormalize(vec vector)
{
    vec result;
    float length;
    length = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
    if (length <= 0.0){
        result.x = 0.0;
        result.y = 0.0;
        result.z = 0.0;
    }
    else
    {
        result.x = vector.x/length;
        result.y = vector.y/length;
        result.z = vector.z/length;
    }
    
    return result;
}

vec getDifference(vec head, vec tail)
{
    vec result;
    result.x = head.x - tail.x;
    result.y = head.y - tail.y;
    result.z = head.z - tail.z;
    return result;
}

vec getCross(vec vector1, vec vector2)
{
    vec result;
    result.x = vector1.y * vector2.z - vector1.z * vector2.y;
    result.y = vector1.z * vector2.x - vector1.x * vector2.z;
    result.z = vector1.x * vector2.y - vector1.y * vector2.x;
    //std::cout << vector1.y << " * " << vector2.z << " - " << vector2.z  << " * " << vector1.y << std::endl;
    return result;
}