//
//  ThePicker
//  Texture.h
//
//  Header for: Helps handle setting up and binding texture
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Texture__
#define __ThePicker__Texture__

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "FreeImage.h"

class Texture
{
    public:
        Texture(const char * file);
        ~Texture();
        void bind();
    private:
        GLuint _textureID;
};

#endif /* defined(__ThePicker__Texture__) */
