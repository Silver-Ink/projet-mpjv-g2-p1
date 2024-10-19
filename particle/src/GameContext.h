#pragma once
#include "primitives/Vec3.h"
#include "particle/Particle.h"
#include "particle/ParticleForceGenerator.h"
#include "particle/ParticleForceRegistry.h"
#include "particle/generators/SpringBungee.h"

class GameContext
{
// SINGLETON
public:
	static GameContext& getInstance()
	{
		static GameContext instance;
		return instance;
	}
private:
	GameContext() {}

public:
	GameContext(const GameContext&) = delete;
	void operator=(const GameContext&) = delete;

// INTERFACE
public:
	void		init	();
	void		Testing();
	void		update	(float _dt);
	void		draw	();

public:
	
	ParticleForceRegistry particleForceRegistry;
	std::vector<Particle*> lstParticle;
	std::vector<ParticleForceGenerator*> lstForceGenerator;

private:
	ParticleForceGenerator*		AddForceGenerator	(ParticleForceGenerator* _forceGenerator);
	Particle*					AddParticle			(Particle* _particle);

	ParticleForceGenerator*		AddForceGenerator	(const ParticleForceGenerator& _forceGenerator);
	Particle*					AddParticle			(const Particle& _particle);

};



