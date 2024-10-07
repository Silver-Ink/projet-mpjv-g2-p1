#pragma once
#include "primitives/Vec3.h"
#include "particle/Particle.h"
#include "particle/ParticleForceGenerator.h"
#include "particle/ParticleForceRegistry.h"

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
	typedef std::vector<ParticleForceRegistry::ParticleForceRegistration> Register;

public:
	void		update(float _dt);
	void		draw();

public:
	Register particleForceRegister;
	std::vector<Particle> lstParticle;
	std::vector<ParticleForceGenerator> lstForceGenerator;
};

