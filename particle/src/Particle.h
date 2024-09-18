#pragma once

#include "primitives/Vec3.h"

float rng(float a, float b) { return (rand() % static_cast<int>(b - a)) + a; }

class Particle
{
public:

	void computeForces(float dt);
	virtual void update(float dt);
	virtual void draw() = 0;

	void setMass(float _mass) { inverseMass = 1 / _mass; }
	float getinverseMass() { return inverseMass; }

	void integrate(float _dt);

protected:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	float inverseMass;
};

