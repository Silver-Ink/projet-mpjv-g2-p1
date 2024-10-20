#include "SpringCable.h"
#include "../Collisionner.h"


void SpringCable::updateForce(Particle* _particle, float /*_dt*/)
{
	Vec3 springForce = _particle->getPos() - hinge->getPos();
	float springLength = springForce.length();
	float extension = springLength - restLength;

	if (extension < 0)
	{
		return;
	}

	springForce *= 1. / springLength; //Normalize

	//Collision
	Collisionner::repositionParticle(_particle, hinge, Collisionner::CollisionResult{ springForce, hinge->getPos(), extension });
	
}


void SpringCable::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::red);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)hinge->getPos());
}