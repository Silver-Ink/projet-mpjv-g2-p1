#pragma once
#include "primitives/Vec3.h"
#include "Particle.h"

enum EProjectile {
	EProjectile_Ball,
	EProjectile_CanonBall,
	EProjectile_FireBall,
	EProjectile_Laser
};



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
	void		update(float _dt);
	void		draw();

	std::vector<Particle*> lstParticle;

private:
	bool updateThrower(float _dt);

	float aimAngle = 0;
	EProjectile currentProjectile = EProjectile_Laser;
	float throwerCooldown = 0;
	float throwerCooldownTimer = 1. / 50.;
};

