#include "RigidBody.h"
#include "../GameContext.h"

RigidBody::RigidBody(const Vec3& _center, float _density, float _length, float _height, float _width, Quaternion _orientation) :
	orientation			(_orientation),
	totalMass			(abs(_length) * abs(_height) * abs(_width) * _density)
{
	massCenter = Particle{ _center };

	front	= Vec3{ _length / 2.f, 0., 0. };
	up		= Vec3{ 0., _height / 2.f, 0. };
	right	= Vec3{ 0., 0., _width / 2.f  };

	initialFront	= Vec3{ _length / 2.f, 0., 0. };
	initialUp		= Vec3{ 0., _height / 2.f, 0. };
	initialRight	= Vec3{ 0., 0., _width / 2.f  };
	//up					(0., _height / 2.f, 0.),
	//right				(0., 0., _width / 2.f),
	//initialFront		(_length/2.f, 0., 0.),
	//initialUp			(0., _height / 2.f, 0.),
	//initialRight		(0., 0., _width / 2.f),

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

	sqRadius = getMaxRadius();

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
	Quaternion angularSpeedQuat = Quaternion(0, angularSpeed.x, angularSpeed.y, angularSpeed.z);

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
	ofSetColor(ofColor::white);
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

	// Draw Enclosing volume
	if (isColliding) {
		ofSetColor(ofColor::red);
	}
	else {
		ofSetColor(ofColor::blue);
	}
	isColliding = false;

	float radius = sqRadius;

	ofSpherePrimitive sphere;
	sphere.setPosition(massCenter.getPos().x, massCenter.getPos().y, massCenter.getPos().z);
	sphere.setRadius(radius);
	sphere.setResolution(6);
	ofNoFill();                 
	ofSetLineWidth(1.5);
	sphere.drawWireframe();
	ofFill();
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

void RigidBody::getPoints(std::array<Vec3, 8>& _outBuffer, bool _localPosition /*= false*/)
{
	Vec3 pos = massCenter.getPos();
	if (_localPosition)
		pos = Vec3{ 0.f };
	_outBuffer[0] = pos	+ front + up + right;
	_outBuffer[1] = pos	+ front + up - right;
	_outBuffer[2] = pos	- front + up - right;
	_outBuffer[3] = pos	- front + up + right;
	_outBuffer[4] = pos	+ front - up + right;
	_outBuffer[5] = pos	+ front - up - right;
	_outBuffer[6] = pos	- front - up - right;
	_outBuffer[7] = pos	- front - up + right;
}

float RigidBody::getMaxRadius()
{
	// Return the maximum distance from the center to a corner of the box
	return (massCenter.getPos() - (massCenter.getPos() + initialFront+ initialUp+ initialRight)).length();
	 
}

bool RigidBody::contact(RigidBody &_other)
{
	Vec3 Pos1 = massCenter.getPos();
	Vec3 Pos2 = _other.massCenter.getPos();

	float dist = (Pos1 - Pos2).length();
	float sumRadius = sqRadius + _other.sqRadius;

	return (dist < sumRadius);
}

RigidBody::SatCollisionResult RigidBody::checkCollision(RigidBody& _other)
{
	SatCollisionResult result;
	result.isCollisionPresent = true;
	std::array<Vec3, 15> lstAxis;

	std::array<Vec3, 8> lstThisPoint;
	std::array<Vec3, 8> lstOtherPoint;

	this->getPoints(lstThisPoint, true);
	_other.getPoints(lstOtherPoint, true);

	Vec3 relativeDist = _other.getMassCenter().getPos() - this->getMassCenter().getPos();
	for (Vec3& otherPoint : lstOtherPoint)
	{
		otherPoint += relativeDist;
	}

	// Step 1.1 : face corner collision (corner of _other into this'  face)
	lstAxis[0] = this->front;
	lstAxis[1] = this->up;
	lstAxis[2] = this->right;

	// Step 1.2 : face corner collision (corner of this into _other's face)
	lstAxis[3] = _other.front;
	lstAxis[4] = _other.up;
	lstAxis[5] = _other.right;

	// Setp 2 : edge edge collision
	lstAxis[6] = this->front.cross(_other.front);
	lstAxis[7] = this->front.cross(_other.up);
	lstAxis[8] = this->front.cross(_other.right);

	lstAxis[9] = this->up.cross(_other.front);
	lstAxis[10] = this->up.cross(_other.up);
	lstAxis[11] = this->up.cross(_other.right);

	lstAxis[12] = this->right.cross(_other.front);
	lstAxis[13] = this->right.cross(_other.up);
	lstAxis[14] = this->right.cross(_other.right);


	int bestAxisId = 0;
	float minInterpenetration = 99999.f;


	for (size_t i = 0; i < 15; i++) // axis loop
	{
		if (lstAxis[i] == Vec3{ 0., 0., 0. })
			continue;

		float minThis = lstThisPoint[0].getProjectionLengthOntoAxis(lstAxis[i]);
		float maxThis = minThis;
		float minOther = lstOtherPoint[0].getProjectionLengthOntoAxis(lstAxis[i]);;
		float maxOther = minOther;

		for (size_t j = 1; j < 8; j++) // points loop
		{
			float thisProj = lstThisPoint[j].getProjectionLengthOntoAxis(lstAxis[i]);
			float otherProj = lstOtherPoint[j].getProjectionLengthOntoAxis(lstAxis[i]);

			if (std::isnan(thisProj) || std::isnan(otherProj))
			{
				thisProj = otherProj; // DEBUG
			}

			if (thisProj < minThis)
				minThis = thisProj;

			if (thisProj > maxThis)
				maxThis = thisProj;

			if (otherProj < minOther)
				minOther = otherProj;

			if (otherProj > maxOther)
				maxOther = otherProj;
		}

		// This is 'after' other on the projected axis 
		// --------------------------------[   this   ]---------------------->
		// ------------------------[  other   ]------------------------------>
		bool caseA = ((minThis < maxOther) && (maxThis > maxOther));

		// This is 'before' other on the projected axis 
		// -----------------[   this   ]------------------------------------->
		// ------------------------[  other   ]------------------------------>
		bool caseB = ((maxThis > minOther) && (minThis < minOther));

		// This contains other on the projected axis 
		// -----------------[           this           ]--------------------->
		// ------------------------[  other   ]------------------------------>
		bool caseC = ((maxThis > maxOther) && (minThis < minOther));

		// This is inside other on the projected axis 
		// -------------------------[    this   ]---------------------------->
		// -----------------[          other           ]--------------------->
		bool caseD = ((maxThis < maxOther) && (minThis > minOther));

		// Detect Interpenetration
		if ( caseA || caseB || caseC || caseD )
		{
			float interpenetration = 0.f;

			if		(caseA)
				interpenetration = maxOther - minThis;
			else if (caseB)
				interpenetration = maxThis - minOther;
			else if (caseC || caseD)
			{
				float ip1 = maxThis - minOther;
				float ip2 = maxOther - minThis;

				interpenetration = (abs(ip1) < abs(ip2)) ? ip1 : ip2;
			}

			if (abs(interpenetration) < abs(minInterpenetration))
			{
				minInterpenetration = interpenetration;
				bestAxisId = i;
			}
		}
		else
		{
			result.isCollisionPresent = false;
			return result;
		}
	}

	// At this point, collision is guaranteed
	result.interpenetration = minInterpenetration;
	result.minimumSeparationAxis = lstAxis[bestAxisId];

	return result;
}
