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

void Bounding::setValues(modelPackage * in_objModel, modelPackage * in_model)
{
    objModel = in_objModel;
    model = in_model;
}

void Bounding::sphere()
{
    // Min/Max for bounding
    vec min;
    min.x = 0.0;
    min.y = 0.0;
    min.z = 0.0;
    vec max;
    max.x = 0.0;
    max.y = 0.0;
    max.z = 0.0;
    vec center;
    float maxValue = 0;
    
    for(int i = 0; i < objModel->vertex.size(); i++)
    {
        // find min/max
        if (objModel->vertex[i].x < min.x)
            min.x = objModel->vertex[i].x;
        if (objModel->vertex[i].x > max.x)
            max.x = objModel->vertex[i].x;
        maxValue = max.x - min.x;
        
        if (objModel->vertex[i].y < min.y)
            min.y = objModel->vertex[i].y;
        if (objModel->vertex[i].y > max.y)
            max.y = objModel->vertex[i].y;
        if ((max.x - min.x) < (max.y - min.y))
            maxValue = max.y - min.y;
        
        if (objModel->vertex[i].z < min.z)
            min.z = objModel->vertex[i].z;
        if (objModel->vertex[i].z > max.z)
            max.z = objModel->vertex[i].z;
        if (maxValue < (max.z - min.z))
            maxValue = max.z - min.z;
    }
    center.x = (max.x + min.x)/2;
    center.y = (max.y + min.y)/2;
    center.z = (max.z + min.z)/2;
    //std::cout << center.x << " " << center.y << " " << center.z << std::endl;
    unpackSphere(model, maxValue/2, 10, 10);
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
