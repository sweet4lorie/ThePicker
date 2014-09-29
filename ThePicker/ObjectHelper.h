//
//  ObjectHelper.h
//  ThePicker
//
//  Created by Emily Chiang on 9/28/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__ObjectHelper__
#define __ThePicker__ObjectHelper__

#include <iostream>
#include "Utilities.h"

void unpackSphere(std::vector<vec> * vertexList, std::vector<unsigned short> * vertexIndices,
            std::vector<vec> * vertexNormalList, std::vector<vec> * textureCoordList,
            float radius, unsigned int rings, unsigned int sectors);

#endif /* defined(__ThePicker__ObjectHelper__) */
