//
//  ThePicker
//  BoundingObject.cpp
//
//  Handles calculations to draw sphere bounding
//  appropriately over the object
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "BoundingObject.h"

Bounding::Bounding()
{
}

void Bounding::setValues(modelPackage * in_objModel, modelPackage * in_model)
{
    _objModel = in_objModel;
    _model = in_model;
    calcMinMaxCenter(_objModel, &_min, &_max, &_center, &_maxValue);
}

void Bounding::box()
{
    unpackBox(_model, _min, _max);
}

Bounding::~Bounding()
{
}
