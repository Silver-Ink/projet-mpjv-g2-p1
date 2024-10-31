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
	Quaternion _qConj = _q.getConjugate();
	*this *= _qConj;
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

Quaternion Quaternion::getInverse()
{
	return Quaternion();
}

Quaternion& Quaternion::inverse()
{
	// TODO: insert return statement here
	return *this;
}

float Quaternion::dotProduct(Quaternion& _q)
{
	return 0.0f;
}

Quaternion Quaternion::getExpo(float _t)
{
	Quaternion q = *this;
	return q.expo(_t);
}

Quaternion& Quaternion::expo(float _t)
{
	float alpha = acos(a);
	float beta = sin(_t * alpha) / sin(alpha);
	a = cos(_t * alpha);
	b *= beta;
	c *= beta;
	d *= beta;
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
