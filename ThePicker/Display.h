//
//  ThePicker
//  Display.h
//
//  Header for display; helps handle display
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//


#ifndef __ThePicker__Display__
#define __ThePicker__Display__

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.h"

class Display
{
    public:
        Display(int width, int height, std::string title);
        virtual ~Display();
        GLFWwindow* window;
    
        bool isClosed();
        void update();
        void destroy();
        void clear(float r, float g, float b, float a);
        static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        
};

#endif /* defined(__ThePicker__Display__) */
