#include "SpringRod.h"
#include "../Collisionner.h"

void SpringRod::updateForce(Particle* _otherParticle, float _dt)
{
	Vec3 springForce = _otherParticle->getPos() - particle->getPos();
	float springLength = springForce.length();
	float extension = springLength - rodLength;

	springForce *= 1. / springLength; //Normalize
	//Collision
	//Collisionner::repositionParticle(_otherParticle, particle, Collisionner::CollisionResult{ springForce.getNormalized(), particle->getPos(), extension });
}


void SpringRod::drawForce(Particle* _otherParticle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::blue);
	ofDrawLine((glm::vec2)_otherParticle->getPos(), (glm::vec2)particle->getPos());
}