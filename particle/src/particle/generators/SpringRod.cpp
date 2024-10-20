#include "SpringRod.h"

void SpringRod::updateForce(Particle* _otherParticle, float _dt)
{
	Vec3 spring = _otherParticle->getPos() - particle->getPos();


	float length = spring.length();
	float extension = length - rodLength;

	spring *= 1. / length * extension;

	_otherParticle->addForce(spring*-1.);
	std::cout << length << endl;
	//particle->addForce(spring);
}


void SpringRod::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::blue);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)particle->getPos());
}