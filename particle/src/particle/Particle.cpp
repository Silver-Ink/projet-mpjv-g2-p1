#include "Particle.h"
#include "../ofApp.h"

Particle::Particle()
{
	position = { 0, static_cast<float>(ofGetHeight()), 0 };
	acceleration = { 0, 0, 0 };
	damping = 1;
	lifeTime = 10;
	initialSpeed = 100;
}

void Particle::computeForces(float _dt)
{
	acceleration = Vec3(0, 15, 0); //Apply Gravity
	acceleration *= 1 / getinverseMass();
	
}

void Particle::update(float _dt)
{
	lifeTime -= _dt;
	integrate(_dt);
	collideBorders();
}

void Particle::integrate(float _dt)
{
	velocity = pow(damping,_dt)*velocity + acceleration * _dt;
	position += velocity * _dt;
}

void Particle::collideBorders()
{
	if ((position.y >= ofGetHeight() && velocity.y > 0) || (position.y <= 0 && velocity.y < 0))
	{
		velocity.y *= -1;
	}
	if ((position.x >= ofGetWidth() && velocity.x > 0) || (position.x <= 0 && velocity.x < 0))
	{
		velocity.x *= -1;
	}
}
