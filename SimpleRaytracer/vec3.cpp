#include "pch.h"
#include "vec3.h"


vec3::vec3()
{
}
inline std::istream& operator>>(std::istream &is, vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}
inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}
inline void vec3::make_unit_vector()
{
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}



vec3 & vec3::operator-=(const vec3 & v2)
{
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];
	return *this;
}

vec3 & vec3::operator*=(const vec3 & v2)
{
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];
	return *this;
}

vec3 & vec3::operator/=(const vec3 & v2)
{
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];
	return *this;
}

vec3 & vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

vec3 & vec3::operator/=(const float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}



vec3::~vec3()
{
}
