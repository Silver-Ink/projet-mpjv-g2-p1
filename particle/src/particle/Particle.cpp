#include "Particle.h"
#include "../ofApp.h"



Particle::Particle(Vec3 _pos) : position(_pos)
{
	acceleration = { 0, 0, 0 };
	clearAccum();
}

void Particle::computeForces(float _dt)
{
	acceleration = accumForce * getinverseMass();
}

void Particle::integrate(float _dt)
{
	velocity = pow(damping,_dt)*velocity + acceleration * _dt;
	//velocity = velocity + acceleration * _dt;
	position += velocity * _dt;
}

void Particle::addForce(const Vec3& _force)
{
	accumForce += _force;
}

void Particle::clearAccum()
{
	accumForce = { 0, 0, 0 };
}

void Particle::update(float _dt)
{
	integrate(_dt);
	clearAccum();
}

void Particle::draw()
{

	ofSetColor(ofColor::white);
	ofDrawCircle((glm::vec2)position, radius);
	ofSetColor(ofColor::darkSlateBlue);
	ofDrawCircle((glm::vec2)position, radius - gBorder);
}