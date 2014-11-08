//
//  ThePicker
//  Camera.h
//
//  header for:
//  handles camera lookAt and projection/modelview matrices
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Camera__
#define __ThePicker__Camera__

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utilities.h"

class Camera
{
    public:
        void setupCamera(float const win_aspect);
        void rotateCameraLeft(float degrees, float *eyePosition, float *centerPostion, float *upVector);
        void rotateCameraUp(float degrees, float *eyePosition, float *centerPosition, float *upVector);
    
        void setMouseLocation(const float & in_mouseX, const float & in_mouseY);
        ray getRay(float win_width, float win_height);
    
        void myPerspective(float fovy, const float aspect, float zNear, float zFar);
        void myLookAt(Vec3 eye, Vec3 center, Vec3 up);
    
        Mat4 myModelView;
        float myProjection[16];
        Vec3 position;
    
    private:
        float _mouseX;
        float _mouseY;
    
        float _rotationDelta = 2.0;
        Vec3 _centerPosition = {0.0, 0.0, 0.0};
        Vec3 _eyePosition = {0.0, 0.0, 2.0};
        Vec3 _upVector = {0.0, 1.0, 0.0};
};


#endif /* defined(__ThePicker__Camera__) */
