#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"

class SpringRod : public ParticleForceGenerator
{
	SpringRod(Particle* _particle, float _rodLength) :
		particle(_particle),
		rodLength(_rodLength)
	{}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

private:
	Particle* particle;
	float rodLength;
};

