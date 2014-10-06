//
//  ThePicker
//  ObjectHelper.cpp
//
//  Helps draws common objects like the sphere
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "ObjectHelper.h"

void unpackSphere(modelPackage * model, float radius, unsigned int rings, unsigned int sectors)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int ring, sector;
    
    std::vector<vec> tempUVList;
    std::vector<vec> tempVertexList;
    std::vector<vec> tempVertexNormalList;
    
	vec current;
	for (ring = 0; ring < rings; ring++) for (sector = 0; sector < sectors; sector++) {
		float const y = sin(-M_PI_2 + M_PI * ring * R);
		float const x = cos(2 * M_PI * sector * S) * sin(M_PI * ring * R);
		float const z = sin(2 * M_PI * sector * S) * sin(M_PI * ring * R);

		current.x = sector * S;
		current.y = ring * R;
        current.z = 0.0;
        tempUVList.push_back(current);

		current.x = x * radius;
		current.y = y * radius;
		current.z = z * radius;
        tempVertexList.push_back(current);

		current.x = x;
		current.y = y;
		current.z = z;
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