#include "RegularSpring.h"

void RegularSpring::updateForce(Particle* _particle, float _dt)
{
	const float lengthThreshold = 0.01;

	Vec3 spring = (_particle->getPos() - springOriginPoint);
	float currentLength = spring.length();

	float difference = currentLength - restLength;
	if (difference > lengthThreshold)
	{
		_particle->addForce(elasticConstant * spring);
	}
}

void RegularSpring::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::white);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)springOriginPoint);
}
