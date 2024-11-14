#include "RegularSpring.h"

void RegularSpring::updateForce(Particle* _particle, float _dt)
{
	const float lengthThreshold = 0.01;

	Vec3 spring = (_particle->getPos() - hinge->getPos());
	float currentLength = spring.length();

	float difference = currentLength - restLength;

	if (isBungee && difference < 0.)
	{
		return;
	}

	if (fabs(difference) > lengthThreshold)
	{
		spring *= -1. / currentLength * difference * elasticConstant;
		_particle->addForce(spring, _particle->getPos());
		spring *= -1.;
		hinge->addForce(spring, hinge->getPos());
	}
}

void RegularSpring::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::white);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)hinge->getPos());
}
