//
//  ThePicker
//  Mouse.cpp
//
//  translates mouse location to a Ray
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Mouse.h"

void Mouse::setMouseLocation(float * in_mouseX, float * in_mouseY)
{
    mouseX = in_mouseX;
    mouseY = in_mouseY;
}

ray Mouse::getRay(const Camera & camera, float win_width, float win_height)
{
    ray myRay;
    
    float x = (2.0f * *mouseX) / win_width - 1.0f;
    float y = 1.0f - (2.0f * *mouseY) / win_height;
    float z = -1.0f;
    
    vec rayNds = getVec(x, y, z);
    float rayClip[] = {rayNds.x, rayNds.y, z, 1.0};
    
    float rayEye[4];
    float tempInverse[16];
    float rayWorld[4];
    
    matInverse(&tempInverse[0]);
    matMultVec4fUtil(rayEye, rayClip, &tempInverse[0]);
    
    rayEye[2] = z;
    rayEye[3] = 0.0;
    
    matMultVec4fUtil(rayWorld, rayEye, &tempInverse[0]);
    vec4 rayWor = getVec4(rayWorld[0], rayWorld[1], rayWorld[2], rayWorld[3]);
    
    // don't forget to normalise the vector at some point
    rayWor = vec4Normalize(rayWor);
    
    myRay.origin.x = camera.position.x;
    myRay.origin.y = camera.position.y;
    myRay.origin.z = camera.position.z;
    myRay.direction.x = rayWor.x;
    myRay.direction.y = rayWor.y;
    myRay.direction.z = rayWor.z;
    myRay.direction.w = rayWor.w;
    
    return myRay;
}