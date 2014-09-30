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
    
        void setValues(modelPackage * in_objModel, modelPackage * in_model);
        void sphere();
        //void cube();
    
        bool hitSphere();
    
    private:
        modelPackage * model;
        modelPackage * objModel;
};


#endif /* defined(__ThePicker__BoundingObject__) */
