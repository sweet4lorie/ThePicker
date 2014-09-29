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
#include "BoundingObject.h"

class Object
{
    public:
        Object();
        ~Object();
    
        //object
        std::vector<vec> * vertexList = new std::vector<vec>;
        std::vector<vec> * vertexNormalList = new std::vector<vec>;
        std::vector<GLushort> * vertexIndices = new std::vector<GLushort>;
        std::vector<GLushort> * normalIndices = new std::vector<GLushort>;
    
        // bounding
        std::vector<vec> * boundVertexList = new std::vector<vec>;
        std::vector<vec> * boundVertexNormalList = new std::vector<vec>;
        std::vector<GLushort> * boundVertexIndices = new std::vector<GLushort>;
        std::vector<GLushort> * boundNormalIndices = new std::vector<GLushort>;
        std::vector<vec> * boundTextureCoordList = new std::vector<vec>;

        std::string type;
        std::string bound;

        void initBuffer();
        void scale(float num);
        void translate(float x, float y, float z);

        void setBuffer();
        void setBoundBuffer();
        void draw(std::string type = "object");
        void createBound();
        void clean();
    
    private:
        enum
        {
            POSITION_VB,
            INDEX_VB,
            TEXCOORD_VB,
            NUM_BUFFERS
        };
        Bounding bs;
        GLuint vertexArrayObject;
        //object
        GLuint VIsize;
        GLuint vertexArrayBuffers[NUM_BUFFERS];
        GLuint indexArrayBuffer;
        GLuint normalArrayBuffer;
        GLuint normalIndexArrayBuffer;
        // bounding
        GLuint boundVIsize;
        GLuint boundVertexArrayBuffers[NUM_BUFFERS];
        GLuint boundIndexArrayBuffer;
        GLuint boundNormalArrayBuffer;
        GLuint boundNormalIndexArrayBuffer;

};

#endif /* OBJECT_H */