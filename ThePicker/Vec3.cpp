//
//  Vec3.cpp
//  ThePicker
//
//  Created by Emily Chiang on 11/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#include <math.h>
#include "Vec3.h"

// constructors

Vec3::Vec3(void): _x(0.0), _y(0.0), _z(0.0) {}

Vec3::Vec3(float a): _x(a), _y(a), _z(a) {}

Vec3::Vec3(float x, float y, float z): _x(x), _y(y), _z(z) {}

Vec3::Vec3(const Vec3 & v): _x(v._x), _y(v._y), _z(v._z){}

// destructor

Vec3::~Vec3(void) {}

// overload operators

Vec3 Vec3::operator= (const Vec3 & rhs)
{
	if(this == &rhs)
		return *this;

	_x = rhs._x; 
	_y = rhs._y; 
	_z = rhs._z;

	return *this;
}

// overload operators

Vec3 Vec3::operator- (void) const
{
    return Vec3(-_x,-_y,-_z);
}


Vec3 Vec3::operator* (const float a) const
{
    return Vec3( _x * a, _y * a, _z * a);
}

Vec3 Vec3::operator/ (const float a) const
{
    return Vec3(_x / a, _y / a, _z / a);
}

Vec3 Vec3::operator+ (const Vec3 & v) const
{
    return (Vec3(_x + v._x, _y + v._y, _z + v._z));
}

Vec3 & Vec3::operator+= (const Vec3 & v)
{
    _x += v._x; _y += v._y; _z += v._z;
	return (*this);
}

bool Vec3::operator== (const Vec3 & v) const
{
    return _x == v._x && _y == v._y && _z == v._z;
}

// cross
Vec3 Vec3::operator^ (const Vec3 & v) const
{
	return (Vec3(_y * v._z - _z * v._y,
					_z * v._x - _x * v._z, 
					_x * v._y - _y * v._x));
}

// functions

Vec3 & Vec3::normalize(void)
{
    float len = sqrt(_x * _x + _y * _y + _z * _z);

	_x /= len;
	_y /= len;
	_z /= len;
	return *this;
}

Vec3 Vec3::length(void)
{
    return  sqrt(_x * _x + _y * _y + _z * _z) ;
}

// multiplication with mat4 * vec3

Vec3 operator* (const Mat4 & mat, const Vec3 & v)
{
	return (Vec3(mat[0] * v._x + mat[1] * v._y + mat[2] * v._z,
					 mat[4] * v._x + mat[5] * v._y + mat[6] * v._z,
					 mat[8] * v._x + mat[9] * v._y + mat[10] * v._z));
}
