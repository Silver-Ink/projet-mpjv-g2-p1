#include "SpringBungee.h"

void SpringBungee::updateForce(Particle* _particle, float /*_dt*/)
{
	Vec3 springForce = _particle->getPos() - hinge->getPos();
	float springLength = springForce.length();
	float extension = springLength - restLength;
	if (extension < 0)
	{
		return;
	}

	springForce *= 1. / springLength; //Normalize

	springForce *= -elasticConstant * extension;

	_particle->addForce(springForce);
}


void SpringBungee::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::white);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)hinge->getPos());
}