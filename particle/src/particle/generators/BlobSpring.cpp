#include "BlobSpring.h"
#include "../Collisionner.h"

void BlobSpring::updateForce(Particle* _particle, float _dt)
{
	const float lengthThreshold = 0.01;

	Vec3 spring = (_particle->getPos() - hinge->getPos());
	float currentLength = spring.length();
	if (currentLength == 0)
	{
		return;
	}
	float springDifference = currentLength - restLength;
	float ropeDifference = currentLength - maxLength;
	if (ropeDifference > 0)
	{
		//Collisionner::repositionParticle(_particle, hinge, Collisionner::CollisionResult{ spring.getNormalized(), hinge->getPos(), ropeDifference });
	}
	else if (fabs(springDifference) > lengthThreshold)
	{
		spring *= -1. / currentLength * springDifference * elasticConstant;
		_particle->addForce(spring, _particle->getPos());
		spring *= -1.;
		hinge->addForce(spring, hinge->getPos());
	}
}

void BlobSpring::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::green);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)hinge->getPos());
}