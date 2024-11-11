#include "Vec3.h"

Vec3& Vec3::operator=(const Vec3& _other)
{
	x = _other.x;
	y = _other.y;
	z = _other.z;
	return *this;
}

Vec3& Vec3::normalize()
{
	float invLen = 1./length();
	x *= invLen;
	y *= invLen;
	z *= invLen;
	return *this;
}

Vec3 Vec3::getNormalized()
{
	Vec3 copy = *this;
	return copy.normalize();
}

Vec3 Vec3::operator*(float _s)
{
	Vec3 copy = *this;
	return copy *= _s;
}

Vec3 operator*(float _s, Vec3& _v)
{
	Vec3 copy = _v;
	return copy *= _s;
}

Vec3& Vec3::operator*=(float _s)
{
	if (_s != 1.f)
	{
		x *= _s;
		y *= _s;
		z *= _s;
	}
	return *this;
}

Vec3 Vec3::operator+(Vec3& _v)
{
	Vec3 copy = *this;
	return copy += _v;
}

Vec3& Vec3::operator+=(Vec3& _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	return *this;
}

Vec3& Vec3::operator+=(const Vec3& _v)
{
	return *this += const_cast<Vec3&>(_v);
}

Vec3 Vec3::operator-(Vec3& _v)
{
	Vec3 copy = *this;
	return copy -= _v;
}

Vec3& Vec3::operator-=(Vec3& _v)
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
	return *this;
}

bool Vec3::operator==(Vec3& _v)
{
	#define EPS .001
	return 
	(	fabs(x - _v.x) < EPS &&
		fabs(y - _v.y) < EPS &&
		fabs(z - _v.z) < EPS	);
}

Vec3 Vec3::operator-()
{
	return *this * -1;
}