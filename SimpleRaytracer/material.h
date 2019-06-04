#pragma once
#include "ray.h"
#include "hitable.h"
class material
{
public:
	vec3 random_in_unit_sphere()
	{
		vec3 p;
		do
		{
			p = 2.0*vec3(rand() % 10000 / 10000.0, rand() % 10000 / 10000.0, rand() % 10000 / 10000.0) - vec3(1, 1, 1);
		} while (p.squared_length() >= 1.0);
		return p;
	}
	material();
	~material();
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)= 0;
};