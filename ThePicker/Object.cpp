//
//  Object.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/26/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "Object.h"


Object::Object()
{
    type = "triangle";
    bound = "sphere";
}

void Object::initBuffer(){
    createBound();
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glGenBuffers(NUM_BUFFERS, boundVertexArrayBuffers);
}

void Object::createBound()
{
    bs.setValues(&model, &boundModel);
    bs.sphere();
}

void Object::scale(float num)
{
    scaleUtil(num, &model.vertex);
    scaleUtil(num, &boundModel.vertex);
}

void Object::translate(float x, float y, float z)
{
    translateUtil(x, y, z, &model.vertex);
    translateUtil(x, y, z, &boundModel.vertex);
}

void Object::setBuffer()
{
    // OBJECT
    // = Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.vertex.size() * sizeof(model.vertex[0]), &model.vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // = Normal
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normal.size() * sizeof(model.normal[0]), &model.normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Object::setBoundBuffer()
{
    // OBJECT
    // = Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, boundModel.vertex.size() * sizeof(boundModel.vertex[0]), &boundModel.vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // = Normal
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, boundModel.normal.size() * sizeof(boundModel.normal[0]), &boundModel.normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}


void Object::draw(std::string drawType)
{
    glBindVertexArray(vertexArrayObject);
    if (drawType == "object")
    {
        setBuffer();
        
        if (type == "triangle"){
            glDrawArrays(GL_TRIANGLE_STRIP, 0, (int)model.vertex.size());
            //glDrawElements(GL_TRIANGLES, VIsize, GL_UNSIGNED_SHORT, 0);
        } else if (type == "quad"){
            glDrawArrays(GL_QUAD_STRIP, 0, (int)model.vertex.size());
        }
    } else if (drawType == "bound")
    {
        setBoundBuffer();
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIndexArrayBuffer);
        glDrawArrays(GL_QUAD_STRIP, 0, (int)boundModel.vertex.size());
        
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Object::~Object()
{
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, vertexArrayBuffers);
    glDeleteBuffers(1, boundVertexArrayBuffers);
    glDeleteVertexArrays(1, &vertexArrayObject);
    
}
