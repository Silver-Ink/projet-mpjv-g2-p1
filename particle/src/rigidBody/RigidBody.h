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
	RigidBody(Vec3 _center, float _length = 1., float _height = 1., float _width = 1., Quaternion _orientation = Quaternion::IDENTITY, float _density = 1);

	//void integrate(float _dt);
	void update(float _dt);
	void draw();

	Particle& getMassCenter() { return massCenter; }

	Quaternion		getOrientation	()									{return orientation;}
	void			setOrientation	(const Quaternion& _o)				{orientation = _o;}
		
	void			setAngularSpeed	(Vec3 _plane, float _magnitude)		{angularSpeed = _plane * _magnitude;}
	void			setAngularSpeed	(Vec3 _omega)						{angularSpeed = _omega;}

	float			getTotalMass	()									{return totalMass;}


private:
	Particle massCenter; // also geometric center

	// Bounds of the box, relative to massCenter's position
	Vec3 front; // X
	Vec3 up;	// Y
	Vec3 right;	// Z

	Vec3 initialFront;	// X
	Vec3 initialUp;		// Y
	Vec3 initialRight;	// Z

	float totalMass;

	Quaternion	orientation;
	Vec3		angularSpeed;
	Vec3		angularAcceleration;
};

