//
//  Vec4.cpp
//  ThePicker
//
//  Created by Emily Chiang on 11/4/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

//
//  Vec4.cpp
//  ThePicker
//
//  Created by Emily Chiang on 11/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include <math.h>
#include "Vec4.h"

// constructors

Vec4::Vec4(void): _x(0.0), _y(0.0), _z(0.0), _w(0.0) {}

Vec4::Vec4(float a): _x(a), _y(a), _z(a), _w(a) {}

Vec4::Vec4(float x, float y, float z, float w): _x(x), _y(y), _z(z), _w(w) {}

Vec4::Vec4(const Vec4 & v): _x(v._x), _y(v._y), _z(v._z), _w(v._w){}

// destructor

Vec4::~Vec4(void) {}

// overload operators

Vec4 Vec4::operator= (const Vec4 & rhs)
{
	if(this == &rhs)
		return *this;

	_x = rhs._x; 
	_y = rhs._y; 
	_z = rhs._z;
    _w = rhs._w;

	return *this;
}

// overload operators

Vec4 Vec4::operator- (void) const
{
    return Vec4(-_x, -_y, -_z, -_w);
}


Vec4 Vec4::operator* (const float a) const
{
    return Vec4( _x * a, _y * a, _z * a, _w * a);
}

Vec4 Vec4::operator/ (const float a) const
{
    return Vec4(_x / a, _y / a, _z / a, _w / a);
}

Vec4 Vec4::operator+ (const Vec4 & v) const
{
    return (Vec4(_x + v._x, _y + v._y, _z + v._z, _w + v._w));
}

Vec4 & Vec4::operator+= (const Vec4 & v)
{
    _x += v._x; _y += v._y; _z += v._z; _w += v._w;
	return (*this);
}

bool Vec4::operator== (const Vec4 & v) const
{
    return _x == v._x && _y == v._y && _z == v._z && _w == v._w;
}


// Matrix Multiplcation product
Vec4 Vec4::operator* (const Mat4& mat) const{
	return (Vec4(mat[0] * _x + mat[4] * _y + mat[8] * _z + mat[12] * _w,
			mat[1] * _x + mat[5] * _y + mat[9] * _z + mat[13] * _w,
			mat[2] * _x + mat[6] * _y + mat[10] * _z + mat[14] * _w,
			mat[3] * _x + mat[7] * _y + mat[11] * _z + mat[15] * _w));
}

// functions

Vec4 & Vec4::normalize(void)
{
    float len = sqrt(_x * _x + _y * _y + _z * _z + _w * _w);

	_x /= len;
	_y /= len;
	_z /= len;
    _w /= len;
	return *this;
}

Vec4 Vec4::length(void)
{
    return  sqrt(_x * _x + _y * _y + _z * _z + _w * _w) ;
}

// multiplication with mat4 * Vec4

Vec4 operator* (const Mat4 & mat, const Vec4 & v)
{
	return (Vec4(mat[0] * v._x + mat[1] * v._y + mat[2] * v._z + mat[3] * v._w,
					 mat[4] * v._x + mat[5] * v._y + mat[6] * v._z + mat[7] * v._w,
					 mat[8] * v._x + mat[9] * v._y + mat[10] * v._z + mat[11] * v._w,
					 mat[12] * v._x + mat[13] * v._y + mat[14] * v._z + mat[15] * v._w));
}
