//
//  ThePicker
//  ObjectHit.cpp
//
//  Helps handle hit for objects
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "ObjectHit.h"

bool hitBox(modelPackage * model, Mat4 * MV, ray & r){

    Vec3 min;
    Vec3 max;
    Vec3 center;
    float maxValue;
    
    calcMinMaxCenter(model, &min, &max, &center, &maxValue);
    
	// r.dir is unit direction vector of ray
	
	//Update the min a max values to transform them to appropiate locations
	Vec4 minValues = Vec4(min._x, min._y, min._z, 1.0f) * *MV;
	Vec4 maxValues = Vec4(max._x, max._y, max._z, 1.0f) * *MV;

	Vec3 dirfrac;

	dirfrac._x = 1.0f / r.direction._x;
	dirfrac._y = 1.0f / r.direction._y;
	dirfrac._z = 1.0f / r.direction._z;

	float t1 = (minValues._x - r.origin._x) * dirfrac._x;
	float t2 = (maxValues._x - r.origin._x) * dirfrac._x;
	float t3 = (minValues._y - r.origin._y) * dirfrac._y;
	float t4 = (maxValues._y - r.origin._y) * dirfrac._y;
	float t5 = (minValues._z - r.origin._z) * dirfrac._z;
	float t6 = (maxValues._z - r.origin._z) * dirfrac._z;

	//find the largest lower bound
	float tmin = getMax(getMax(getMin(t1, t2), getMin(t3, t4)), getMin(t5, t6));

	//find the smallest upper bound
	float tmax = getMin(getMin(getMax(t1, t2), getMax(t3, t4)), getMax(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the AABB is behind the camera
	if (tmax < 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}
    
	//Intersect
	return true;
}