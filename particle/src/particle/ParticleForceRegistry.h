#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
public:
	struct ParticleForceRegistration {
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

};
