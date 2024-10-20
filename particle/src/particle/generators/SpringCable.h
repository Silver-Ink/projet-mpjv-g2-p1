#pragma once
#include "../ParticleForceGenerator.h"

class SpringCable : public ParticleForceGenerator
{
public:
	SpringCable(Particle* _hinge, float _restLength) :
		hinge(_hinge),
		restLength(_restLength)
	{}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

private:
	Particle* hinge;
	float restLength;
};

