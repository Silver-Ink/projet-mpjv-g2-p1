#include "Plane.h"

Plane::Plane(Vec3 _origin, Vec3 _normal) : origin(_origin), normal(_normal.normalize()) {}

Plane::Plane(Vec3 _p1, Vec3 _p2, Vec3 _p3)
{
	Vec3 v1 = _p2 - _p1;
	Vec3 v2 = _p3 - _p1;
	normal = v1.cross(v2).normalize();
	origin = _p1;
}

Vec3 Plane::getOrigin()
{
	return origin;
}

Vec3 Plane::getNormal()
{
	return normal;
}

Vec3 Plane::projectPoint(Vec3 _point)
{
	Vec3 v = _point - origin;
	float distance = v.dot(normal);
	return _point - normal * distance;
}

float Plane::getDistance(Vec3 _point)
{
	Vec3 v = _point - origin;
	return v.dot(normal);
}