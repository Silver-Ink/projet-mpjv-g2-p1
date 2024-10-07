#pragma once

#include "../primitives/Vec3.h"

float rng(float a, float b) { return (rand() % static_cast<int>(b - a)) + a; }

class Particle
{
public:
	Particle();

	void computeForces(float _dt);
	virtual void update(float _dt);
	virtual void draw();

	void setMass(float _mass) { inverseMass = (_mass != 0) ? (1 / _mass) : 999999; }
	float getMass() { return 1 / inverseMass; }
	float getinverseMass() { return inverseMass; }
	float getlifeTime() { return lifeTime; }

	void integrate(float _dt);

	Vec3& getPos() { return position; }

protected:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	float damping;
	float inverseMass;
	float lifeTime;
	int initialSpeed;

public:
	Vec3 accumForce;
	void addForce(const Vec3& _force);
	void clearAccum();
};

