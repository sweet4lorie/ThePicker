//
//  ThePicker
//  Camera.cpp
//
//  handles camera lookAt and projection/modelview matrices
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include <math.h>
#include "Camera.h"

Camera::Camera(Vec3 eyePosition, Vec3 upVector): _eyePosition(eyePosition), _upVector(upVector) {}

void Camera::reset(Vec3 eyePosition, Vec3 upVector){
    _eyePosition = eyePosition;
    _upVector = upVector;
    myLookAt(_eyePosition, _centerPosition, _upVector);
}

void Camera::setupCamera(float const win_aspect)
{
    position = Vec3(_eyePosition._x, _eyePosition._y, _eyePosition._z);
    
    myPerspective(60.0, win_aspect, 0.5, 7.0);
    
    float mv[16];
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, mv);
    myModelView = mv;

    myLookAt(_eyePosition, _centerPosition, _upVector);
}

void Camera::rotate(double x1, double y1, double x2, double y2, double r)
{
    if (x1 != x2 or y1 != y2)
    {
        //double min_x;
        //double max_x;
        std::vector<Vec3> mouse;
        mouse.push_back(Vec3(float(x1), float(y1), float(r)));
        mouse.push_back(Vec3(float(x2), float(y2), float(r)));
        std::vector<Vec3> P;
        
        for (int i = 0; i < 2; i++)
        {
            if (sqrt(mouse[i]._x * mouse[i]._x + mouse[i]._y * mouse[i]._y) < r/sqrt(2))
            {
                P.push_back(Vec3(mouse[i]._x, mouse[i]._y, sqrt(r * r - (mouse[i]._x * mouse[i]._x + mouse[i]._y * mouse[i]._y))).normalize());
            } else
            {
                P.push_back(Vec3(mouse[i]._x, mouse[i]._y, (r * r) / (2 * sqrt(mouse[i]._x * mouse[i]._x + mouse[i]._y * mouse[i]._y))).normalize());
            }
        }
        
        Vec3 axis = P[0] ^ P[1];
        float angle = atan(double(axis.length() / (P[0] * P[1])));
        
        Quat Q(axis, angle);
        Mat4 rm = Q.getRotationMatrix();
        _upVector = rm * _upVector;
        _eyePosition = rm * _eyePosition;
        myLookAt(_eyePosition, _centerPosition, _upVector);
    }
}

ray Camera::getRay(float win_width, float win_height, const float & in_mouseX, const float & in_mouseY)
{
    _mouseX = in_mouseX;
    _mouseY = in_mouseY;
    ray myRay;
    
    float x = (2.0f * _mouseX) / win_width - 1.0f;
    float y = 1.0f - (2.0f * _mouseY) / win_height;
    float z = -1.0f;
    
    Vec3 rayNds = Vec3(x, y, z);
    Vec4 rayClip = {rayNds._x, rayNds._y, z, 1.0};
    
    Vec4 rayEye;
    Vec4 rayWorld;
    
    Mat4 tempInverse = myProjection;
    tempInverse.Inverse();
    rayEye = tempInverse * rayClip;
    
    rayEye._z = z;
    rayEye._w = 0.0;
    
    tempInverse = myModelView;
    tempInverse.Inverse();
    rayWorld = tempInverse * rayEye;
    //vec4 rayWor = getVec4(rayWorld[0], rayWorld[1], rayWorld[2], rayWorld[3]);
    
    // don't forget to normalise the vector at some point
    rayWorld.normalize();
    
    myRay.origin._x = _eyePosition._x;
    myRay.origin._y = _eyePosition._y;
    myRay.origin._z = _eyePosition._z;
    myRay.direction._x = rayWorld._x;
    myRay.direction._y = rayWorld._y;
    myRay.direction._z = rayWorld._z;
    myRay.direction._w = rayWorld._w;
    
    //printf("Ray: \nOrigin(%f, %f, %f), \nDirection(%f, %f, %f)",
    //myRay.origin.x, myRay.origin.y, myRay.origin.z, myRay.direction.x, myRay.direction.y, myRay.direction.z);
    
    return myRay;
}

void Camera::myPerspective( float fovy, const float aspect, float zNear, float zFar)
{
	GLfloat radians_angle = M_PI * fovy / 180.0f;
	GLfloat cot_fov = 1 / tanf(radians_angle / 2.0);
    
    myProjection[0] = cot_fov / aspect;
    myProjection[5] = cot_fov;
    myProjection[10] = (zNear + zFar) / (zNear - zFar);
    myProjection[11] = -1.0f;
    myProjection[14] = (2 * zNear * zFar) / (zNear - zFar);
    myProjection[15] = 0.0f;
}

void Camera::myLookAt(Vec3 eye, Vec3 center, Vec3 up)
{
    /*  gluLookAt( eyeX, eyeY, eyeZ,
       centerX, centerY, centerZ,
       upX, upY, upZ );
    */
    Vec3 f = center + -eye;
    /* double f0 = centerX - eyeX;
    double f1 = centerY - eyeY;
    double f2 = centerZ - eyeZ;*/

    // normalize f
    float magnitudeOfF = sqrt( (f._x * f._x) + (f._y * f._y) + (f._z * f._z) );
    if (magnitudeOfF == 0) // insure it is not 0 or will return nan
    magnitudeOfF = 1;
    Vec3 unitF = { static_cast<float>(f._x/magnitudeOfF), static_cast<float>(f._y/magnitudeOfF), static_cast<float>(f._z/magnitudeOfF) };

    // normalize up vector
    float magnitudeOfUp = sqrt( (up._x * up._x) + (up._y * up._y) + (up._z * up._z));
    if (magnitudeOfUp == 0)
    magnitudeOfUp = 1;
    Vec3 unitUp = { static_cast<float>(up._x / magnitudeOfUp), static_cast<float>(up._y / magnitudeOfUp), static_cast<float>(up._z / magnitudeOfUp) };
    Vec3 s;
    Vec3 u;

    // s = f cross up , u = s cross f
    s = unitF^unitUp;   // vecCrossfUtil(s, unitF, unitUp);
    u = s^unitF;        // vecCrossfUtil(u, s, unitF);
    float M[16] = {s._x, u._x, -unitF._x, 0.0,
                s._y, u._y, -unitF._y, 0.0,
                s._z, u._z, -unitF._z, 0.0,
                0.0, 0.0, 0.0, 1.0 };
    
    Mat4 TempMat;
    TempMat = myModelView * M;   // matMult4fUtil(myModelView, myModelView, M);
    myModelView = TempMat.Translate(-eye);    //matTranslatefUtil(myModelView, -eyeX, -eyeY, -eyeZ);
    
}