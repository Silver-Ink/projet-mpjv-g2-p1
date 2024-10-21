#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"
#include "../IDrawsLine.h"

class SpringRod : public ParticleForceGenerator, public IDrawsLine
{
public:
	SpringRod(Particle* _particle, float _rodLength) :
		particle(_particle),
		rodLength(_rodLength)
	{}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

	virtual Vec3 getSecondEnd() override { return particle->getPos(); }

private:
	Particle* particle;
	float rodLength;
};

