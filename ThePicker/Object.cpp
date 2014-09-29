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
    bs.setValues(boundVertexList, boundVertexIndices, boundVertexNormalList, boundTextureCoordList);
    createBound();
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glGenBuffers(NUM_BUFFERS, &indexArrayBuffer);
    glGenBuffers(NUM_BUFFERS, &normalArrayBuffer);
    glGenBuffers(NUM_BUFFERS, &normalIndexArrayBuffer);
    
    
    glGenBuffers(NUM_BUFFERS, boundVertexArrayBuffers);
    glGenBuffers(NUM_BUFFERS, &boundIndexArrayBuffer);
    glGenBuffers(NUM_BUFFERS, &boundNormalArrayBuffer);
    glGenBuffers(NUM_BUFFERS, &boundNormalIndexArrayBuffer);
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
    
    for(int i = 0; i < vertexList->size(); i++)
    {
        // find min/max
        if (vertexList->at(i).x < min.x)
            min.x = vertexList->at(i).x;
        if (vertexList->at(i).x > max.x)
            max.x = vertexList->at(i).x;
        greatestNum = max.x - min.x;
        
        if (vertexList->at(i).y < min.y)
            min.y = vertexList->at(i).y;
        if (vertexList->at(i).y > max.y)
            max.y = vertexList->at(i).y;
        if ((max.x - min.x) < (max.y - min.y))
            greatestNum = max.y - min.y;
        
        if (vertexList->at(i).z < min.z)
            min.z = vertexList->at(i).z;
        if (vertexList->at(i).z > max.z)
            max.z = vertexList->at(i).z;
        if (greatestNum < (max.z - min.z))
            greatestNum = max.z - min.z;
    }
    center.x = (max.x + min.x)/2;
    center.y = (max.y + min.y)/2;
    center.z = (max.z + min.z)/2;
    bs.sphere(greatestNum, center);
}

void Object::scale(float num)
{
    for(int i = 0; i < vertexList->size(); i++)
    {
        vertexList->at(i).x *= num;
        vertexList->at(i).y *= num;
        vertexList->at(i).z *= num;
    }
    for(int i = 0; i < boundVertexList->size(); i++)
    {
        boundVertexList->at(i).x *= num;
        boundVertexList->at(i).y *= num;
        boundVertexList->at(i).z *= num;
    }
}

void Object::translate(float x, float y, float z)
{
    translateUtil(x, y, z, vertexList);
    translateUtil(x, y, z, boundVertexList);
}

void Object::setBuffer()
{
    // OBJECT
    // = Verticies
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, vertexList->size() * sizeof(vec), &vertexList->at(0), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // where to start check, how big each data is, type, n/a, how much to skip, where to start
    glBindVertexArray(1);

    if (vertexIndices->size() > 0){
        // = Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices->size() * sizeof(GLushort), &vertexIndices->at(0), GL_STATIC_DRAW);
    }
    
    if (vertexNormalList->size() > 0){
        // = Vertex Normals
        glBindBuffer(GL_ARRAY_BUFFER, normalArrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexNormalList->size() * sizeof(vec), &vertexNormalList->at(0), GL_STATIC_DRAW);
    
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, normalArrayBuffer);
    }
    if (normalIndices->size() > 0){
        // = normal Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalIndexArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, normalIndices->size() * sizeof(GLushort), &normalIndices->at(0), GL_STATIC_DRAW);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    VIsize = (GLint)vertexIndices->size();
}

void Object::setBoundBuffer()
{
   // BOUNDING
    // = Verticies
    glBindBuffer(GL_ARRAY_BUFFER, boundVertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, boundVertexList->size() * sizeof(vec), &boundVertexList->at(0), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, boundVertexArrayBuffers[POSITION_VB]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // where to start check, how big each data is, type, n/a, how much to skip, where to start
    glBindVertexArray(1);

    if (boundVertexIndices->size() > 0){
        // = Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIndexArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, boundVertexIndices->size() * sizeof(GLushort), &boundVertexIndices->at(0), GL_STATIC_DRAW);
    }
    
    if (boundVertexNormalList->size() > 0){
        // = Vertex Normals
        glBindBuffer(GL_ARRAY_BUFFER, boundNormalArrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, boundVertexNormalList->size() * sizeof(vec), &boundVertexNormalList->at(0), GL_STATIC_DRAW);
    
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, boundNormalArrayBuffer);
    }
    
    if (boundNormalIndices->size() > 0){
        //std::cout << "\nSIZE HERE" << boundNormalIndices->size() << ;
        // = normal Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundNormalIndexArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, boundNormalIndices->size() * sizeof(GLushort), &boundNormalIndices->at(0), GL_STATIC_DRAW);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    boundVIsize = (GLint)boundVertexIndices->size();
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
    } else if (drawType == "bound")
    {
        setBoundBuffer();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundIndexArrayBuffer);
        glDrawElements(GL_QUADS, boundVIsize, GL_UNSIGNED_SHORT, 0);
        
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
    glDeleteBuffers(1, &indexArrayBuffer);
    glDeleteBuffers(1, &normalArrayBuffer);
    glDeleteBuffers(1, &normalIndexArrayBuffer);
    
    glDeleteBuffers(1, boundVertexArrayBuffers);
    glDeleteBuffers(1, &boundIndexArrayBuffer);
    glDeleteBuffers(1, &boundNormalArrayBuffer);
    glDeleteBuffers(1, &boundNormalIndexArrayBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
    
}
