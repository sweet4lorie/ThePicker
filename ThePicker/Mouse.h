//
//  ThePicker
//  Mouse.h
//
//  header for: translates mouse location to a Ray
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Mouse__
#define __ThePicker__Mouse__

#include <stdio.h>
#include "Camera.h"
#include "Utilities.h"

class Mouse
{
    public:
        void setMouseLocation(float * mouseX, float * mouseY);
        ray getRay(const Camera & camera, float window_width, float window_height);
    private:
        float * mouseX = new float;
        float * mouseY = new float;
};

#endif /* defined(__ThePicker__Mouse__) */
