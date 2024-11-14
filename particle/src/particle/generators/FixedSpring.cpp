#include "FixedSpring.h"


void FixedSpring::updateForce(Particle* _particle, float _dt)
{
	const float lengthThreshold = 0.01;

	Vec3 spring = (_particle->getPos() - springOriginPoint);
	float currentLength = spring.length();

	float difference = currentLength - restLength;
	if (fabs(difference) > lengthThreshold)
	{
		spring *= -1. / currentLength * difference * elasticConstant;
		_particle->addForce(spring, _particle->getPos());
	}
}

void FixedSpring::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::white);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)springOriginPoint);
}