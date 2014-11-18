//
//  Transform.h
//  ThePicker
//
//  Created by Emily Chiang on 11/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__Transform__
#define __ThePicker__Transform__

#include <stdio.h>
#include "Utilities.h"

class Transform
{
    public:
        Transform();
        ~Transform();
        Mat4 MV;
    
        void scale(float sAmount);
        void rotate(float rAngle, Vec3 rVector);
        void translate(Vec3 tVector);
        Mat4 getModelMatrix();

    private:
        float _scaleAmount = 1;
        rotation _rotateAmount;
        Vec3 _translateVector = {0.0, 0.0, 0.0};
    
        Mat4 scaleMatrix();
        Mat4 translationMatrix();
};

#endif /* defined(__ThePicker__Transform__) */
