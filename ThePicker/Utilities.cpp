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

/*
vec3 getVec3(float x, float y, float z)
{
    vec3 tempVertex;
    tempVertex.x = x;
    tempVertex.y = y;
    tempVertex.z = z;
    return tempVertex;
}

vec4 getVec4(float x, float y, float z, float w)
{
    vec4 tempVertex;
    tempVertex.x = x;
    tempVertex.y = y;
    tempVertex.z = z;
    tempVertex.w = w;
    return tempVertex;
}

void vecCopy4fUtil(float *dest, float *src)
{
    int i;
    for(i = 0; i < 4; i++){
        dest[i] = src[i];
    }
}

// result = A cross B
void vecCrossfUtil(float * resultVector, float * vector1, float * vector2)
{
    resultVector[0] = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
    resultVector[1] = (vector2[0] * vector1[2]) - (vector1[0] * vector2[2]);
    resultVector[2] = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
}

bool matInverse(float * m, float * invOut)
{
    float inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

void matMultVec4fUtil(float * vout, float * v, float * m)
{
    float c[4];
    vecCopy4fUtil(c, v);
    vout[0] = m[0] * c[0] + m[4] * c[1] + m[8]  * c[2] + m[12] * c[3];
    vout[1] = m[1] * c[0] + m[5] * c[1] + m[9]  * c[2] + m[13] * c[3];
    vout[2] = m[2] * c[0] + m[6] * c[1] + m[10] * c[2] + m[14] * c[3];
    vout[3] = m[3] * c[0] + m[7] * c[1] + m[11] * c[2] + m[15] * c[3];
}

// C = A * B
// C, A, B are all matrices
void matMult4fUtil (float * resultMat, float * mat1, float * mat2)
{
    // copy matrices
    float tempMat1[16];
    float tempMat2[16];
    for (int i = 0; i < 16; i++)
    {
        tempMat1[i] = mat1[i];
        tempMat2[i] = mat2[i];
    }

    // matrix multiplication operations
    for (int i = 0; i < 4; i++)
    {
        resultMat[i] = tempMat1[0+i] * tempMat2[0] + tempMat1[4+i] * tempMat2[1] + tempMat1[8+i] * tempMat2[2] + tempMat1[12+i] * tempMat2[3];
        resultMat[i+4] = tempMat1[0+i] * tempMat2[4] + tempMat1[4+i] * tempMat2[5] + tempMat1[8+i] * tempMat2[6] + tempMat1[12+i] * tempMat2[7];
        resultMat[i+8] = tempMat1[0+i] * tempMat2[8] + tempMat1[4+i] * tempMat2[9] + tempMat1[8+i] * tempMat2[10] + tempMat1[12+i] * tempMat2[11];
        resultMat[i+12] = tempMat1[0+i] * tempMat2[12] + tempMat1[4+i] * tempMat2[13] + tempMat1[8+i] * tempMat2[14] + tempMat1[12+i] * tempMat2[15];
    }
}

void matTranslatefUtil( float *matrix, float x, float y, float z )
{
    float translationMatrix[16] = { 1.0, 0.0, 0.0, 0.0,
                                    0.0, 1.0, 0.0, 0.0,
                                    0.0, 0.0, 1.0, 0.0,
                                    x, y, z, 1.0 };
    matMult4fUtil(matrix, matrix, translationMatrix);
}

// scale on matrices
void matScalefUtil( float *matrix, float x, float y, float z )
{
    // Scale matrix
    float scale_matrix[16] = { x, 0.0, 0.0, 0.0,
                               0.0, y, 0.0, 0.0,
                               0.0, 0.0, z, 0.0,
                               0.0, 0.0, 0.0, 1.0};
    matMult4fUtil(matrix, matrix, scale_matrix);
}


// rotate matrix
void matRotatefUtil( float *rotationMatrix, float degrees, float x, float y, float z )
{
    // Variables needed to perform operations
    float angle = degrees * M_PI / 180;
    float c = cosf(angle);
    float s = sinf(angle);

    // normalize xyz
    float magnitudeOfxyz = sqrtf( powf(x, 2) + powf(y, 2) + powf(z, 2));
    if(magnitudeOfxyz == 0)
        magnitudeOfxyz = 1;
    float normX = x / magnitudeOfxyz;
    float normY = y / magnitudeOfxyz;
    float normZ = z / magnitudeOfxyz;

    // Rodrigues' rotation formula
    rotationMatrix[0] = (normX * normX * (1 - c)) + c; // wrong
    rotationMatrix[1] = (normY * normX * (1 - c)) + (normZ * s);
    rotationMatrix[2] = (normX * normZ * (1 - c)) - (normY * s);
    rotationMatrix[3] = 0.0;
    rotationMatrix[4] = (normX * normY * (1 - c)) - (normZ * s);
    rotationMatrix[5] = (normY * normY * (1 - c)) + c; 
    rotationMatrix[6] = (normY * normZ * (1 - c)) + (normX * s); //wrong
    rotationMatrix[7] = 0.0;
    rotationMatrix[8] = (normX * normZ * (1 - c)) + (normY * s);
    rotationMatrix[9] = (normY * normZ * (1 - c)) - (normX * s); //wrong
    rotationMatrix[10] = (normZ * normZ * (1 - c)) + c;
    rotationMatrix[11] = 0.0;
    rotationMatrix[12] = 0.0;
    rotationMatrix[13] = 0.0;
    rotationMatrix[14] = 0.0;
    rotationMatrix[15] = 1.0;
}

//====

void translateUtil(float x, float y, float z, std::vector<vec3> * vertexList)
{
    for(int i = 0; i < vertexList->size(); i++)
    {
        vertexList->at(i).x += x;
        vertexList->at(i).y += y;
        vertexList->at(i).z += z;
    }
    
}

void scaleUtil(float num, std::vector<vec3> * vertexList)
{
    for(int i = 0; i < vertexList->size(); i++)
    {
        vertexList->at(i).x *= num;
        vertexList->at(i).y *= num;
        vertexList->at(i).z *= num;
    }
}

vec4 vec4Normalize(vec4 vector)
{
    vec4 result;
    float length;
    length = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z) + (vector.w * vector.w));
    if (length <= 0.0){
        result.x = 0.0;
        result.y = 0.0;
        result.z = 0.0;
        result.w = 0.0;
    }
    else
    {
        result.x = vector.x/length;
        result.y = vector.y/length;
        result.z = vector.z/length;
        result.w = vector.w/length;
    }
    
    return result;
}


vec3 vecFaceNormal(vec3 pt1, vec3 pt2, vec3 pt3)
{
    vec3 norm;
    norm = vecCross(vecDifference(pt1, pt3), vecDifference(pt1, pt2));
    norm = vecNormalize(norm);
    //std::cout << norm.x << " " << norm.y << " " << norm.z << std::endl;
    return norm;
}

vec3 vecNormalize(vec3 vector)
{
    vec3 result;
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

vec3 vecDifference(vec3 head, vec3 tail)
{
    vec3 result;
    result.x = head.x - tail.x;
    result.y = head.y - tail.y;
    result.z = head.z - tail.z;
    return result;
}

vec3 vecCross(vec3 vector1, vec3 vector2)
{
    vec3 result;
    result.x = vector1.y * vector2.z - vector1.z * vector2.y;
    result.y = vector1.z * vector2.x - vector1.x * vector2.z;
    result.z = vector1.x * vector2.y - vector1.y * vector2.x;
    //std::cout << vector1.y << " * " << vector2.z << " - " << vector2.z  << " * " << vector1.y << std::endl;
    return result;
}
*/