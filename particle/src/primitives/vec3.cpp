#include "vec3.h"


Vec3& Vec3::normalize()
{
	float length = getLength();
	x *= length;
	y *= length;
	z *= length;
	return *this;
}

Vec3 Vec3::getNormalized()
{
	Vec3 normalized = *this;
	return normalized.normalize();
}

Vec3 Vec3::operator*(float s)
{
	Vec3& v = *this;
	return v *= s;
}

Vec3& Vec3::operator*=(float s)
{
	if (s != 1.f)
	{
		x *= s;
		y *= s;
		z *= s;
	}
	return *this;
}

Vec3 Vec3::operator+(Vec3& v)
{
	Vec3& copy = *this;
	return copy += v;
}

Vec3& Vec3::operator+=(Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3 Vec3::operator-(Vec3& v)
{
	Vec3& copy = *this;
	return copy -= v;
}

Vec3& Vec3::operator-=(Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

