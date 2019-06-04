#pragma once
#include "hitable.h"
#include "material.h"
class sphere :
	public hitable
{
public:
	sphere();
	sphere(vec3 cen, float r) :center(cen), radius(r) {};
	sphere(vec3 cen,float r,material* tmat):center(cen), radius(r),mat(tmat) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record &rec)const;
	vec3 center;
	float radius;
	material* mat;
	~sphere();
};

