#include "Laser.h"

Laser::Laser(float _angle) : Particle()
{
	velocity = { 300 * cos(_angle), -300 * sin(_angle), 0 };
	setMass(150);
	lifeTime = 20;
	damping = 1;
};

void Laser::update(float _dt)
{
	Particle::update(_dt);

}

void Laser::draw()
{
	ofSetColor(200, 0, 0);									// Red color
	ofDrawCircle(position.x, position.y, 5);				// Draw a circle

}