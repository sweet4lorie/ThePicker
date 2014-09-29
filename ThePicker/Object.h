//
//  Object.h
//  ThePicker
//
//  Created by Emily Chiang on 9/26/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef OBJECT_H
#define OBJECT_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "ObjectHelper.h"

class Object
{
    public:
        Object();
        ~Object();
        std::vector<vec> * vertexList = new std::vector<vec>;
        std::vector<vec> * vertexNormalList = new std::vector<vec>;
        std::vector<GLushort> * vertexIndices = new std::vector<GLushort>;
        std::vector<GLushort> * normalIndices = new std::vector<GLushort>;
        
        std::string type;
        std::string bound;

        void initBuffer();
        void scale(float num);
        void translate(float x, float y, float z);

        void setBuffer();
        void draw();
        void createBound(std::string type);
        void clean();
    
    private:
        enum
        {
            POSITION_VB,
            INDEX_VB,
            TEXCOORD_VB,
            NUM_BUFFERS
        };
        GLuint VIsize;
        GLuint vertexArrayObject;
        GLuint vertexArrayBuffers[NUM_BUFFERS];
        GLuint indexArrayBuffer;
        GLuint normalArrayBuffer;
        GLuint normalIndexArrayBuffer;

};

#endif /* OBJECT_H */