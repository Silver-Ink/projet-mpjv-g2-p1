#pragma once
#include "../particle/Particle.h"
#include "../primitives/vec3.h"
#include "../primitives/Quaternion.h"
#include "../matrix/Matrix3.h"
#include "../matrix/Matrix4.h"

class RigidBody
{
public:
	RigidBody() = default;
	RigidBody(Vec3 _center, float _length = 1., float _height = 1., float _width = 1., Quaternion _orientation = Quaternion::IDENTITY);

	//void integrate(float _dt);
	void update(float _dt);
	void draw();



private:
	Particle massCenter; // also geometric center

	// Bounds of the box, relative to massCenter's position
	Vec3 front; // X
	Vec3 up;	// Y
	Vec3 right;	// Z

	Vec3 initialFront;	// X
	Vec3 initialUp;		// Y
	Vec3 initialRight;	// Z

	float massTotal;

	Quaternion	orientation;
	Vec3		angularSpeed;
	Vec3		angularAcceleration;
};

