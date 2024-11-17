#include "Quaternion.h"

Quaternion Quaternion::IDENTITY{ 1., 0., 0., 0. };

Quaternion::Quaternion(float _omega, float _x, float _y, float _z)
	: a(_omega), b(_x), c(_y), d(_z)
{}

Quaternion::Quaternion(float _theta, Vec3 _axis)
{
	a = cos(_theta / 2.f);
	float s = sin(_theta / 2.f);
	b = s * _axis.x;
	c = s * _axis.y;
	d = s * _axis.z;
}

Quaternion::Quaternion(const Vec3 _v)
	: a(0), b(_v.x), c(_v.y), d(_v.z)
{}

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

Quaternion Quaternion::operator/(float _s)
{
	Quaternion q = *this;
	return q /= _s;
}

Quaternion& Quaternion::operator/=(float _s)
{
	// Division by zero?
	a /= _s;
	b /= _s;
	c /= _s;
	d /= _s;
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
	float resultA = a * _q.a - b * _q.b - c * _q.c - d * _q.d;
	float resultB = a * _q.b + b * _q.a + c * _q.d - d * _q.c;
	float resultC = a * _q.c + c * _q.a - b * _q.d + d * _q.b;
	
	d = a * _q.d + d * _q.a + b * _q.c - c * _q.b;
	a = resultA;
	b = resultB;
	c = resultC;

	return *this;
}

bool Quaternion::operator==(Quaternion& _q)
{
#define EPS .001
	return
		(fabs(a - _q.a) < EPS &&
			fabs(b - _q.b) < EPS &&
			fabs(c - _q.c) < EPS &&
			fabs(d - _q.d) < EPS);
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
	Quaternion q = *this;
	return q.inverse();
}

Quaternion& Quaternion::inverse()
{
	conjugate();
	*this /= length();
	return *this;
}

float Quaternion::dotProduct(Quaternion& _q)
{
	return a * _q.a + b * _q.b + c * _q.c + d * _q.d;
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

Matrix3 Quaternion::toMatrix3()
{
	Matrix3 m;
	m.set(0, 0, 1 - 2 * c * c - 2 * d * d);
	m.set(0, 1, 2 * b * c - 2 * a * d);
	m.set(0, 2, 2 * b * d + 2 * a * c);

	m.set(1, 0, 2 * b * c + 2 * a * d);
	m.set(1, 1, 1 - 2 * b * b - 2 * d * d);
	m.set(1, 2, 2 * c * d - 2 * a * b);

	m.set(2, 0, 2 * b * d - 2 * a * c);
	m.set(2, 1, 2 * c * d + 2 * a * b);
	m.set(2, 2, 1 - 2 * b * b - 2 * c * c);
	return m;
}

Vec3 Quaternion::rotateVector(const Vec3& v)
{
	Vec3 u(b, c, d);

	return 2.0f * u.dot(v) * u
		+ (a * a - u.dot(u)) * v
		+ 2.0f * a * u.cross(v);
}

Quaternion operator*(float _s, Quaternion& _q)
{
	Quaternion q = _q;
	return q *= _s;
}
