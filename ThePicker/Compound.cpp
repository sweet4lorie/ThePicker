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
    std::vector<vec> tempVertexList;
    std::vector<vec> tempUVCoordList;
    std::vector<vec> tempVectorNormalList;
    std::vector<vec> tempFace;
    tempFace.reserve(6);
    unsigned int indexCount = 0;
    
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
                tempVertexList.push_back(currentVec);
            }
            
            // texture coord
            else if(strncmp(buffer, "vt", 2) == 0) // is 'vt'
            {
                sscanf(buffer, "vt %f %f", &(currentVec.x), &(currentVec.y));
                currentVec.z = 0.0;
                tempUVCoordList.push_back(currentVec);
            }
            
            // vertex normal
            else if(strncmp(buffer, "vn", 2) == 0) // is 'vn'
            {
                sscanf(buffer, "vn %f %f %f", &(currentVec.x), &(currentVec.y), &(currentVec.z));
                tempVectorNormalList.push_back(currentVec);
            }
            
            // face
            else if(strncmp(buffer, "f ", 2) == 0) // is 'f '
            {
                GLushort vertexIndex[3], uvIndex[3], normalIndex[3];
                sscanf(buffer, "f %hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu",
                                &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                
                tempFace[0] = tempVertexList[vertexIndex[0] - 1];
                tempFace[1] = tempVertexList[vertexIndex[1] - 1];
                tempFace[2] = tempVertexList[vertexIndex[2] - 1];
                
                tempFace[3] = tempUVCoordList[uvIndex[0] - 1];
                tempFace[4] = tempUVCoordList[uvIndex[1] - 1];
                tempFace[5] = tempUVCoordList[uvIndex[2] - 1];
                
                tempFace[6] = tempVectorNormalList[normalIndex[0] - 1];
                tempFace[7] = tempVectorNormalList[normalIndex[1] - 1];
                tempFace[8] = tempVectorNormalList[normalIndex[2] - 1];
                
                for (unsigned int i = 0; i < 3; ++i){
                    objectList->push_back(tempFace[i]);
                    objectList->push_back(tempFace[i+1]);
                    objectList->push_back(tempFace[i+1]);
                }
                
                /*
                bool found = false;
                for (unsigned int i = 0; i < 3; ++i){
                    //Check if the vertices was stored already
                    found = false;
                    for (unsigned short j = 0; j < objectList->size(); ++j){
                        if ((j % 3 == 0)
                            && VVvecComp(tempFace[i], objectList->at(j))
                            && VVvecComp(tempFace[i+3], objectList->at(j+1))
                            && VVvecComp(tempFace[i+6], objectList->at(j+2)) ){
                            objectIndices->push_back(j);
                            //objectIndices->push_back(j+1);
                            //objectIndices->push_back(j+2);
                            found = true;
                            break;
                        }
                    }
                    if (!found){
                        printf("not found one temp and one index. %d", indexCount);
                        objectList->push_back(tempFace[i]);
                        objectIndices->push_back(indexCount);
                        ++indexCount;
                    }
                } // for*/
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