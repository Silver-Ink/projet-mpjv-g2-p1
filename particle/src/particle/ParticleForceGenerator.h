#pragma once
#include "Particle.h"

class ParticleForceGenerator {

public:
	virtual void updateForce(Particle* _particle, float _dt) = 0;
	virtual void drawForce(Particle* _particle) = 0;

};