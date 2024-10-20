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
					// Replace les particule pour qu'elles ne se supperposent pas
					float massP1 = p1->getMass();
					float massP2 = p2->getMass();

					Vec3 deltaP1 = - massP2 / (massP1 + massP2) * collision.interPenetration * collision.normal;
					Vec3 deltaP2 =   massP1 / (massP1 + massP2) * collision.interPenetration * collision.normal;

					p1->getPos() += deltaP1;
					p2->getPos() += deltaP2;



					//Applique l'impulsion
					Vec3 velocityRelative = p1->getVelocity() - p2->getVelocity();

					float impulsionStrength = ( (restitutionCoef + 1.f) * velocityRelative.dot(collision.normal) ) /
					//						  ----------------------------------------------------------------------
													   ( p1->getinverseMass() + p2->getinverseMass() );

					p1->addForce( -impulsionStrength * collision.normal * p1->getinverseMass() );
					p2->addForce(  impulsionStrength * collision.normal * p2->getinverseMass() );
				}
			}
		}
	}
}
