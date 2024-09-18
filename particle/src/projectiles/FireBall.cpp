#include "FireBall.h"
#include "../ofMain.h"

FireBall::FireBall(float _angle) : Particle()
{
	float speed = 200;
	velocity = { speed * cos(_angle), speed * -sin(_angle), 0 };
	setMass(120);
	lifeTime = 8;
}

void FireBall::update(float _dt)
{
	Particle::update(_dt);
	// The FireBall consumes itself overtime, so its mass decreases
	// invMass_{f+1} = 1 / ( mass * coef/sec) 
	inverseMass /= .7 * _dt;
}

void FireBall::draw()
{
	ofSetColor({ 255, 131, 48 });
	ofDrawCircle({ position.x, position.y}, 50.);
	ofSetColor(ofColor::white);
	
}
