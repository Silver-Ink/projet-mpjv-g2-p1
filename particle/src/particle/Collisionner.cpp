#include "Collisionner.h"

Collisionner::CollisionResult Collisionner::CheckCollision(Particle* _p1, Particle* _p2)
{
	CollisionResult result{};

	Vec3 difference = _p2->getPos() - _p1->getPos();
	float sqDist = difference.sqLength();

	float radSum = _p1->radius + _p2->radius;
	float sqRad = radSum * radSum;

	if (sqDist < sqRad) // Collision
	{
		result.isCollisionPresent = true;
		result.normal = difference.getNormalized();
		result.collisionPoint = _p1->getPos() + _p1->radius * result.normal;
		result.interPenetration = radSum - sqrt(sqDist);
	}

	return result;
}

void Collisionner::HandleAllCollision(std::vector<Particle*>& _lstParticle)
{
	for (int i = 0; i < _lstParticle.size(); i++)
	{
		for (int j = i; j < _lstParticle.size(); j++) // On ne teste que la collision [a;b] et pas [b;a]
		{
			if (i != j)
			{
				Particle* p1 = _lstParticle[i];
				Particle* p2 = _lstParticle[j];
				CollisionResult collision = CheckCollision(p1, p2);

				if (collision.isCollisionPresent)
				{
					repositionParticle(p1, p2, collision);

					applyImpulsion(p1, p2, collision);
				}
			}
		}
	}
}

void Collisionner::repositionParticle(Particle* _p1, Particle* _p2, Collisionner::CollisionResult& _collision)
{
	// Replace les particule pour qu'elles ne se supperposent pas
	float massP1 = _p1->getMass();
	float massP2 = _p2->getMass();

	Vec3 deltaP1 = -massP2 / (massP1 + massP2) * _collision.interPenetration * _collision.normal;
	Vec3 deltaP2 =  massP1 / (massP1 + massP2) * _collision.interPenetration * _collision.normal;

	_p1->getPos() += deltaP1;
	_p2->getPos() += deltaP2;
}

void Collisionner::applyImpulsion(Particle* _p1, Particle* _p2, Collisionner::CollisionResult& _collision)
{
	//Applique l'impulsion
	Vec3 velocityRelative = _p1->getVelocity() - _p2->getVelocity();

	float impulsionStrength = (	(restitutionCoef + 1.f) * velocityRelative.dot(_collision.normal) ) /
	//						  ----------------------------------------------------------------------
										(_p1->getinverseMass() + _p2->getinverseMass());

	_p1->addForce(-impulsionStrength * _collision.normal * _p1->getinverseMass(), _collision.collisionPoint);
	_p2->addForce(impulsionStrength * _collision.normal * _p2->getinverseMass(), _collision.collisionPoint);
}
