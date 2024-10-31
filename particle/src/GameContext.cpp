#include "GameContext.h"
#include "../ofMain.h"
#include "particle/generators/Friction.h"
#include "particle/generators/RegularSpring.h"
#include "particle/generators/SpringRod.h"
#include "particle/Collisionner.h"
#include "particle/generators/SpringCable.h"
#include "particle/generators/FixedSpring.h"
#include "particle/generators/BlobSpring.h"



void GameContext::init()
{
	emptyScene();

	ParticleGravity* gravity = new ParticleGravity();
	AddForceGenerator(gravity);

}

void GameContext::update(float _dt)
{
	particleForceRegistry.UpdateForces(_dt);

	Collisionner::HandleAllCollision(lstParticle);

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

void GameContext::emptyScene()
{
	particleForceRegistry.Clear();
	for (auto p : lstParticle)
	{
		delete p;
	}
	lstParticle.clear();
	for (auto fg : lstForceGenerator)
	{
		delete fg;
	}
	lstForceGenerator.clear();
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