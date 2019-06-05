#pragma once
#ifndef  CAMERAH
#define CAMERAH
#include "ray.h"
#define M_PI 3.1415926

class camera
{
public:
	camera();
	camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist)
	{
		lens_radius = aperture / 2;
		
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = vec3::unit_vector(lookfrom - lookat);
		u = vec3::unit_vector(vec3::cross(vup, w));
		v = vec3::cross(w, u);
		lower_left_corner = origin-half_width*focus_dist*u-half_height*focus_dist*v-focus_dist*w;
		horizontal = 2 * half_width*focus_dist*u;
		vertical = 2 * half_height*focus_dist*v;
	}
	~camera();
	ray get_ray(float s, float t) {
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin+offset, lower_left_corner + s * horizontal + t * vertical - origin-offset);
	}
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	vec3 u, v, w;
	float lens_radius;
	vec3 random_in_unit_disk()
	{
		vec3 p;
		do
		{
			p = 2.0*vec3(rand() % 10000 / 10000.0, rand() % 10000 / 10000.0, 0) - vec3(1, 1, 0);
		} while (vec3::dot(p, p) >= 1.0);
		return p;
	}
};

#endif // ! CAMERAH

