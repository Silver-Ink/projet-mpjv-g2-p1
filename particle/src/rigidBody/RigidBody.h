#pragma once
#include "../particle/Particle.h"
#include "../primitives/vec3.h"
#include "../primitives/Quaternion.h"
#include "../matrix/Matrix3.h"
#include "../matrix/Matrix4.h"

struct SatCollisionResult {
	bool isCollisionPresent{ false };
	float interpenetration{ 0. };
	Vec3 normal{ 0. }; // AKA normal vector
	Vec3 collisionPoint{};
};

class RigidBody
{
public:
	RigidBody() = default;
	RigidBody(const Vec3& _center,float _density = 0.001, float _length = 30., float _height = 30., float _width = 30., Quaternion _orientation = Quaternion::IDENTITY);

	//void integrate(float _dt);
	void update(float _dt);
	void draw();

	Particle& getMassCenter() { return massCenter; }

	Quaternion		getOrientation	()									{return orientation;}
	void			setOrientation	(const Quaternion& _o)				{orientation = _o;}
		
	void			setAngularSpeed	(Vec3 _plane, float _magnitude)		{angularSpeed = _plane * _magnitude;}
	void			setAngularSpeed	(Vec3 _omega)						{angularSpeed = _omega;}

	float			getTotalMass	()									{return totalMass;}
	
	bool			containsPoint	(Vec3 _point);
	void			getPoints		(std::array<Vec3, 8>& _outBuffer, bool _localPosition = false);

	float			getMaxRadius	();

	bool			contact			(RigidBody &_other);


	SatCollisionResult		checkCollision		(RigidBody& _other);

	Particle massCenter{}; // also geometric center
	bool isColliding = false;

private:

	// Bounds of the box, relative to massCenter's position
	Vec3 front; // X
	Vec3 up;	// Y
	Vec3 right;	// Z

	Vec3 initialFront;	// X
	Vec3 initialUp;		// Y
	Vec3 initialRight;	// Z

	float totalMass;
	float sqRadius{};

	Quaternion	orientation;
	Vec3		angularSpeed;
	Vec3		angularAcceleration;

	Matrix3		inverseInertiaTensor;

};



