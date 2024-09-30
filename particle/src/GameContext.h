#pragma once
#include "primitives/Vec3.h"
#include "particle/Particle.h"

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
};

