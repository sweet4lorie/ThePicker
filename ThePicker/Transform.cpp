//
//  Transform.cpp
//  ThePicker
//
//  Created by Emily Chiang on 11/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include "Transform.h"

/*
scale
rotation
translate
*/
Transform::Transform()
{
}

void Transform::scale(float sAmount)
{
    _scaleAmount *= sAmount;
}

void Transform::rotate(float rAngle, Vec3 rVector)
{
    _rotateAmount.vector = rVector;
    _rotateAmount.angle = rAngle;
}

void Transform::translate(Vec3 tVector)
{
    _translateVector._x += tVector._x;
    _translateVector._y += tVector._y;
    _translateVector._z += tVector._z;
}

// order: translate, rotate, scale

Mat4 Transform::getModelMatrix()
{
    MV = translationMatrix() * scaleMatrix();
    return MV;
}

Mat4 Transform::scaleMatrix()
{
    Mat4 sM;
    sM[0] = _scaleAmount;
    sM[5] = _scaleAmount;
    sM[10] = _scaleAmount;
    return sM;
}

/*
Mat4 Transform::rotationMatrix()
{
    
}
*/

Mat4 Transform::translationMatrix()
{
    Mat4 tM;
    tM[12] = _translateVector._x;
    tM[13] = _translateVector._y;
    tM[14] = _translateVector._z;
    return tM;
}

Transform::~Transform()
{
}
