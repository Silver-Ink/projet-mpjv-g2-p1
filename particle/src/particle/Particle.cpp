#include "Particle.h"
#include "../ofApp.h"

Particle::Particle()
{
	position = { 0, 0, 0 };
	acceleration = { 0, 0, 0 };
	accumForce = { 0, 0, 0 };

}

void Particle::computeForces(float _dt)
{
	acceleration = accumForce * getinverseMass();
}

void Particle::update(float _dt)
{
	integrate(_dt);
}

void Particle::integrate(float _dt)
{
	velocity = pow(damping,_dt)*velocity + acceleration * _dt;
	position += velocity * _dt;
}

void Particle::addForce(const Vec3& _force)
{
	accumForce += _force;
}

void Particle::clearAccum()
{
	accumForce = { 0, 0, 0 };
}

