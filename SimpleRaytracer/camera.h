#pragma once
#ifndef  CAMERAH
#define CAMERAH
#include "ray.h"
class camera
{
public:
	camera();
	~camera();
	ray get_ray(float u, float v) {
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;

};

#endif // ! CAMERAH

