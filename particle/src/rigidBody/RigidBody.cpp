#include "RigidBody.h"
#include "../GameContext.h"

RigidBody::RigidBody(const Vec3& _center, float _length, float _height, float _width, Quaternion _orientation, float _density) :
	massCenter			(_center),
	initialFront		(abs(_length/2.f), 0., 0.),
	initialUp			(0., abs(_height / 2.f), 0.),
	initialRight		(0., 0., abs(_width / 2.f)),
	front				(abs(_length/2.f), 0., 0.),
	up					(0., abs(_height / 2.f), 0.),
	right				(0., 0., abs(_width / 2.f)),
	orientation			(_orientation),
	totalMass			(abs(_length) * abs(_height) * abs(_width) * _density)
{
	// Calculate inertia tensor
	float _rx = _length / 2.f;
	float _ry = _height / 2.f;
	float _rz = _width / 2.f;

	float element[3][3] = {
		{_ry*_ry + _rz*_rz, _ry*_rx*-1, _rz*_rx*-1},
		{_rx*_ry*-1, _rx*_rx + _rz*_rz, _rz*_ry*-1},
		{_rx*_rz*-1, _ry*_rz*-1, _rx*_rx + _ry*_ry}
	};

	inverseInertiaTensor = Matrix3(element);
	inverseInertiaTensor *= totalMass;
	inverseInertiaTensor = inverseInertiaTensor.inverse();
}

void RigidBody::update(float _dt)
{
	Vec3 _torque = Vec3(0, 0, 0); // torque???
	// get acceleration from a = T * J-1
	angularAcceleration = inverseInertiaTensor * _torque;

	// update angular speed
	angularSpeed += angularAcceleration * _dt;

	// update orientation
	Quaternion angularSpeedQuat = Quaternion(0, angularSpeed.x, angularSpeed.y, angularSpeed.z);		// Demander au prof explications parce que �a parait magique

	orientation += 0.5 * angularSpeedQuat * orientation * _dt;
	orientation.normalize();

	// transform quaternion to matrix
	Matrix3 rotationMatrix = orientation.toMatrix3();

	//Update inverse inertia tensor
	inverseInertiaTensor = rotationMatrix * inverseInertiaTensor * rotationMatrix.transpose(); 

	// apply matrix to initial vectors and stock them
	front = rotationMatrix * initialFront;
	up = rotationMatrix * initialUp;
	right = rotationMatrix * initialRight;
}

void RigidBody::draw()
{
	ofPushMatrix(); // Temporarly moving pivot

	ofTranslate((glm::vec3)massCenter.getPos()); // Pivot translation to box center

	// Drawing box line by line
	Vec3 boxEnd1 = front - up + right;

	ofDrawLine((glm::vec3)boxEnd1, (glm::vec3)(boxEnd1 - 2 * front));
	ofDrawLine((glm::vec3)boxEnd1, (glm::vec3)(boxEnd1 + 2 * up));
	ofDrawLine((glm::vec3)boxEnd1, (glm::vec3)(boxEnd1 - 2 * right));

	Vec3 boxEnd2 = -front + up + right;

	ofDrawLine((glm::vec3)boxEnd2, (glm::vec3)(boxEnd2 + 2 * front));
	ofDrawLine((glm::vec3)boxEnd2, (glm::vec3)(boxEnd2 - 2 * up));
	ofDrawLine((glm::vec3)boxEnd2, (glm::vec3)(boxEnd2 - 2 * right));

	Vec3 boxEnd3 = -front - up - right;

	ofDrawLine((glm::vec3)boxEnd3, (glm::vec3)(boxEnd3 + 2 * front));
	ofDrawLine((glm::vec3)boxEnd3, (glm::vec3)(boxEnd3 + 2 * up));
	ofDrawLine((glm::vec3)boxEnd3, (glm::vec3)(boxEnd3 + 2 * right));

	Vec3 boxEnd4 = front + up - right;

	ofDrawLine((glm::vec3)boxEnd4, (glm::vec3)(boxEnd4 - 2 * front));
	ofDrawLine((glm::vec3)boxEnd4, (glm::vec3)(boxEnd4 - 2 * up));
	ofDrawLine((glm::vec3)boxEnd4, (glm::vec3)(boxEnd4 + 2 * right));

	ofPopMatrix(); // Resetting pivot
}

bool RigidBody::containsPoint(Vec3 _point)
{
	Vec3 relativePoint{ _point - massCenter.getPos() };

	//Values of initial___ are used as length of vector front, up and right
	float x = abs(relativePoint.dot(front)	/ initialFront.x);
	float y = abs(relativePoint.dot(up)		/ initialUp.y);
	float z = abs(relativePoint.dot(right)	/ initialRight.z);

	return x < initialFront.x &&
		   y < initialUp.y &&
		   z < initialRight.z;
}
