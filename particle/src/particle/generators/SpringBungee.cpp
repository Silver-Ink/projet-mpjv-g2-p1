#include "SpringBungee.h"

void SpringBungee::updateForce(Particle* _particle, float /*_dt*/)
{
	Vec3 spring = _particle->getPos() - hinge->getPos();
	
	float extension = spring.length() - restLength;

	_particle->addForce(- elasticConstant * extension);
}