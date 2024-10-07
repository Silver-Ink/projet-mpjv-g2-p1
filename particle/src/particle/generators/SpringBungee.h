#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"

class SpringBungee : public ParticleForceGenerator
{
	SpringBungee(Particle* _hinge, float _restLength, float _elasticConstant = .01) : 
		hinge(_hinge),
		restLength(_restLength),
		elasticConstant(_elasticConstant)
	{}
	virtual void updateForce(Particle* _particle, float _dt) override;

private:
	Particle* hinge;
	float restLength;
	float elasticConstant;
};

