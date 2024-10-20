#pragma once

#include "../primitives/Vec3.h"
#include "Particle.h"

class Collisionner
{
public:
	static constexpr float restitutionCoef{ .7f };


	struct CollisionResult {
		bool isCollisionPresent{ false };
		Vec3 normal{ 0.f };
		Vec3 collisionPoint{ 0.f };
		float interPenetration{ 0.f };
	};

	static CollisionResult CheckCollision(Particle* _p1, Particle* _p2);
	static void HandleAllCollision(std::vector<Particle*>& _lstParticle);
};

