#include "pch.h"
#include "sphere.h"


sphere::sphere()
{
}

bool sphere::hit(const ray & r, float tmin, float tmax, hit_record & rec) const
{
	vec3 oc = r.origin() - center;
	float a = vec3::dot(r.direction(), r.direction());
	float b = vec3::dot(oc, r.direction());
	float c = vec3::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a*c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;
		if (temp<tmax&&temp>tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat;
			return true;
		}
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp<tmax&&temp>tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat;
			return true;
		}
	}
	return false;
}


sphere::~sphere()
{
}
