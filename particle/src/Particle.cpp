#include "Particle.h"
#include "ofApp.h"

Particle::Particle()
{
	position = { 0, static_cast<float>(ofGetHeight()), 0 };
	acceleration = { 0, 0, 0 };
	damping = 1;
	lifeTime = 10;
}

void Particle::computeForces(float _dt)
{
	acceleration = Vec3(0, 15, 0); //Apply Gravity
	
}

void Particle::update(float _dt)
{
	lifeTime -= _dt;
	integrate(_dt);
}

void Particle::integrate(float _dt)
{
	velocity = pow(damping,_dt)*velocity + acceleration * _dt;
	position += velocity * _dt;
}


