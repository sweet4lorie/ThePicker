//
//  ThePicker
//  Shader.h
//
//  Header for: Helps handle setting up, editing, and calling shader
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Shader__
#define __ThePicker__Shader__

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Camera.h"
#include "Object.h"
#include "Utilities.h"

class Shader
{
    public:
        Shader(const std::string & file);
        void bind();
        void bindFixed();
        void update(const Camera & camera, Object & obj);
        void setColor(float r, float g, float b, float a);
        ~Shader();
    private:
        static const unsigned int NUM_SHADERS = 2;
        static const unsigned int NUM_UNIFORMS = 2;
        GLuint _program;
        GLuint _shaders[NUM_SHADERS];
        GLuint _uniforms[NUM_UNIFORMS];
};


#endif /* defined(__ThePicker__Shader__) */
