//
//  Display.h
//  ThePicker
//
//  Created by Emily Chiang on 9/25/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__Display__
#define __ThePicker__Display__

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>

static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Display
{
    public:
        Display(int width, int height, std::string title);
        virtual ~Display();
        bool isClosed();
        void update();
        void destroy();
        void clear(float r, float g, float b, float a);
    
    private:
        GLFWwindow* window;
};

#endif /* defined(__ThePicker__Display__) */