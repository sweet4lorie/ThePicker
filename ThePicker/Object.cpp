//
//  ThePicker
//  Object.cpp
//
//  Base class for creating objects
//  Handles basic transformations, and draws, set buffer
//  for both object and its bounding.
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Object.h"

Object::Object()
{
    _obj = "new";
    bound = "box";
    initBuffer();
}

void Object::setCompound(const std::string file)
{
    if (_obj == "new")
    {
        bound = "box";
        _obj = "compound";
        unpackCompound(&model, file);
        initBuffer();
    }
}

bool Object::inView(float (& projectionMatrix)[16], Mat4 & modelViewMatrix)
{
    return checkView(&boundModel, projectionMatrix, modelViewMatrix);
}

bool Object::hit(ray myRay)
{
    bool hitStatus = false;
    if (bound == "box")
    {
        hitStatus = hitBox(&boundModel, &MV, myRay);
    }
    return hitStatus;
}


void Object::initBuffer(){
    createBound();
    
    glGenVertexArrays(1, &_vertexArrayObject);
    glBindVertexArray(_vertexArrayObject);
    
    glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
    glGenBuffers(NUM_BUFFERS, _boundVertexArrayBuffers);
}


void Object::createBound()
{
    _bs.setValues(&model, &boundModel);
    _bs.box();
}

void Object::setBuffer()
{
    // OBJECT
    // = Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.vertex.size() * sizeof(model.vertex[0]), &model.vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // = Normal
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normal.size() * sizeof(model.normal[0]), &model.normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // = Texture
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normal.size() * sizeof(model.texture[0]), &model.texture[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}


void Object::setBoundBuffer()
{
    // OBJECT
    // = Vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, boundModel.vertex.size() * sizeof(boundModel.vertex[0]), &boundModel.vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}


void Object::draw(std::string drawType)
{
    glBindVertexArray(_vertexArrayObject);
    
    if (drawType == "object")
    {
        setBuffer();
        glDrawArrays(GL_TRIANGLES, 0, (int)model.vertex.size());
    }
    else if (drawType == "bound")
    {
        setBoundBuffer();
        glDrawArrays(GL_LINES, 0, (int)boundModel.vertex.size());
        
    }

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    
    glDisableVertexAttribArray(0);
}


Object::~Object()
{
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, _vertexArrayBuffers);
    glDeleteBuffers(1, _boundVertexArrayBuffers);
    glDeleteVertexArrays(1, &_vertexArrayObject);
    
}
