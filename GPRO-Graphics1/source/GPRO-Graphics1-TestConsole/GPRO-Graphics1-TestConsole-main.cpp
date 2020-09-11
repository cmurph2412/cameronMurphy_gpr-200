/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: Cameron Murphy
	Modified because: Worked on implementing assignment 1 into main, as well as the write-color and ray-color functions.
*/


#include <stdio.h>
#include <stdlib.h>

#include "gpro/gpro-math/gproVector.h"
#include "gpro/sphere.h"
#include "gpro/hittable-list.h"
#include "gpro/ray.h"

void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vec3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus
}

#ifdef __cplusplus
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#endif


//Writes the color to the file based on the given value
void writeColor(ofstream &out, color pixel_color)
{
	out << static_cast<int>(255.999 * pixel_color.x) << ' ' << static_cast<int>(255.999 * pixel_color.y) << ' ' << static_cast<int>(255.999 * pixel_color.z) << endl;
}

//Defining infinity
const float infinity = numeric_limits<float>::infinity();

//Determines the color using a ray
color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;

	//If it hits an object sets it to the objects color
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5f * (rec.normal + color(1, 1, 1));
	}
	
	//Returns color for background (did not hit any objects)
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

int main(int const argc, char const* const argv[])
{
	//Define image sizes as constants
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//Define objects in the world
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5f));
	world.add(make_shared<sphere>(point3(0, -100.5f, -1), 100.0f));

	//Setting up camera
	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0f;
	vec3 origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//Set up output stream
	ofstream output;
	output.open("image.ppm");

	//initialize height and width
	output << "P3\n" << image_width << ' ' << image_height << "\n255\n"; 

	//Render
	for (int j = image_height - 1; j >= 0; --j)
	{
		for (int i = 0; i < image_width; ++i)
		{
			//Casts ray into world
			float u = float(i) / (image_width - 1);
			float v = float(j) / (image_height - 1);
			ray r(origin, lower_left_corner + horizontal * u + vertical * v - origin);

			//Determines the color of the pixel and changes it in the file
			color pixelColor = ray_color(r, world);
			writeColor(output, pixelColor);
		}
	}

	//Closes output file and program
	output.close();
	cout << "Done" << endl;
	return 0;
	printf("\n\n");
	system("pause");
}
