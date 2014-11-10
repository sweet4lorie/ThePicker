//
//  ThePicker
//  ObjectUnpack.h
//
//  Header for: Helps unpack vertices and normals for objects
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__ObjectHelper__
#define __ThePicker__ObjectHelper__

#include <iostream>
#include <fstream>
#include "Utilities.h"

bool cullBox(modelPackage * model, float (& projectionMatrix)[16]);
void unpackBox(modelPackage * model, Vec3 min, Vec3 max);
void unpackCompound(modelPackage * model, const std::string file);
void unpackSphere(modelPackage * model, float radius, unsigned int rings, unsigned int sectors);

#endif /* defined(__ThePicker__ObjectHelper__) */
