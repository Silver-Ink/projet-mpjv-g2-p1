#pragma once
#include "primitives/Vec3.h"
#include "particle/Particle.h"
#include "particle/generators/ParticleGravity.h"
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

	void generateBlob(int nbParticle, float firmness, ParticleGravity* gravity = nullptr);

	void leftClickAt(int _x, int _y);
	void rightClickAt(int _x, int _y);

	void releaseLeftClick(int _x, int _y);
	void releaseRightClick(int _x, int _y);

	void updateGrabbed();

private:
	ParticleForceGenerator*		AddForceGenerator	(ParticleForceGenerator* _forceGenerator);
	Particle*					AddParticle			(Particle* _particle);

	Particle*					AddParticle			(const Particle& _particle);

	Vec3 grabOffset;
	Particle* grabbedParticle{ nullptr };
};



