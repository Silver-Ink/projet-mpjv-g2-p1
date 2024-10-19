#include "SpringRod.h"

void SpringRod::updateForce(Particle* _otherParticle, float _dt)
{
	Vec3 spring = _otherParticle->getPos() - particle->getPos();

	float extension = spring.length() - rodLength;

	_otherParticle->addForce(-extension);
	particle->addForce(extension);
}


void SpringRod::drawForce(Particle* _particle)
{

}