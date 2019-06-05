#pragma once
#include "material.h"
class dielectric :
	public material
{
public:
	dielectric();
	dielectric(float ri) :ref_idx(ri) {}
	~dielectric();
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)
	{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1, 1, 1);
		vec3 refracted;
		float reflect_probe;
		float cosine;
		if (vec3::dot(r_in.direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * vec3::dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -vec3::dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_probe = schlick(cosine, ref_idx);
		}else
		{
			scattered = ray(rec.p, refracted);
			reflect_probe = 1.0;
		}
		if (rand() % 10000 / 10000.0 < reflect_probe)
		{
			scattered = ray(rec.p, reflected);
		}
		else
		{
			scattered = ray(rec.p, refracted);
		}
		return true;
	}
	float ref_idx;
};

