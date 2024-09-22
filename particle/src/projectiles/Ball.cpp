#include "Ball.h"

Ball::Ball(float _angle) : Particle()
{
	float speed = 225;
	velocity = { speed * cos(_angle), speed * -sin(_angle), 0 };
	setMass(200);
	lifeTime = 15;
	damping = 0.95;
}

void Ball::update(float dt)
{
	Particle::update(dt);

}

void Ball::draw()
{
	ofSetColor({ 100, 100, 100 });
	ofDrawCircle({ position.x, position.y }, 20.);
}
