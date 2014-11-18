//
//  ThePicker
//  Utilities.cpp
//
//  Helps with various calculation functions
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Utilities.h"

float getMax(float a, float b)
{
    float max;
    if (a < b)
        max = b;
    else
        max = a;
    return max;
}

float getMin(float a, float b)
{
    float min;
    if (a > b)
        min = b;
    else
        min = a;
    return min;
}

plane planeNormalize(float * in_plane)
{
    //float l = sqrt(in_plane[0] * in_plane[0] + in_plane[1] * in_plane[1] + in_plane[2] * in_plane[2]);
    
    Vec3 tempV = {in_plane[0], in_plane[1], in_plane[2]};
    tempV.normalize();
    float l = tempV.length();
    
    plane tempP;
    tempP.normal = tempV;
    tempP.offset = in_plane[3] / l;
    
    return tempP;
}

void calcMinMaxCenter(modelPackage * objModel, Vec3 * min, Vec3 * max, Vec3 * center, float * maxValue)
{
    // Min/Max for bounding
    min->_x = 0.0;
    min->_y = 0.0;
    min->_z = 0.0;
    max->_x = 0.0;
    max->_y = 0.0;
    max->_z = 0.0;
    
    for(int i = 0; i < objModel->vertex.size(); i++)
    {
        // find min/max
        if (objModel->vertex[i]._x < min->_x)
            min->_x = objModel->vertex[i]._x;
        if (objModel->vertex[i]._x > max->_x)
            max->_x = objModel->vertex[i]._x;
        
        if (objModel->vertex[i]._y < min->_y)
            min->_y = objModel->vertex[i]._y;
        if (objModel->vertex[i]._y > max->_y)
            max->_y = objModel->vertex[i]._y;
        
        if (objModel->vertex[i]._z < min->_z)
            min->_z = objModel->vertex[i]._z;
        if (objModel->vertex[i]._z > max->_z)
            max->_z = objModel->vertex[i]._z;
    }
    if (*maxValue < (max->_x - min->_x))
        *maxValue = max->_x - min->_x;
    if (*maxValue < (max->_y - min->_y))
        *maxValue = max->_y - min->_y;
    if (*maxValue < (max->_z - min->_z))
        *maxValue = max->_z - min->_z;

    center->_x = (max->_x + min->_x)/2;
    center->_y = (max->_y + min->_y)/2;
    center->_z = (max->_z + min->_z)/2;
}
