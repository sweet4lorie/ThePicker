//
//  Mat4.h
//  ThePicker
//
//  Created by Emily Chiang on 11/3/14.
//  Copyright (c) 2014 Emily Chiang. All rights reserved.
//

#ifndef __ThePicker__Mat4__
#define __ThePicker__Mat4__

#include <stdio.h>
#include <iostream>

class Vec3;
//This is a 4X4 column major Matrix
//All calculations will be done
class Mat4
{
    public:

        //Constructors
        Mat4();
        Mat4(const float m[16]);
        Mat4(const Mat4 & m);
        Mat4(const float s);

        //Operator Functions
        Mat4& operator= (const Mat4 & m);
        
        Mat4 operator+ (const Mat4 & m) const;
        Mat4 operator+ (const float m[16]) const;
        
        Mat4 operator- (const Mat4 & m) const;
        Mat4 operator- (const float m[16]) const;

        Mat4 operator* (const Mat4 & m) const;
        Mat4 operator* (const float m[16]) const;
        
        Mat4 operator* (const float & s) const;
        Mat4 operator/ (const float & s) const;

        Mat4& operator+= (const Mat4 & m);
        Mat4& operator+= (const float m[16]);
        Mat4& operator-= (const Mat4 & m);
        Mat4& operator-= (const float m[16]);

        Mat4& operator*= (const Mat4 & m);
        Mat4& operator*= (const float m[16]);

        Mat4& operator*= (const float & s);
        Mat4& operator/= (const float & s);

        bool operator==(const Mat4& m) const;
        bool operator== (const float  m[16]) const;

        float & operator[](const int & i);

        const float & operator[](const int & i) const;

        //Built in Functions
        float Determinant() const;
        Mat4 Get_Inverse() const;
        void Inverse();
        void Transpose();
        Mat4 Get_Transpose() const;

        static Mat4 Translate(const Vec3 & v);
        static Mat4 Translate(const float & x, const float & y, const float & z);

        //TODO: FIX ROTATION	static Mat4 Rotate(const Vector3D& angles);

        static Mat4 Scale(const Vec3 & s);
        static Mat4 Scale(const float & s);
        static Mat4 Scale(const float & x, const float & y, const float & z);

        ~Mat4();

    private:

        float _m[16];

        float * Get_Minor_Matrix(int column, int row) const;
};

float Det3x3(const float m[9]);

#endif