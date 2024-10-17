#pragma once

#include "../../primitives/vec3.h"
#include "../ParticleForceGenerator.h"

class Friction : public ParticleForceGenerator
{
	public: 
		Vec3 truenormal = { 1,-1,0 };
		Vec3 normal = truenormal.normalize();

		virtual void updateForce(Particle* _particle, float _dt ) override;
		virtual void drawForce(Particle* _particle) override;
		Vec3 gravity{ 0., 15., 0. };
		float mu_stat = 0.85;
		float mu_dyn = 0.7;

};

