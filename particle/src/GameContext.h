#pragma once
#include "primitives/vec3.h"


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
	GameContext() {};

public:
	GameContext(const GameContext &) = delete;
	void operator=(const GameContext &) = delete;

// INTERFACE

public:
	void update(float dt);
	void draw();

private:
	Vec3 screenSize;
	float aimAngle = 0;
};

