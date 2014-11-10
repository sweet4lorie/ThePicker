//
//  ThePicker
//  ObjectHit.h
//
//  Header for: Helps handle hit for objects
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#ifndef __ThePicker__ObjectHit__
#define __ThePicker__ObjectHit__

#include <iostream>
#include "Utilities.h"

bool checkView(modelPackage * model, float (& pm)[16], Mat4 & mv);
float pointOnPlane (plane plane, Vec3 point);
bool hitBox(modelPackage * model, Mat4 * MV, ray & myRay);

#endif /* defined(__ThePicker__ObjectHit__) */
