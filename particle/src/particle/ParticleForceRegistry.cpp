#include <vector>

#include "ParticleForceRegistry.h"
#include "IDrawsLine.h"

void ParticleForceRegistry::Add(Particle* _particle, ParticleForceGenerator* _forceGenerator)
{
	registerForceToParticle.emplace_back<ParticleForceRegistration>({ _particle, _forceGenerator });
}

void ParticleForceRegistry::Remove(int _registrationIndex)
{
	registerForceToParticle.erase(registerForceToParticle.begin() + _registrationIndex);
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
	size_t i = 0;
	bool lineFound = false;

	while (i < registerForceToParticle.size() && !lineFound)
	{
		ParticleForceRegistration forceRegistry = registerForceToParticle[i];

		if (IDrawsLine* fr = dynamic_cast<IDrawsLine*>(forceRegistry.forceGenerator)) // Only considering generators that draw lines
		{
			if (fr->doesLineTouch(forceRegistry.particle, _x, _y, 6.5)) // Is the cursor close enough to a line?
			{
				Remove(i);
				lineFound = true;
			}
		}
		i++;
	}
}