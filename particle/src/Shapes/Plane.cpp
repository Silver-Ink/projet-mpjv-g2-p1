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
    Vec3 totalTorque(0, 0, 0);
    Vec3 averagePoint(0, 0, 0);
	Vec3 totalImpulse(0, 0, 0);
    int collisionCount = 0;

    for (Vec3 point : points)
    {
        float distance = getDistance(point);
        if (distance < 0)
        {
            Vec3 projectedPoint = projectPoint(point);
            Vec3 normal = (point - projectedPoint);
            correction += normal;
            averagePoint += projectedPoint;
            collisionCount++;


			totalImpulse += normal * impulsionStrength;

            Vec3 r = point - _rb->massCenter.getPos();
            Vec3 force = -normal;
            Vec3 torque = r.cross(force);
            totalTorque += torque;
        }
    }

    if (collisionCount > 0)
    {
        correction /= collisionCount; 
        averagePoint /= collisionCount; 
        _rb->massCenter.getPos() -= correction;

        // Appliquer le couple total
        _rb->massCenter.addImpulsion(-totalImpulse/2, averagePoint); // Pas de force, juste pour le point d'application
        _rb->massCenter.accumTorque += totalTorque;

        // Ajuster la vélocité pour éviter les oscillations
        Vec3 velocity = _rb->massCenter.getVelocity();
        float dotProduct = velocity.dot(correction);
        if (dotProduct < 0)
        {
            // Augmenter l'effet de la correction en multipliant par un facteur plus grand
            float attenuationFactor = 2.0f; // Vous pouvez ajuster ce facteur pour plus d'atténuation
            _rb->massCenter.getVelocity() -= attenuationFactor * dotProduct * correction.getNormalized();
        }
    }
}