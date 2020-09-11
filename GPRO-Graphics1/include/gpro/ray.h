#pragma once
/*
 Author:				Cameron-Murphy
 Class:					GPR-200-01
 Assignment:			Lab 1: Hello Modern Graphics
 Due Date:              9/11/20
*/

#include <iostream>
#include "gpro-math/gproVector.h"

using namespace std;

//Class for casting a ray
class ray
{
public:
	ray() {} //Default constructor
	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {} //Constructor (takes origin and direction of ray)
	point3 origin() const { return orig; } //Returns origin
	vec3 direction() const { return dir; } //Returns direction

	//Points at specified point
	point3 at(float t) const
	{
		return orig + t * dir;
	}

private:
	//Member variables
	point3 orig;
	vec3 dir;
};