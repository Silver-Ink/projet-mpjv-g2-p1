#include "CanonBall.h"

CanonBall::CanonBall(float _angle) : Particle() 
{
	initialSpeed = 250;
	velocity = { initialSpeed * cos(_angle), -initialSpeed * sin(_angle), 0 };
	setMass(15);
	lifeTime = 20;
	damping = 0.95;
};

void CanonBall::update(float _dt)
{
	Particle::update(_dt);

}

void CanonBall::draw()
{
	ofSetColor(65, 69, 69);									// Grey color
	ofDrawCircle(position.x, position.y, 50);				// Draw a circle

}