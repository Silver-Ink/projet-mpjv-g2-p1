#include "Laser.h"

Laser::Laser(float _angle) : Particle()
{
	velocity = { 3000 * cos(_angle), -3000 * sin(_angle), 0 };
	setMass(0.00001);
	lifeTime = 10;
	damping = 1;

	angle = _angle;
	length = 100.;
};

void Laser::update(float _dt)
{
	Particle::update(_dt);

}

void Laser::draw()
{
	ofSetLineWidth(2.5);
	ofSetColor(200, 0, 0);
	ofDrawLine(position.x, position.y, position.x + length * cos(angle), position.y - length * sin(angle));		// Draw a line
}

void Laser::collideBorders()
{
	if ((position.y >= ofGetHeight() && velocity.y > 0) || (position.y <= 0 && velocity.y < 0))
	{
		velocity.y *= -1;
		angle *= -1;
	}

	if ((position.x >= ofGetWidth() && velocity.x > 0) || (position.x <= 0 && velocity.x <0))
	{
		velocity.x *= -1;
		angle = 3.14 - angle;
	}
}
