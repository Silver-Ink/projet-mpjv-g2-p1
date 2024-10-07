#include "GameContext.h"
#include "../ofMain.h"

void GameContext::update(float _dt)
{
	particleForceRegistry.UpdateForces(_dt);

	particleForceRegistry.Clear(); //

	for (auto& particle : lstParticle)
	{
		particle.update(_dt);
	}
}

void GameContext::draw()
{
	particleForceRegistry.DrawForces();
}
