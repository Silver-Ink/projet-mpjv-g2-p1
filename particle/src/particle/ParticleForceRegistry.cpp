#include "ParticleForceRegistry.h"
#include "IDrawsLine.h"

void ParticleForceRegistry::Add(Particle* _particle, ParticleForceGenerator* _forceGenerator)
{
	registerForceToParticle.emplace_back<ParticleForceRegistration>({ _particle, _forceGenerator });
}

void ParticleForceRegistry::Remove(Particle* _particle, ParticleForceGenerator* _forceGenerator)
{
	
}

void ParticleForceRegistry::UpdateForces(float _dt)
{
	for (auto& forceRegistry : registerForceToParticle)
	{
		forceRegistry.forceGenerator->updateForce(forceRegistry.particle, _dt);
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

void ParticleForceRegistry::destroyLineAt(int _x, int _y)
{
	for (auto& forceRegistry : registerForceToParticle)
	{
		if (IDrawsLine* fr = dynamic_cast<IDrawsLine*>(forceRegistry.forceGenerator)) // Only considering generators that draw lines
		{
			if (fr->doesLineTouch(forceRegistry.particle, _x, _y, 5.))
			{

			}
		}
	}
}