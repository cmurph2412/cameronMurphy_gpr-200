#pragma once
/*
 Author:				Cameron-Murphy
 Class:					GPR-200-01
 Assignment:			Lab 1: Hello Modern Graphics
 Due Date:              9/11/20
*/

#include "ray.h"
#include "gpro-math/gproVector.h"
#include "hittable-list.h"

//Class for placing a sphere in the world
class sphere : public hittable
{
public:
	sphere() {} //Default constructor
	sphere(point3 cen, float r) : center(cen), radius(r) {}; //Contructor takes the center location and the radius

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override; //Definition for hit function

private:
	//Member variables
	point3 center;
	float radius;
};

//Detection for if the sphere is hit
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared();
	float half_b = dot(oc, r.direction());
	float c = oc.length_squared() - radius * radius;
	float discriminant = half_b * half_b - a * c;

	if (discriminant > 0)
	{
		float root = sqrt(discriminant);

		float temp = (-half_b - root) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			return true;
		}

		temp = (-half_b + root) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			return true;
		}
	}

	return false;
}
