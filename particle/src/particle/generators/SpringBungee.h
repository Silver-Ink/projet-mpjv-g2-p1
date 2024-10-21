#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"
#include "../IDrawsLine.h"

class SpringBungee : public ParticleForceGenerator, public IDrawsLine
{
public:
	SpringBungee(Particle* _hinge, float _restLength, float _elasticConstant = .01) : 
		hinge(_hinge),
		restLength(_restLength),
		elasticConstant(_elasticConstant)
	{}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

	virtual Vec3 getSecondEnd() override { return hinge->getPos(); }

private:
	Particle* hinge;
	float restLength;
	float elasticConstant;
};

