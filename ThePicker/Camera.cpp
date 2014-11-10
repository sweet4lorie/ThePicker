//
//  ThePicker
//  Camera.cpp
//
//  handles camera lookAt and projection/modelview matrices
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Camera.h"

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

/*
void Camera::setMouseLocation(const float & in_mouseX, const float & in_mouseY)
{
    _mouseX = in_mouseX;
    _mouseY = in_mouseY;
}
*/

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
/*
// rotatas camera to the left and right
void rotateCameraLeft(float degrees, float *eyePosition, float *centerPosition, float *upVector)
{
    float tempMatrix[16];
    float tempEyePosition[3];

    // rotate around the up vector
    matRotatefUtil(tempMatrix, degrees, upVector[0], upVector[1], upVector[2]);

    // get new eye position
    matMultVec4fUtil( tempEyePosition, eyePosition, tempMatrix );
    eyePosition[0] = tempEyePosition[0];
    eyePosition[1] = tempEyePosition[1];
    eyePosition[2] = tempEyePosition[2];
}

// rotates camera up and down
void rotateCameraUp(float degrees, float *eyePosition, float *centerPosition, float *upVector){
    // get right first
    // rotate around x to get the new eye position
    // rotation matrix with eye position
    // gaze = center - eye
    // find new Up = R x G

    float rotationMatrix[16];
    float gazeVector[3];
    float rightVector[3];
    float tempEyePosition[3];
    float tempUpVector[3];

    // center - eye
    gazeVector[0] = centerPosition[0] - eyePosition[0];
    gazeVector[1] = centerPosition[1] - eyePosition[1];
    gazeVector[2] = centerPosition[2] - eyePosition[2];

    // normalize gaze
    float magnitudeOfGaze = sqrtf(powf(gazeVector[0],2)+ powf(gazeVector[1],2) + powf(gazeVector[2],2));
    gazeVector[0] = gazeVector[0]/magnitudeOfGaze;
    gazeVector[1] = gazeVector[1]/magnitudeOfGaze;
    gazeVector[2] = gazeVector[2]/magnitudeOfGaze;

    // right = gaze x up
    vecCrossfUtil(rightVector, gazeVector, upVector);

    // obtain rotation matrix on right vector
    matRotatefUtil(rotationMatrix, degrees, rightVector[0], rightVector[1], rightVector[2]);

    // get new eye position
    matMultVec4fUtil( tempEyePosition, eyePosition, rotationMatrix );
    vecCrossfUtil(rightVector, gazeVector, upVector); // the right vector is null so need value again
    eyePosition[0] = tempEyePosition[0];
    eyePosition[1] = tempEyePosition[1];
    eyePosition[2] = tempEyePosition[2];

    // based on new eye and center, get new gaze
    gazeVector[0] = centerPosition[0] - eyePosition[0];
    gazeVector[1] = centerPosition[1] - eyePosition[1];
    gazeVector[2] = centerPosition[2] - eyePosition[2];

    // normalize new gaze
    magnitudeOfGaze = sqrtf(powf(gazeVector[0],2)+ powf(gazeVector[1],2) + powf(gazeVector[2],2));
    gazeVector[0] = gazeVector[0]/magnitudeOfGaze;
    gazeVector[1] = gazeVector[1]/magnitudeOfGaze;
    gazeVector[2] = gazeVector[2]/magnitudeOfGaze;

    // get new up vector
    vecCrossfUtil(tempUpVector, rightVector, gazeVector);
    upVector[0] = tempUpVector[0];
    upVector[1] = tempUpVector[1];
    upVector[2] = tempUpVector[2];

    //printf("right vector: %f, %f, %f\n", rightVector[0], rightVector[1], rightVector[2]);
}*/
