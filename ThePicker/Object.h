//
//  ThePicker
//  Object.h
//
//  Header for:
//  Base class for creating objects
//  Handles basic transformations, and draws, set buffer
//  for both object and its bounding.
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef OBJECT_H
#define OBJECT_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "ObjectUnpack.h"
#include "ObjectHit.h"
#include "BoundingObject.h"
#include "Transform.h"

class Object : public Transform
{
    public:
        Object();
        ~Object();
    
        // set object
        void setSphere(float radius, unsigned int rings, unsigned int sectors);
        void setCompound(const std::string file);
    
        // object
        GLuint positionID;
        GLuint normalID;
        modelPackage model;
    
        // bounding
        modelPackage boundModel;
        std::string bound;

        void initBuffer();

        void setBuffer();
        void setBoundBuffer();
    
        void draw(std::string type = "object");
        bool inView(float (& projectionMatrix)[16], Mat4 & modelViewMatrix);
        bool hit(ray myRay);
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
    
        Bounding _bs;
        GLuint _vertexArrayObject;
    
        //object
        std::string _obj;
        GLuint _VIsize;
        GLuint _vertexArrayBuffers[NUM_BUFFERS];
    
        // bounding
        GLuint _boundVIsize;
        GLuint _boundVertexArrayBuffers[NUM_BUFFERS];

};

#endif /* OBJECT_H */