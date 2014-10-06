//
//  ThePicker
//  Compound.cpp
//
//  Handles calculations to draw from an obj file
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//


#include "Compound.h"

Compound::Compound(const std::string file)
{
    unpack(file);
    initBuffer();
}

void Compound::unpack(const std::string file)
{
    std::vector<GLushort> tempVertexIndices;
    std::vector<GLushort> tempUVIndices;
    std::vector<GLushort> tempNormalIndices;
    std::vector<vec> tempVectorList;
    std::vector<vec> tempNormalList;
    std::vector<vec> tempUVList;
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
                tempVectorList.push_back(currentVec);
            }
            
            // texture coord
            else if(strncmp(buffer, "vt", 2) == 0) // is 'vt'
            {
                sscanf(buffer, "vt %f %f", &(currentVec.x), &(currentVec.y));
                currentVec.z = 0.0;
                tempUVList.push_back(currentVec);
            }
            
            // vertex normal
            else if(strncmp(buffer, "vn", 2) == 0) // is 'vn'
            {
                sscanf(buffer, "vn %f %f %f", &(currentVec.x), &(currentVec.y), &(currentVec.z));
                tempNormalList.push_back(currentVec);
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
                tempVertexIndices.push_back(vertexIndex[0]);
                tempVertexIndices.push_back(vertexIndex[1]);
                tempVertexIndices.push_back(vertexIndex[2]);
                tempUVIndices.push_back(uvIndex[0]);
                tempUVIndices.push_back(uvIndex[1]);
                tempUVIndices.push_back(uvIndex[2]);
                tempNormalIndices.push_back(normalIndex[0]);
                tempNormalIndices.push_back(normalIndex[1]);
                tempNormalIndices.push_back(normalIndex[2]);
            }
        } // while
        for (int i = 0; i < tempVertexIndices.size(); i++)
        {
            if (i % 3 == 0)
            {
                model.vertex.push_back(tempVectorList[tempVertexIndices[i]]);
                model.vertex.push_back(tempVectorList[tempVertexIndices[i+1]]);
                model.vertex.push_back(tempVectorList[tempVertexIndices[i+2]]);
                
                model.normal.push_back(tempNormalList[tempNormalIndices[i]]);
                model.normal.push_back(tempNormalList[tempNormalIndices[i+1]]);
                model.normal.push_back(tempNormalList[tempNormalIndices[i+2]]);
            }
        }
        
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