#include "CanonBall.h"

void CanonBall::update(float _dt)
{
	Particle::update(_dt);

}

void CanonBall::draw()
{
	ofSetColor(65, 69, 69);									// Grey color
	//ofFill();												// Fill the shape
	ofDrawCircle(position.x, position.y, 50);				// Draw a circle

}