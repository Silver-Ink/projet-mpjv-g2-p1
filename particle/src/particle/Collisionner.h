#pragma once

#include "../primitives/Vec3.h"
#include "../rigidBody/RigidBody.h"

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

	static void HandleAllCollision(std::vector<RigidBody*>& _lstRigidBody);

	static void repositionParticle(RigidBody* _rb1, RigidBody* _rb2, Collisionner::CollisionResult& _collision);
	static void applyImpulsion(RigidBody* _rb1, RigidBody* _rb2, Collisionner::CollisionResult& _collision);
};

