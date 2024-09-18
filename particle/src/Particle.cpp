#include "Particle.h"
#include "ofApp.h"

void Particle::computeForces(float dt)
{
	acceleration = Vec3(0, 9.8, 0); //Apply Gravity
	
}

void Particle::update(float _dt)
{
	integrate(_dt); 
}

void Particle::integrate(float _dt)
{
	velocity += acceleration * _dt;
	position += velocity * _dt;
}


