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
    bs.setValues(boundObjectList, boundObjectIndices);
    createBound();
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glGenBuffers(NUM_BUFFERS, &indexArrayBuffer);
    
    glGenBuffers(NUM_BUFFERS, boundVertexArrayBuffers);
    glGenBuffers(NUM_BUFFERS, &boundIndexArrayBuffer);
}

void Object::createBound()
{
    // Min/Max for bounding
    vec min;
    min.x = 0.0;
    min.y = 0.0;
    min.z = 0.0;
    vec max;
    max.x = 0.0;
    max.y = 0.0;
    max.z = 0.0;
    vec center;
    float greatestNum;
    
    for(int i = 0; i < objectList->size(); i++)
    {
        if (i % 3 == 0)
        {
            // find min/max
            if (objectList->at(i).x < min.x)
                min.x = objectList->at(i).x;
            if (objectList->at(i).x > max.x)
                max.x = objectList->at(i).x;
            greatestNum = max.x - min.x;
            
            if (objectList->at(i).y < min.y)
                min.y = objectList->at(i).y;
            if (objectList->at(i).y > max.y)
                max.y = objectList->at(i).y;
            if ((max.x - min.x) < (max.y - min.y))
                greatestNum = max.y - min.y;
            
            if (objectList->at(i).z < min.z)
                min.z = objectList->at(i).z;
            if (objectList->at(i).z > max.z)
                max.z = objectList->at(i).z;
            if (greatestNum < (max.z - min.z))
                greatestNum = max.z - min.z;
        }
    }
    center.x = (max.x + min.x)/2;
    center.y = (max.y + min.y)/2;
    center.z = (max.z + min.z)/2;
    bs.sphere(greatestNum, center);
}

void Object::scale(float num)
{
    scaleUtil(num, objectList);
    scaleUtil(num, boundObjectList);
}

void Object::translate(float x, float y, float z)
{
    translateUtil(x, y, z, objectList);
    translateUtil(x, y, z, boundObjectList);
}

void Object::setBuffer()
{
    // OBJECT
    // = Verticies
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, objectList->size() * sizeof(vec), &objectList->at(0), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec) * 2, 0);
    // where to start check, how big each data is, type, n/a, how much to skip, where to start
    glBindVertexArray(1);

    if (objectList->size() > 0){
        // = Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, objectIndices->size() * sizeof(GLushort), &objectIndices->at(0), GL_STATIC_DRAW);
    }
    VIsize = (GLint)objectIndices->size();
}

void Object::setBoundBuffer()
{
   // BOUNDING
    // = Verticies
    glBindBuffer(GL_ARRAY_BUFFER, boundVertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, boundObjectList->size() * sizeof(vec), &boundObjectList->at(0), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, boundVertexArrayBuffers[POSITION_VB]);
    glVertexAttribPointer(0, sizeof(vec), GL_FLOAT, GL_FALSE, sizeof(vec) * 2, 0);
    // where to start check, how big each data is, type, n/a, how much to skip, where to start
    glBindVertexArray(1);

    if (boundObjectIndices->size() > 0){
        // = Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIndexArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, boundObjectIndices->size() * sizeof(GLushort), &boundObjectIndices->at(0), GL_STATIC_DRAW);
    }
    boundVIsize = (GLint)boundObjectIndices->size();
}


void Object::draw(std::string drawType)
{
    glBindVertexArray(vertexArrayObject);
    if (drawType == "object")
    {
        setBuffer();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBuffer);
        
        if (type == "triangle"){
            glDrawElements(GL_TRIANGLES, VIsize, GL_UNSIGNED_SHORT, 0);
        } else if (type == "quad"){
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
            glDrawElements(GL_QUADS, VIsize, GL_UNSIGNED_SHORT, 0);
        }
    } /*else if (drawType == "bound")
    {
        setBoundBuffer();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIndexArrayBuffer);
        glDrawElements(GL_QUADS, boundVIsize, GL_UNSIGNED_SHORT, 0);
        
    }*/

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Object::~Object()
{
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, vertexArrayBuffers);
    glDeleteBuffers(1, &indexArrayBuffer);
    
    glDeleteBuffers(1, boundVertexArrayBuffers);
    glDeleteBuffers(1, &boundIndexArrayBuffer);

    glDeleteVertexArrays(1, &vertexArrayObject);
    
}
