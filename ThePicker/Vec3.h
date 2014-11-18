//
//  ThePicker
//  Vec3.h
//
//  Header for: 3D Vector class
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Vec3__
#define __ThePicker__Vec3__

#include <stdio.h>
#include "Mat4.h"

class Vec3{
    public:
        // constructors
        Vec3(void);
        Vec3(float a);
        Vec3(float x, float y, float z);
        Vec3(const Vec3 & v);
    
        // destructor
        ~Vec3(void);
    
        // overload operators
        Vec3 operator= (const Vec3 & rhs);
        Vec3 operator- (void) const;
        Vec3 operator* (const float a) const;
        float operator* (const Vec3& b) const;
        Vec3 operator/ (const float a) const;
        Vec3 operator+ (const Vec3 & v) const;
        Vec3 & operator+= (const Vec3 & v);
        bool operator== (const Vec3 & v) const;
        // cross
        Vec3 operator^ (const Vec3 & v) const;
    
        // normalize
        Vec3 & normalize(void);
        float length(void);
    
        float _x, _y, _z;
};

// multiplication by a matrix on the left
Vec3 operator* (const Mat4 & mat, const Vec3 & v);

#endif /* defined(__ThePicker__Vec3__) */
