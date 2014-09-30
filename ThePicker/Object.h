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
        GLuint positionID;
        GLuint normalID;
        modelPackage model;
    
        // bounding
        modelPackage boundModel;

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
            NORMAL_VB,
            TEXCOORD_VB,
            NUM_BUFFERS
        };
        Bounding bs;
        GLuint vertexArrayObject;
        //object
        GLuint VIsize;
        GLuint vertexArrayBuffers[NUM_BUFFERS];
        // bounding
        GLuint boundVIsize;
        GLuint boundVertexArrayBuffers[NUM_BUFFERS];

};

#endif /* OBJECT_H */