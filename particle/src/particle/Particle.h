#pragma once

#include "../primitives/Vec3.h"

float rng(float a, float b) { return (rand() % static_cast<int>(b - a)) + a; }

class Particle
{
public:
	Particle() : Particle(0., 0., 0.) {}
	Particle(float _x, float _y) : Particle(Vec3{ _x, _y , 0. }) {}
	Particle(float _x, float _y, float _z) : Particle(Vec3{ _x, _y , _z }) {}
	Particle(Vec3 _pos);

	void computeForces(float _dt);
	virtual void update(float _dt);
	virtual void draw();

	void setMass(float _mass) { inverseMass = (_mass != 0) ? (1 / _mass) : 999999; }
	float getMass() { return 1 / inverseMass; }
	float getinverseMass() { return inverseMass; }

	void integrate(float _dt);

	Vec3& getPos() { return position; }

protected:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	float damping{0};
	float inverseMass{1};

public:
	Vec3 accumForce;
	void addForce(const Vec3& _force);
	void clearAccum();
};

