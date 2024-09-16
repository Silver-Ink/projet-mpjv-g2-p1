#pragma once

#include "primitives/vec3.h"

float rng(float a, float b) { return (rand() % static_cast<int>(b - a)) + a; }

class Particle
{
public:
	Particle(float maxTrans, float maxVel, float maxAcc) : mPosition(rng(-maxTrans, maxTrans)), mVelocity(rng(-maxVel, maxVel)), mAcceleration(rng(-maxAcc, maxAcc)) {}

	void update();
	void draw();

	void setMass(float _mass) { inverseMass = 1 / _mass; }
	float getinverseMass() { return inverseMass; }

private:
	Vec3 mPosition;
	Vec3 mVelocity;
	Vec3 mAcceleration;
	float inverseMass;
};

