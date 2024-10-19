#include "ParticleForceRegistry.h"

void ParticleForceRegistry::Add(Particle* _particle, ParticleForceGenerator* _forceGenerator)
{
	registerForceToParticle.emplace_back<ParticleForceRegistration>({ _particle, _forceGenerator });
}

void ParticleForceRegistry::Remove(Particle* _particle, ParticleForceGenerator* _forceGenerator)
{
	
}

void ParticleForceRegistry::UpdateForces(float _dt)
{
	for (auto& forceResistry : registerForceToParticle)
	{
		forceResistry.forceGenerator->updateForce(forceResistry.particle, _dt);
	}
}

void ParticleForceRegistry::DrawForces()
{
	for (auto& fr : registerForceToParticle)
	{
		fr.forceGenerator->drawForce(fr.particle);
		fr.particle->draw();
	}
}
