#include "RigidBody.h"
#include "../GameContext.h"

RigidBody::RigidBody(const Vec3& _center, float _density, float _length, float _height, float _width, Quaternion _orientation) :
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
	float _rx = _length;
	float _ry = _height;
	float _rz = _width;

	float Ixx = (1.0f / 12.0f) * totalMass * (_ry * _ry + _rz * _rz);
	float Iyy = (1.0f / 12.0f) * totalMass * (_rx * _rx + _rz * _rz);
	float Izz = (1.0f / 12.0f) * totalMass * (_rx * _rx + _ry * _ry);

	float element[3][3] = {
		{1/Ixx, 0, 0},
		{0, 1/Iyy, 0},
		{0, 0, 1/Izz}
	};

	inverseInertiaTensor = Matrix3(element);
}

//si jamais on a besoin de calculer la matrice d'inertie � partir de points ( si l'objet n'est pas un cube)
/*Matrix3 calculateInertiaTensor(const std::vector<Vec3>& points, float density) {
	float Ixx = 0, Iyy = 0, Izz = 0;
	float Ixy = 0, Ixz = 0, Iyz = 0;

	for (const Vec3& p : points) {
		float x = p.x;
		float y = p.y;
		float z = p.z;

		Ixx += density * (y * y + z * z);
		Iyy += density * (x * x + z * z);
		Izz += density * (x * x + y * y);
		Ixy -= density * (x * y);
		Ixz -= density * (x * z);
		Iyz -= density * (y * z);
	}

	float elements[3][3] = {
		{Ixx, Ixy, Ixz},
		{Ixy, Iyy, Iyz},
		{Ixz, Iyz, Izz}
	};

	return Matrix3(elements);
}*/

void RigidBody::update(float _dt)
{
	Vec3 _torque = massCenter.accumTorque;
	massCenter.accumTorque = Vec3{ 0,0,0 };
	

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

	massCenter.update(_dt);
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
