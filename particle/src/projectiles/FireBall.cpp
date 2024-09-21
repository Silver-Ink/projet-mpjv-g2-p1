#include "FireBall.h"
#include "../ofMain.h"

FireBall::FireBall(float _angle) : Particle()
{
	float speed = 175;
	velocity = { speed * cos(_angle), speed * -sin(_angle), 0 };
	setMass(200);
	lifeTime = 8;
}

void FireBall::update(float _dt)
{
	Particle::update(_dt);
	// The FireBall consumes itself overtime, so its mass decreases
	// invMass_{f+1} = 1 / ( mass * coef/sec) 
	inverseMass /= .999;			// add *_dt ? --> consumes too fast
}

void FireBall::draw()
{
	float scale = 0.25;
	ofSetColor({ 255, 131, 48 });
	ofDrawCircle({ position.x, position.y }, ( scale / inverseMass));	// scale/inverseMasse to have a cirlce of radius 50 at the beginning
	ofSetColor(ofColor::white);
	
}
