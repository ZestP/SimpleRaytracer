#pragma once
#include "material.h"
class metal :
	public material
{
public:
	metal();
	metal(vec3 alb, float f) :albedo(alb) { if (f < 1)fuzz = f; else fuzz = 1; };
	~metal();
	
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)
	{
		vec3 reflected = reflect(vec3::unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (vec3::dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
};

