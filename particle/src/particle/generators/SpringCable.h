#pragma once
#include "../ParticleForceGenerator.h"
#include "../IDrawsLine.h"

class SpringCable : public ParticleForceGenerator, public IDrawsLine
{
public:
	SpringCable(Particle* _hinge, float _restLength) :
		hinge(_hinge),
		restLength(_restLength)
	{}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

	virtual Vec3 getSecondEnd() override { return hinge->getPos(); }

private:
	Particle* hinge;
	float restLength;
};

