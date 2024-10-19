#include "GameContext.h"
#include "../ofMain.h"
#include "particle/generators/ParticleGravity.h"
#include "particle/generators/Friction.h"



void GameContext::init()
{
	//ParticleGravity* gravity = new ParticleGravity();
	//AddForceGenerator(gravity);
	ParticleGravity* gravity = static_cast<ParticleGravity*>(lstForceGenerator.emplace_back(new ParticleGravity()));

	Particle* p1 = new Particle(300., 0. );
	Particle* p2 = new Particle(300., 250. );

	AddParticle(p1);
	AddParticle(p2);
	Particle* p3 = AddParticle({100., 100.});

	lstForceGenerator.emplace_back(new ParticleGravity());


	SpringBungee* springBungee1 = new SpringBungee( p1, 200. );
	AddForceGenerator(springBungee1);


	particleForceRegistry.Add(p2, springBungee1);
}
void GameContext::Testing() {

	Particle* p = new Particle(500, 500);

	lstParticle.emplace_back(p);

	ParticleGravity* gravity = new ParticleGravity();

	lstForceGenerator.emplace_back(gravity);
	

	//doit on mettre la force normal avec la friction ou en dehors?
	Friction* friction = new Friction();
	lstForceGenerator.emplace_back(friction);
	particleForceRegistry.Add(p, friction);
	particleForceRegistry.Add(p, gravity);
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

ParticleForceGenerator* GameContext::AddForceGenerator(ParticleForceGenerator* _forceGenerator)
{
	lstForceGenerator.emplace_back(_forceGenerator);
	return _forceGenerator;
}

Particle* GameContext::AddParticle(Particle* _particle)
{
	lstParticle.emplace_back(_particle); 
	return _particle;
}

Particle* GameContext::AddParticle(const Particle& _particle)
{
	Particle* newParticle = new Particle(_particle);
	lstParticle.emplace_back(newParticle);
	return newParticle;
}
