#include "ParticleGravity.h"

void ParticleGravity::updateForce(Particle* _particle, float _dt)
{
	_particle->addForce( gravity*_particle->getMass() );
}