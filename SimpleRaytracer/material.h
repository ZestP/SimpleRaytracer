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
	vec3 reflect(const vec3& v, const vec3& n)
	{
		return v - 2 * vec3::dot(v, n)*n;
	}
	bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
	{
		vec3 uv = vec3::unit_vector(v);
		float dt = vec3::dot(uv, n);
		float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
		if (discriminant > 0)
		{
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
			return true;
		}
		else
		{
			return false;
		}
	}
	float schlick(float cosine, float ref_idx)
	{
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cosine), 5);
	}
	material();
	~material();
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)= 0;
};