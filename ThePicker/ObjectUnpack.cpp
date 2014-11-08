//
//  ThePicker
//  ObjectUnpack.cpp
//
//  Helps unpack vertices and normals for objects
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "ObjectUnpack.h"

void unpackBox(modelPackage * model, Vec3 min, Vec3 max)
{
    std::vector<Vec3> tempList;
    tempList.push_back(Vec3(min._x, min._y, min._z)); // 0
    tempList.push_back(Vec3(min._x, min._y, max._z)); // 1
    tempList.push_back(Vec3(min._x, max._y, max._z)); // 2
    tempList.push_back(Vec3(max._x, max._y, min._z)); // 3
    tempList.push_back(Vec3(min._x, max._y, min._z)); // 4
    tempList.push_back(Vec3(max._x, min._y, max._z)); // 5
    tempList.push_back(Vec3(max._x, min._y, min._z)); // 6
    tempList.push_back(Vec3(max._x, max._y, max._z)); // 7
    
    int list [] = { 1, 2, 3,
                    3, 0, 4,
                    5, 0, 6,
                    3, 6, 0,
                    0, 2, 4,
                    5, 1, 0,
                    2, 1, 5,
                    7, 6, 3,
                    6, 7, 5,
                    7, 3, 4,
                    7, 4, 2,
                    7, 2, 5 };
    
    for (int i = 0; i < 36; i++)
    {
        model->vertex.push_back(tempList[list[i]]);
    }
    
    
    
    
}


void unpackCompound(modelPackage * model, const std::string file)
{
    std::vector<unsigned short> tempVertexIndices;
    std::vector<unsigned short> tempUVIndices;
    std::vector<unsigned short> tempNormalIndices;
    std::vector<Vec3> tempVertextList;
    std::vector<Vec3> tempNormalList;
    std::vector<Vec3> tempUVList;
    char buffer [255];
    
    // for file
    std::ifstream inFile;
    inFile.open(file);
    
    if (inFile.is_open())
    {
        // current vec
        Vec3 currentVec;
        
        while(!inFile.eof()){
            inFile.getline(buffer, sizeof(buffer), '\n');
            
            // vertex
            if(strncmp(buffer, "v ", 2) == 0) // is 'v '
            {
                sscanf(buffer, "v %f %f %f", &(currentVec._x), &(currentVec._y), &(currentVec._z));
                tempVertextList.push_back(currentVec);
            }
            
            // texture coord
            else if(strncmp(buffer, "vt", 2) == 0) // is 'vt'
            {
                sscanf(buffer, "vt %f %f", &(currentVec._x), &(currentVec._y));
                currentVec._z = 0.0;
                tempUVList.push_back(currentVec);
            }
            
            // vertex normal
            else if(strncmp(buffer, "vn", 2) == 0) // is 'vn'
            {
                sscanf(buffer, "vn %f %f %f", &(currentVec._x), &(currentVec._y), &(currentVec._z));
                tempNormalList.push_back(currentVec);
            }
            
            // face
            else if(strncmp(buffer, "f ", 2) == 0) // is 'f '
            {
                unsigned short vertexIndex[3], uvIndex[3], normalIndex[3];
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
            model->vertex.push_back(tempVertextList[tempVertexIndices[i]-1]);
            model->normal.push_back(tempNormalList[tempNormalIndices[i]-1]);
        }
        
    } // if file
    
    inFile.close();
    //std::cout << "DONE";
}

/*
//Create your three vertices
for (int i = 0; i < 3; i++)
{
    VertexData vd;
    vd.vertex = tempVertextList[vertexIndex[i]];
    //vd.texture = tempUVList[uvIndex[i]];
    vd.normal = tempNormalList[normalIndex[i]];
    model.push_back(&vd);
}
*/


/*
void unpackSphere(std::vector<VertexData*> & model, float radius, unsigned int rings, unsigned int sectors)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int ring, sector;
    
    std::vector<Vec3> tempUVList;
    std::vector<Vec3> tempVertexList;
    std::vector<Vec3> tempVertexNormalList;
    
	Vec3 current;
	for (ring = 0; ring < rings; ring++) for (sector = 0; sector < sectors; sector++) {
		float const y = sin(-M_PI_2 + M_PI * ring * R);
		float const x = cos(2 * M_PI * sector * S) * sin(M_PI * ring * R);
		float const z = sin(2 * M_PI * sector * S) * sin(M_PI * ring * R);

		current._x = sector * S;
		current._y = ring * R;
        current._z = 0.0;
        tempUVList.push_back(current);

		current._x = x * radius;
		current._y = y * radius;
		current._z = z * radius;
        tempVertexList.push_back(current);

		current._x = x;
		current._y = y;
		current._z = z;
        tempVertexNormalList.push_back(current);
	}

	for (ring = 0; ring < rings - 1; ring++) for (sector = 0; sector < sectors - 1; sector++) {
        int a = ring * sectors + sector;
        int b = ring * sectors + (sector + 1);
        int c = (ring + 1) * sectors + (sector + 1);
        int d = (ring + 1) * sectors + sector;
        
		model->vertex.push_back(tempVertexList[a]);
		model->vertex.push_back(tempVertexList[b]);
		model->vertex.push_back(tempVertexList[c]);
		model->vertex.push_back(tempVertexList[d]);
        
        model->normal.push_back(tempVertexNormalList[a]);
		model->normal.push_back(tempVertexNormalList[b]);
		model->normal.push_back(tempVertexNormalList[c]);
		model->normal.push_back(tempVertexNormalList[d]);
	}
}
*/