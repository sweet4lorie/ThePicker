//
//  ThePicker
//  Utilities.h
//
//  Header for: Helps with various calculation functions and sets up structs
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Utilities__
#define __ThePicker__Utilities__

#include <iostream>
#include <cmath>
#include <vector>
#include "Mat4.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Quat.h"

#define PROJECTION_SIZE 16

typedef struct
{
    std::vector<Vec3> vertex;
    std::vector<Vec3> texture;
    std::vector<Vec3> normal;
} modelPackage;

typedef struct
{
    Vec3 origin;
    Vec4 direction;
} ray;

typedef struct
{
    Vec3 normal;
    float offset;
} plane;

typedef struct
{
    float angle;
    Vec3 vector;
} rotation;


float getMax(float a, float b);
float getMin(float a, float b);
plane planeNormalize(float * in_plane);
void calcMinMaxCenter(modelPackage * objModel, Vec3 * min, Vec3 * max, Vec3 * center, float * maxValue);


#endif /* defined(__ThePicker__File__) */
