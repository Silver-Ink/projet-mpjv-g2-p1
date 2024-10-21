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

	typedef std::vector<ParticleForceRegistration> Register;

	void Add			(Particle* _particle, ParticleForceGenerator* _forceGenerator);
	void Remove			(int _registrationIndex);
	void Clear			()																	{ registerForceToParticle.clear(); }

	void UpdateForces	(float _dt);
	void DrawForces		();

	void destroyLineAt(int _x, int _y);

private:

	Register registerForceToParticle;
};
