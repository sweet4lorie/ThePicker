//
//  Quat.h
//  ThePicker
//
//  Created by Emily Chiang on 11/9/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__Quat__
#define __ThePicker__Quat__

#include <stdio.h>
#include "Mat4.h"

//#define M_PI 3.14159265358979323846

class Quat
{
    public:
        Mat4 Q;
        Mat4 Q_bar;
    
        Quat(float * axis, float & a);
        Quat(float x, float y, float z, float w);
    
        Quat operator+ (const Quat & q) const;
        Quat operator- (const Quat & q) const;
    
        Mat4 getRotationMatrix();
        Mat4 addRotations(Quat & q1, Quat & q2);
    
    private:
        float _x, _y, _z, _w;
        void QQ_bar();
    
};

#endif /* defined(__ThePicker__Quat__) */
