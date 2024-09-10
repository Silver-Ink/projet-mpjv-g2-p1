#pragma once

#include <cmath>
#include <cstdio>
#include "ofMain.h"

struct Vec3
{
public:

	Vec3(float x) : Vec3(x, x, x) { }
	Vec3(float x, float y, float z) : x(x), y(y), z(z) { }

	Vec3(Vec3& ref) : x(ref.x), y(ref.y), z(ref.z) {}

	float	getLength() { return std::sqrt(sqLength()); }
	float	sqLength() { return x * x + y * y + z * z; }
	Vec3&	normalize();
	Vec3	getNormalized();

	Vec3	operator*(float s);
	Vec3&	operator*=(float s);

	Vec3	operator+(Vec3& v);
	Vec3&	operator+=(Vec3& v);

	Vec3	operator-(Vec3& v);
	Vec3&	operator-=(Vec3& v);

	float	dot(Vec3& v)	{ return x * v.x + y * v.y + z + v.z; }
	Vec3	cross(Vec3& v) { return Vec3{ x * v.y - y * v.x,
										  y * v.z - z * v.y,
										  z * v.x - x * v.z }; }

	void	print() { printf("{%.1f;%.1f;%.1f}", x, y, z); }

	explicit operator glm::vec3() { return { x, y, z }; }


public :
	float x;
	float y;
	float z;
};