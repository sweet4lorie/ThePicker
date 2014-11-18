//
//  ThePicker
//  Quat.cpp
//
//  Quaturnian class
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include <math.h>
#include "Quat.h"

Quat::Quat(Vec3 & axis, float & a)
{
    float a_rad = a * (M_PI/180);
    _x = axis._x * sin(a_rad/2);
    _y = axis._y * sin(a_rad/2);
    _z = axis._z * sin(a_rad/2);
    _w = cos(a_rad/2);
    QQ_bar();
}

Quat::Quat(float x, float y, float z, float w): _x(x), _y(y), _z(z), _w(w) {}


void Quat::QQ_bar()
{
    // reminder: column major
    float tempQ[16] = {
                    _w, _z, -_y, -_x,
                    -_z, _w, _x, -_y,
                    _y, -_x, _w, -_z,
                    _x, _y, _z, _w };
    Q = tempQ;
    float tempQ_bar [16] = {
                    _w, _z, -_y, _x,
                    -_z, _w, _x, _y,
                    _y, -_x, _w, -_z,
                    -_x, -_y, -_z, _w };
    Q_bar = tempQ_bar;
}

Quat Quat::operator+ (const Quat & q) const
{
    return Quat(_x + q._x, _y + q._y, _z + q._z, _w + q._w);
}

Quat Quat::operator- (const Quat & q) const
{
    return Quat(_x - q._x, _y - q._y, _z - q._z, _w - q._w);
}


Mat4 Quat::getRotationMatrix()
{
    return Q_bar * Q;
}

Mat4 addRotations(Quat & q1, Quat & q2)
{
    return (q2.Q_bar * q1.Q_bar) * (q2.Q * q1.Q);
}