#pragma once

#include "../primitives/Vec3.h"
#include "Particle.h"

class Collisionner
{
public:
	static constexpr float restitutionCoef{ .7f };


	struct CollisionResult {
		CollisionResult(const Vec3& _normal, const Vec3& _collisionPoint, float _interpenetration) :
			normal(_normal),
			collisionPoint(_collisionPoint),
			interPenetration(_interpenetration) 
		{}
		CollisionResult() = default;

		bool isCollisionPresent{ false };
		Vec3 normal{ 0.f };
		Vec3 collisionPoint{ 0.f };
		float interPenetration{ 0.f };
	};

	static CollisionResult CheckCollision(Particle* _p1, Particle* _p2);
	static void HandleAllCollision(std::vector<Particle*>& _lstParticle);

	static void repositionParticle(Particle* _p1, Particle* _p2, Collisionner::CollisionResult& _collision);
	static void applyImpulsion(Particle* _p1, Particle* _p2, Collisionner::CollisionResult& _collision);
};

