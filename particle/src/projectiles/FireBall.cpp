#include "FireBall.h"
#include "../ofMain.h"

FireBall::FireBall(float _angle) : Particle()
{
	initialSpeed = 500;
	velocity = { initialSpeed * cos(_angle), initialSpeed * -sin(_angle), 0 };
	setMass(20);
	lifeTime = 12;
	damping = 0.98;
}

void FireBall::update(float _dt)
{
	Particle::update(_dt);
	// The FireBall consumes itself overtime, so its mass decreases
	inverseMass /= .999;			
}

void FireBall::draw()
{
	float scale = 2.5;
	ofSetColor({ 255, 131, 48 });
	ofDrawCircle({ position.x, position.y }, (scale / inverseMass));	// scale/inverseMasse to have a circle of radius 50 at the beginning + allow decrease of the radius
	ofSetColor(ofColor::white);
	
}
