//
//  Compound.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "Compound.h"

Compound::Compound(const std::string file)
{
    unpack(file);
    initBuffer();
}

void Compound::unpack(const std::string file)
{
    char buffer [255];
    
    // for file
    std::ifstream inFile;
    inFile.open(file);
    
    if (inFile.is_open())
    {
        // current vec
        vec currentVec;
        
        while(!inFile.eof()){
            inFile.getline(buffer, sizeof(buffer), '\n');
            
            // vertex
            if(strncmp(buffer, "v ", 2) == 0) // is 'v '
            {
                sscanf(buffer, "v %f %f %f", &(currentVec.x), &(currentVec.y), &(currentVec.z));
                vertexList->push_back(currentVec);
            }
            
            // texture coord
            else if(strncmp(buffer, "vt", 2) == 0) // is 'vt'
            {
                sscanf(buffer, "vt %f %f", &(currentVec.x), &(currentVec.y));
                currentVec.z = 0.0;
                textureCoordList->push_back(currentVec);
            }
            
            // vertex normal
            else if(strncmp(buffer, "vn", 2) == 0) // is 'vn'
            {
                sscanf(buffer, "vn %f %f %f", &(currentVec.x), &(currentVec.y), &(currentVec.z));
                vertexNormalList->push_back(currentVec);
            }
            
            // face
            else if(strncmp(buffer, "f ", 2) == 0) // is 'f '
            {
                GLushort vertexIndex[3], uvIndex[3], normalIndex[3];
                sscanf(buffer, "f %hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu",
                                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                //std::cout << vertexIndex[1] << std::endl;
                vertexIndices->push_back(vertexIndex[0]);
                vertexIndices->push_back(vertexIndex[1]);
                vertexIndices->push_back(vertexIndex[2]);
                uvIndices->push_back(uvIndex[0]);
                uvIndices->push_back(uvIndex[1]);
                uvIndices->push_back(uvIndex[2]);
                normalIndices->push_back(normalIndex[0]);
                normalIndices->push_back(normalIndex[1]);
                normalIndices->push_back(normalIndex[2]);
            }
        } // while
    } // if file
    
    inFile.close();
    //std::cout << "DONE";
}


Compound::~Compound()
{
}

/*std::vector<vec> vertexList;
vec one;
one.x = -0.5;
one.y = -0.5;
one.z = 0;
vertexList.push_back(one);
vec two;
two.x = 0;
two.y = 0.5;
two.z = 0;
vertexList.push_back(two);
vec three;
three.x = 0.5;
three.y = -0.5;
three.z = 0;
vertexList.push_back(three);*/