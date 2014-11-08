//
//  ThePicker
//  BoundingObject.h
//
//  Header for: Handles calculations to draw sphere bounding
//  appropriately over the object
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//


#ifndef __ThePicker__BoundingObject__
#define __ThePicker__BoundingObject__

#include <iostream>
#include "Utilities.h"
#include "ObjectUnpack.h"

class Bounding
{
    public:
        Bounding();
        ~Bounding();
    
        void calcValues();
        void setValues(modelPackage * in_objModel, modelPackage * in_model);
        void box();
    
    private:
        modelPackage * _model;
        modelPackage * _objModel;
        Vec3 _min;
        Vec3 _max;
        float _maxValue = 0;
        Vec3 _center;
};


#endif /* defined(__ThePicker__BoundingObject__) */
