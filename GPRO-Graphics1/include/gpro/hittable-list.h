#pragma once
/*
 Author:				Cameron-Murphy
 Class:					GPR-200-01
 Assignment:			Lab 1: Hello Modern Graphics
 Due Date:              9/11/20
*/

#include <vector>
#include <iostream>
#include "ray.h"
#include <memory>

using namespace std;

//Structure for taking note of raycast hits
struct hit_record
{
	point3 p;
	vec3 normal;
	float t;
	bool front_face;

	//Determine front and back faces
	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

//Base class for any hittable objects (spheres)
class hittable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0; //Base function for hit
};

//Class that stores hittable objects
class hittable_list : public hittable
{
public:
	hittable_list() { } //Default constructor
	hittable_list(shared_ptr<hittable> object) { add(object); } //Constructor automatically adds object

	void clear() { objects.clear(); } //Clear all objects off of the list
	void add(shared_ptr<hittable> object) { objects.push_back(object); } //Adds passed object into the list

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const; //Determine what is hit from all in the list

public:
	vector<shared_ptr<hittable>> objects; //Vector that stores all of the hittable objects
};

//Determines what is hit from the list
bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const shared_ptr<hittable>& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}