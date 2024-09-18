#include "Particle.h"
#include "ofApp.h"

void Particle::computeForces(float dt)
{
	acceleration = Vec3(0, 99.8, 0); //Apply Gravity
}

void Particle::update(float dt)
{
	integrate(1. / 60.); //TODO : change to deltatime
}

void Particle::integrate(float _dt)
{
	velocity += acceleration * _dt;
	position += velocity * _dt;
}


