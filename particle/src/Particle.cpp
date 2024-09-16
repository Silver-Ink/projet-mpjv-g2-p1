#include "Particle.h"
#include "ofApp.h"

void Particle::update()
{
	integrate(1. / 60.); //TODO : change to deltatime
}

void Particle::draw()
{
	//ofDrawCircle(mPosition, 5.);
	//ofDrawCircle()
}

void Particle::integrate(float _dt)
{
	velocity += acceleration * _dt;
	position += velocity * _dt;
}


