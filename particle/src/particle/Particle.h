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
	void freeze();
	void unfreeze();
	virtual void update(float _dt);
	virtual void draw();

	void	setMass			(float _mass) { inverseMass = (_mass != 0) ? (1 / _mass) : 999999; }
	float	getMass			() { return 1.f / inverseMass; }
	float	getinverseMass	() { return inverseMass; }
	Vec3&	getPos			() { return position; }
	Vec3	getVelocity		() { return velocity; }

	void integrate(float _dt);



protected:
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	float damping{.8};
	float inverseMass{10};
	bool frozen{ false };

	static constexpr float gBorder{ 3. };

public:
	float radius{ 10. };
	Vec3 accumForce;
	void addForce(const Vec3& _force, const Vec3& applicationPoint);
	void clearAccum();
};

