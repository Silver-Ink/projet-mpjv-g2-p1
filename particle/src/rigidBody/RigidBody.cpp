#include "RigidBody.h"

RigidBody::RigidBody(Vec3 _center, float _length, float _height, float _width, Quaternion _orientation, float _density) :
	massCenter			(_center),
	initialFront		(abs(_length/2.f), 0., 0.),
	initialUp			(0., abs(_height / 2.f), 0.),
	initialRight		(0., 0., abs(_width / 2.f)),
	orientation			(_orientation),
	totalMass			(abs(_length) * abs(_height) * abs(_width) * _density)
{
}

void RigidBody::update(float _dt)
{

	// update orientation
	Quaternion angularSpeedQuat = Quaternion(angularSpeed.x, angularSpeed.y, angularSpeed.z, 0);

	Quaternion nextOrientation = orientation + 0.5 * angularSpeedQuat * orientation * _dt;

	// transform quaternion to matrix
	Matrix3 rotationMatrix = nextOrientation.toMatrix3();

	// apply matrix to initial vectors and stock them
	/*front = rotationMatrix * initialFront;
	up = rotationMatrix * initialUp;
	right = rotationMatrix * initialRight;*/
}
