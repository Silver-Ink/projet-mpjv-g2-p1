#pragma once

#include "primitives/vec3.h"

float rng(float a, float b) { return (rand() % static_cast<int>(b - a)) + a; }

class Particle
{
public:

	virtual void update();
	virtual void draw() = 0;

	void setMass(float _mass) { inverseMass = 1 / _mass; }
	float getinverseMass() { return inverseMass; }

	void integrate(float _dt);

private:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	float inverseMass;
};

