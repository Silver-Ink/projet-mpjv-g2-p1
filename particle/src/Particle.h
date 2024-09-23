#pragma once

#include "primitives/Vec3.h"

float rng(float a, float b) { return (rand() % static_cast<int>(b - a)) + a; }

class Particle
{
public:
	Particle();

	void computeForces(float _dt);
	virtual void update(float _dt);
	virtual void draw() = 0;

	void setMass(float _mass) { inverseMass = 1 / _mass; }
	float getinverseMass() { return inverseMass; }
	float getlifeTime() { return lifeTime; }

	void integrate(float _dt);

	virtual void collideBorders();

protected:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	float damping;
	float inverseMass;
	float lifeTime;				
};

