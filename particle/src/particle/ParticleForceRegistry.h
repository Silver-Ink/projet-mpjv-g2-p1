#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
	struct ParticleForceRegistration {
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

};
