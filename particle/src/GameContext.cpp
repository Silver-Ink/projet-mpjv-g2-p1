#include "GameContext.h"
#include "../ofMain.h"

void GameContext::init()
{
	Particle* p1 = new Particle(100., 100. );

	Particle* p2 = new Particle(300., 160. );
	Particle* p3 = new Particle(160., 300. );

	lstParticle.emplace_back(p1);
	lstParticle.emplace_back(p2);
	lstParticle.emplace_back(p3);

	SpringBungee* fg1 = new SpringBungee( p1, 50. );
	lstForceGenerator.emplace_back(fg1);

	particleForceRegistry.Add(p2, fg1);
}

void GameContext::update(float _dt)
{
	particleForceRegistry.UpdateForces(_dt);

	//particleForceRegistry.Clear();

	for (auto particle : lstParticle)
	{
		particle->computeForces(_dt);
	}

	for (auto particle : lstParticle)
	{
		particle->update(_dt);
	}
}

void GameContext::draw()
{
	particleForceRegistry.DrawForces();
	for (auto particle : lstParticle)
	{
		particle->draw();
	}
}
