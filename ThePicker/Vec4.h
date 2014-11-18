//
//  ThePicker
//  Vec4.h
//
//  Header for: 4D Vector class
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__Vec4__
#define __ThePicker__Vec4__

#include <stdio.h>
#include "Mat4.h"

class Vec4{
    public:
        // constructors
        Vec4(void);
        Vec4(float a);
        Vec4(float x, float y, float z, float w);
        Vec4(const Vec4 & v);
    
        // destructor
        ~Vec4(void);
    
        // overload operators
        Vec4 operator= (const Vec4 & rhs);
        Vec4 operator- (void) const;
        Vec4 operator* (const float a) const;
        Vec4 operator/ (const float a) const;
        Vec4 operator+ (const Vec4 & v) const;
        Vec4 & operator+= (const Vec4 & v);
        bool operator== (const Vec4 & v) const;
    
        Vec4 operator* (const Mat4& m) const;
    
        // normalize
        Vec4 & normalize(void);
        Vec4 length(void);
    
        float _x, _y, _z, _w;
};

// multiplication by a matrix on the left
Vec4 operator* (const Mat4 & mat, const Vec4 & v);


#endif /* defined(__ThePicker__Vec4__) */
