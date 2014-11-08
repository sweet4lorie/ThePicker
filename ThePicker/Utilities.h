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

#define PROJECTION_SIZE 16

/*
typedef struct
{
    float x, y, z;
} vec3;

typedef struct
{
    float x, y, z, w;
} vec4;
*/

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
    float angle;
    Vec3 vector;
} rotation;


float getMax(float a, float b);
float getMin(float a, float b);
void calcMinMaxCenter(modelPackage * objModel, Vec3 * min, Vec3 * max, Vec3 * center, float * maxValue);


/*
vec3 getVec(float x, float y, float z);
vec4 getVec4(float x, float y, float z, float w);

void vecCopy4fUtil(float *dest, float *src);
void vecCrossfUtil(float * resultVector, float * vector1, float * vector2);

bool matInverse(float * m, float * invOut);
void matMultVec4fUtil(float* vout, float* v, float* m);
void matMult4fUtil (float * resultMat, float * mat1, float * mat2);
void matTranslatefUtil( float *matrix, float x, float y, float z );
void matScalefUtil( float *matrix, float x, float y, float z );
void matRotatefUtil( float *rotationMatrix, float degrees, float x, float y, float z );

void translateUtil(float x, float y, float z, std::vector<vec3> *vertexList);
void scaleUtil(float num, std::vector<vec3> * vertexList);
vec4 vec4Normalize(vec4 vector);
vec3 vecFaceNormal(vec3 pt1, vec3 pt2, vec3 pt3);
vec3 vecDifference(vec3 head, vec3 tail);
vec3 vecCross(vec3 vector1, vec3 vector2);
vec3 vecNormalize(vec3 vector);
*/
#endif /* defined(__ThePicker__File__) */
