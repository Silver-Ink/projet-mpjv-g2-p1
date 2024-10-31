#include "Quaternion.h"

Quaternion Quaternion::operator*(float _s)
{
	Quaternion q = *this;
	return q *= _s;
}

Quaternion& Quaternion::operator*=(float _s)
{
	a *= _s;
	b *= _s;
	c *= _s;
	d *= _s;
	return *this;
}

Quaternion Quaternion::operator+(Quaternion& _q)
{
	Quaternion q = *this;
	return q += _q;
}

Quaternion& Quaternion::operator+=(Quaternion& _q)
{
	a += _q.a;
	b += _q.b;
	c += _q.c;
	d += _q.d;
	return *this;
}

Quaternion Quaternion::operator-(Quaternion& _q)
{
	Quaternion q = *this;
	return q -= _q;
}

Quaternion& Quaternion::operator-=(Quaternion& _q)
{

	a -= _q.a;
	b -= _q.b;
	c -= _q.c;
	d -= _q.d;
	return *this;
}

Quaternion Quaternion::operator*(Quaternion& _q)
{
	Quaternion q = *this;
	return q *= _q;
}

Quaternion& Quaternion::operator*=(Quaternion& _q)
{

	return *this;
}

Quaternion Quaternion::operator-()
{
	Quaternion q = *this;
	q.a = -a;
	q.b = -b;
	q.c = -c;
	q.d = -d;
	return q;
}

Quaternion Quaternion::getConjugate()
{
	Quaternion q = *this;
	return q.conjugate();
}

Quaternion& Quaternion::conjugate()
{
	b = -b;
	c = -c;
	d = -d;
	return *this;
}

float Quaternion::length()
{
	return sqrtf(a*a + b*b + c*c + d*d);
}

Quaternion Quaternion::getNormalized()
{
	Quaternion q = *this;
	return normalize();
}

Quaternion& Quaternion::normalize()
{
	float l = length();
	a /= l;
	b /= l;
	c /= l;
	d /= l;
	return *this;
}

Quaternion operator*(float _s, Quaternion& _q)
{
	Quaternion q = _q;
	return q *= _s;
}
