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
        Camera (Vec3 eyePosition, Vec3 upVector);
        void reset(Vec3 eyePosition, Vec3 upVector);
        void setupCamera(float const win_aspect);
        void rotate(double mousePX, double mousePY, double mouseRX, double mouseRY0, double r);
    
        ray getRay(float win_width, float win_height, const float & in_mouseX, const float & in_mouseY);
    
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
