#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
public:
	Vec3 gravity { 0., -9.81, 0. };

	virtual void updateForce	(Particle* _particle, float _dt)	override;
	virtual void drawForce		(Particle* _particle)				override {}
};

#define ADD_GRAVITY( _PARTICLE )\
particleForceRegistry.Add(_PARTICLE, gravity);
