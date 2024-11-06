#include "RigidBody.h"

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