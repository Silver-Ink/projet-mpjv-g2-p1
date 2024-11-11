#pragma once

#include <cmath>
#include <cstdio>
#include "ofMain.h"

struct Vec3
{
public:

	Vec3() : Vec3(0.f) {}
	Vec3(float x) : Vec3(x, x, x) { }
	Vec3(float x, float y, float z) : x(x), y(y), z(z) { }

	Vec3(const Vec3& ref) : x(ref.x), y(ref.y), z(ref.z) {}

	Vec3&	operator=(const Vec3& _other);

	float	length() { return std::sqrt(sqLength()); }
	float	sqLength() { return x * x + y * y + z * z; }
	Vec3&	normalize();
	Vec3	getNormalized();

	Vec3	operator*(float _s);
	Vec3&	operator*=(float _s);

	Vec3	operator+(Vec3& _v);
	Vec3&	operator+=(Vec3& _v);
	Vec3&	operator+=(const Vec3& _v);

	Vec3	operator-(Vec3& _v);
	Vec3&	operator-=(Vec3& _v);

	Vec3	operator-();


	bool	operator==(Vec3& _v);
	bool	operator<(Vec3& _v) { return _v.x < x && _v.y < y && _v.z < z; }
	bool	operator>(Vec3& _v) { return _v.x > x && _v.y > y && _v.z > z; }

	float	dot(Vec3& _v)	{ return x * _v.x + y * _v.y + z * _v.z; }
	Vec3	cross(Vec3& _v) { return Vec3{	y * _v.z - z * _v.y,
											z * _v.x - x * _v.z,
											x * _v.y - y * _v.x }; }

	void	print() { printf("{%.1f;%.1f;%.1f}", x, y, z); }

	explicit operator glm::vec3() { return { x, y, z }; }
	explicit operator glm::vec2() { return { x, y }; }


public :
	float x;
	float y;
	float z;
};

Vec3 operator*(float _s, Vec3& _v);