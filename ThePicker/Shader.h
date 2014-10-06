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
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
    public:
        Shader(const std::string & file);
        void bind();
        void bindFixed();
        void setMatrix();
        void setColor(float r, float g, float b, float a);
        ~Shader();
    private:
        static const unsigned int NUM_SHADERS = 2;
        GLuint program;
        GLint posAttrib;
        GLuint shaders[NUM_SHADERS];
};


#endif /* defined(__ThePicker__Shader__) */
