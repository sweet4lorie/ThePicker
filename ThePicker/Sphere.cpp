//
//  Sphere.cpp
//  ThePicker
//
//  Created by Emily Chiang on 9/21/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//


#include "Sphere.h"

Sphere::Sphere(float radius, unsigned int rings, unsigned int sectors)
{
    type = "quad";
    bound = "sphere";
    unpackSphere(objectList, objectIndices, radius, rings, sectors);
    initBuffer();
}

void Sphere::hit()
{
    std::cout << "Check Hit" << std::endl;
}


Sphere::~Sphere()
{
}


    /*
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int ring, sector;

	//vertexList.resize(rings * sectors);
	//normalList.resize(rings * sectors);
	//texureCoordList.resize(rings * sectors);
	vec current;
	for (ring = 0; ring < rings; ring++) for (sector = 0; sector < sectors; sector++) {
		float const y = sin(-M_PI_2 + M_PI * ring * R);
		float const x = cos(2 * M_PI * sector * S) * sin(M_PI * ring * R);
		float const z = sin(2 * M_PI * sector * S) * sin(M_PI * ring * R);

		current.x = sector * S;
		current.y = ring * R;
        current.z = 0.0;
        texureCoordList.push_back(current);

		current.x = x * radius;
		current.y = y * radius;
		current.z = z * radius;
        vertexList.push_back(current);

		current.x = x;
		current.y = y;
		current.z = z;
        vertexNormalList.push_back(current);
	}

	//vertexIndices.resize(rings * sectors * 4);
	//std::vector<GLushort>::iterator index = vertexIndices.begin();
    
	for (ring = 0; ring < rings - 1; ring++) for (sector = 0; sector < sectors - 1; sector++) {
		vertexIndices.push_back(ring * sectors + sector);
		vertexIndices.push_back(ring * sectors + (sector + 1));
		vertexIndices.push_back((ring + 1) * sectors + (sector + 1));
		vertexIndices.push_back((ring + 1) * sectors + sector);
	}
    
    std::cout << "vextList COUNT: " << vertexList.size() << std::endl;
    for(int i = 0; i < vertexList.size(); i++)
    {
        std::cout << "vertexList: " << vertexList[i].x << ", " << vertexList[i].y << ", " << vertexList[i].z << std::endl;
    }
    std::cout << "vertexIndices COUNT: " << vertexIndices.size()/4 << std::endl;
    
    for(int i = 0; i < vertexIndices.size(); i++)
    {
        std::cout << "vertexIndices: " << vertexIndices[i] << std::endl;
    }
    std::cout << vertexList[0].x << " " << vertexList[0].y << " " << vertexList[0].z << std::endl;
    std::cout << vertexList[1].x << " " << vertexList[1].y << " " << vertexList[1].z << std::endl;
    std::cout << vertexList[11].x << " " << vertexList[11].y << " " << vertexList[11].z << std::endl;
    std::cout << vertexList[10].x << " " << vertexList[10].y << " " << vertexList[10].z << std::endl;
    */
/*
    // scale, rotate, translate
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, z);
    
    //This is where you put your affine transformation matrix into the stack
    
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor3f(1.0, 0.0, 0.0);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
	glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
	glPopMatrix();
*/