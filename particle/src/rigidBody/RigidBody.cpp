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
	Quaternion angularSpeedQuat = Quaternion(0, angularSpeed.x, angularSpeed.y, angularSpeed.z);		// Demander au prof explications parceque �a parait magique

	Quaternion nextOrientation = orientation + 0.5 * angularSpeedQuat * orientation * _dt;

	// transform quaternion to matrix
	Matrix3 rotationMatrix = nextOrientation.toMatrix3();

	// apply matrix to initial vectors and stock them
	/*front = rotationMatrix * initialFront;
	up = rotationMatrix * initialUp;
	right = rotationMatrix * initialRight;*/
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

	Vec3 boxEnd2 = -1 * front + up + right;

	ofDrawLine((glm::vec3)boxEnd2, (glm::vec3)(boxEnd2 + 2 * front));
	ofDrawLine((glm::vec3)boxEnd2, (glm::vec3)(boxEnd2 - 2 * up));
	ofDrawLine((glm::vec3)boxEnd2, (glm::vec3)(boxEnd2 - 2 * right));

	Vec3 boxEnd3 = -1 * front - up - right;

	ofDrawLine((glm::vec3)boxEnd3, (glm::vec3)(boxEnd3 + 2 * front));
	ofDrawLine((glm::vec3)boxEnd3, (glm::vec3)(boxEnd3 + 2 * up));
	ofDrawLine((glm::vec3)boxEnd3, (glm::vec3)(boxEnd3 + 2 * right));

	Vec3 boxEnd4 = front + up - right;

	ofDrawLine((glm::vec3)boxEnd4, (glm::vec3)(boxEnd4 - 2 * front));
	ofDrawLine((glm::vec3)boxEnd4, (glm::vec3)(boxEnd4 - 2 * up));
	ofDrawLine((glm::vec3)boxEnd4, (glm::vec3)(boxEnd4 + 2 * right));

	ofPopMatrix(); // Resetting pivot
}