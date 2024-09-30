#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
public:
	Vec3 gravity { 0., -15., 0. };

	virtual void updateForce(Particle* _particle, float _dt) override;
};

