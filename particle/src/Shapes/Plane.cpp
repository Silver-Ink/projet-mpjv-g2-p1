#include "Plane.h"

Plane::Plane(Vec3 _origin, Vec3 _normal) : origin(_origin), normal(_normal.normalize())
{
	impulsionStrength = 10;
}

Plane::Plane(Vec3 _p1, Vec3 _p2, Vec3 _p3)
{
	Vec3 v1 = _p2 - _p1;
	Vec3 v2 = _p3 - _p1;
	normal = v1.cross(v2).normalize();
	origin = _p1;
	impulsionStrength = 10;
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

void Plane::draw()
{
	float size = 10000;
	//set the color to gray for the plane
	ofPushMatrix();
	ofSetColor(128, 128, 128);
	ofRotateDeg(90, 1, 0, 0);
	ofDrawPlane(origin.x,-origin.z,-origin.y, size, size);
	ofPopMatrix();
}

void Plane::collisionResolve(RigidBody* _rb)
{
	array<Vec3, 8> points;
	_rb->getPoints(points);
	for (Vec3 point : points)
	{
		float distance = getDistance(point);
		if (abs(distance) < 0.01)
			continue;
		if (distance < 0)
		{
			Vec3 projectedPoint = projectPoint(point);
			Vec3 normal = (point - projectedPoint).normalize();
			_rb->massCenter.addForce(-1 * normal * impulsionStrength, projectedPoint);
			_rb->massCenter.getPos() += normal * distance;
		}
		else
			if(distance < 0.1 && _rb->massCenter.getVelocity().sqLength()<3)
			{
				_rb->massCenter.getVel() = _rb->massCenter.getVel() - _rb->massCenter.getVel().dot(normal) * normal;
			}
	}
}
