#include "EnclosingVolume.h"
#include "../ofApp.h"

void EnclosingVolume::update(float _dt) {
	// call the rigid body update function
	rb.update(_dt);

}

bool EnclosingVolume::contact(EnclosingVolume _other)
{
	Vec3 Pos1 = rb.massCenter.getPos();
	Vec3 Pos2 = _other.rb.massCenter.getPos();

	float dist = (Pos1 - Pos2).length();
	float sumRadius = radius + _other.radius;

	return (dist <= sumRadius);
	
}

void EnclosingVolume::resolveCollision(EnclosingVolume _other)
{
	// Get center & speed of both rigid bodies
	Vec3 center1 = rb.getMassCenter().getPos();
	Vec3 center2 = _other.rb.getMassCenter().getPos();

	Vec3 velocity1 = rb.getMassCenter().getVelocity();
	Vec3 velocity2 = _other.rb.getMassCenter().getVelocity();

	// Get the normal vector
	Vec3 normal = center2 - center1;
	normal.normalize();

	// Calculate relative velocity
	Vec3 relativeVelocity = velocity2 - velocity1;

	// Calculate relative speed
	float relativeSpeedNormal = relativeVelocity.dot(normal);

	// If the relative speed is positive, the objects are moving away from each other
	if (relativeSpeedNormal > 0)
		return;

	// Restitution
	float restitution = 0.8f;

	// Calculate impulse scalar
	float impulseScalar = -(1 + restitution) * relativeSpeedNormal;
	impulseScalar /= ( rb.getTotalMass() + _other.rb.getTotalMass() );

	// Apply impulse
	Vec3 impulse = impulseScalar * normal;

	rb.getMassCenter().addForce(-impulse, center1);
	_other.rb.getMassCenter().addForce(impulse, center2);
}


void EnclosingVolume::drawCollisionVolume()
{
	ofSetColor(ofColor::red);
	ofSpherePrimitive sphere;
	sphere.setPosition(rb.massCenter.getPos().x, rb.massCenter.getPos().y, rb.massCenter.getPos().z);
	sphere.setRadius(radius);
	sphere.setResolution(6);
	ofNoFill();
	ofSetLineWidth(1.5);
	sphere.drawWireframe();
	ofFill();
	ofSetColor(ofColor::white);

}