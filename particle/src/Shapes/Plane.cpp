#include "Plane.h"

Plane::Plane(Vec3 _origin, Vec3 _normal) : origin(_origin), normal(_normal.normalize())
{
	impulsionStrength = 1;
}

Plane::Plane(Vec3 _p1, Vec3 _p2, Vec3 _p3)
{
	Vec3 v1 = _p2 - _p1;
	Vec3 v2 = _p3 - _p1;
	normal = v1.cross(v2).normalize();
	origin = _p1;
	impulsionStrength = 1;
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
    Vec3 correction(0, 0, 0);
    int collisionCount = 0;

    for (Vec3 point : points)
    {
        float distance = getDistance(point);
        if (distance < 0)
        {
            Vec3 projectedPoint = projectPoint(point);
            Vec3 normal = (point - projectedPoint);
            correction += normal;
            collisionCount++;

            // Calculer l'impulsion en tenant compte de la masse infinie du plan
            float massCube = _rb->getTotalMass();
            Vec3 impulsion = -massCube * normal;
            _rb->massCenter.addImpulsion(impulsion*2, point);
        }
    }

    if (collisionCount > 0)
    {
        correction /= collisionCount; // Moyenne des corrections
        _rb->massCenter.getPos() -= correction;

        // Ajuster la vélocité pour éviter les oscillations
        Vec3 velocity = _rb->massCenter.getVelocity();
        if (velocity.dot(correction) < 0)
        {
            _rb->massCenter.getVelocity() -= velocity.dot(correction) * correction.getNormalized();
        }
    }
}