#include "Particle.h"
#include "ofApp.h"

void Particle::update()
{
	mVelocity += mAcceleration;
	mPosition += mVelocity;
}

void Particle::draw()
{
	//ofDrawCircle(mPosition, 5.);
	//ofDrawCircle()
}


