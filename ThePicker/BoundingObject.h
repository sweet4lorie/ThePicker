//
//  BoundingObject.h
//  ThePicker
//
//  Created by Emily Chiang on 9/28/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__BoundingObject__
#define __ThePicker__BoundingObject__

#include <iostream>
#include "Utilities.h"
#include "ObjectHelper.h"

class Bounding
{
    public:
        Bounding();
        ~Bounding();
    
        void setValues(std::vector<vec> * in_vertexList, std::vector<unsigned short> * in_vertexIndices,
                std::vector<vec> * in_vertexNormalList, std::vector<vec> * in_textureCoordList);
        void sphere(float & maxValue, vec & center);
        //void cube();
    
        bool hitSphere();
    
    private:
        std::vector<vec> * vertexList;
        std::vector<unsigned short> * vertexIndices;
        std::vector<vec> * vertexNormalList;
        std::vector<vec> * textureCoordList;
};


#endif /* defined(__ThePicker__BoundingObject__) */
