//
//  ObjectHelper.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/28/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "ObjectHelper.h"

void unpackSphere(std::vector<vec> * objectList, std::vector<unsigned short> * objectIndices,
            float radius, unsigned int rings, unsigned int sectors)
{
    std::vector<vec> tempList;
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int ring, sector;

	vec current;
	for (ring = 0; ring < rings; ring++) for (sector = 0; sector < sectors; sector++) {
		float const y = sin(-M_PI_2 + M_PI * ring * R);
		float const x = cos(2 * M_PI * sector * S) * sin(M_PI * ring * R);
		float const z = sin(2 * M_PI * sector * S) * sin(M_PI * ring * R);

        // vertex
		current.x = x * radius;
		current.y = y * radius;
		current.z = z * radius;
        objectList->push_back(current);
        
        // uv
		current.x = sector * S;
		current.y = ring * R;
        current.z = 0.0;
        objectList->push_back(current);

        //normal
		current.x = x;
		current.y = y;
		current.z = z;
        objectList->push_back(current);
        
	}

	for (ring = 0; ring < rings - 1; ring++) for (sector = 0; sector < sectors - 1; sector++) {
		objectIndices->push_back(ring * sectors + sector);
		objectIndices->push_back(ring * sectors + (sector + 1));
		objectIndices->push_back((ring + 1) * sectors + (sector + 1));
		objectIndices->push_back((ring + 1) * sectors + sector);
	}
}