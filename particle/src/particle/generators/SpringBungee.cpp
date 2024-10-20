#include "SpringBungee.h"

void SpringBungee::updateForce(Particle* _particle, float /*_dt*/)
{
	//Vec3 springForce = _particle->getPos() - hinge->getPos();
	//float springLength = springForce.length();
	//float extension = springLength - restLength;
	//if (extension < 0)
	//{
	//	return;
	//}

	//springForce *= 1. / springLength; //Normalize

	//springForce *= -elasticConstant * extension;

	//_particle->addForce(springForce);
	//springForce *= -1;
	//hinge->addForce(springForce);

	const float lengthThreshold = 0.01;

	Vec3 spring = (_particle->getPos() - hinge->getPos());
	float currentLength = spring.length();

	float difference = currentLength - restLength;

	if (fabs(difference) > lengthThreshold)
	{
		spring *= -1. / currentLength * difference * elasticConstant;
		_particle->addForce(spring);
		spring *= -1.;
		hinge->addForce(spring);
	}
}


void SpringBungee::drawForce(Particle* _particle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::red);
	ofDrawLine((glm::vec2)_particle->getPos(), (glm::vec2)hinge->getPos());
}