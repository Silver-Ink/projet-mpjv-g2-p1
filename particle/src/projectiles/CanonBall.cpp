#include "CanonBall.h"

CanonBall::CanonBall(float _angle) : Particle() 
{
	velocity = { 160 * cos(_angle), -200 * sin(_angle), 0 };
	setMass(150);
	lifeTime = 8;
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