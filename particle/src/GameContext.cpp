#include "GameContext.h"
#include "../ofMain.h"
#include "particle/generators/ParticleGravity.h"

void GameContext::init()
{
	Particle* p1 = new Particle(300., 0. );

	Particle* p2 = new Particle(300., 250. );
	Particle* p3 = new Particle(160., 300. );

	lstParticle.emplace_back(p1);
	lstParticle.emplace_back(p2);
	//lstParticle.emplace_back(p3);

	ParticleGravity* gravity = new ParticleGravity();

	SpringBungee* fg1 = new SpringBungee( p1, 200. );
	lstForceGenerator.emplace_back(fg1);

	lstForceGenerator.emplace_back(gravity);

	particleForceRegistry.Add(p2, fg1);
	particleForceRegistry.Add(p2, gravity);
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
