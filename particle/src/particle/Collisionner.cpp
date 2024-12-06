#include "Collisionner.h"

void Collisionner::HandleAllCollision(std::vector<RigidBody*>& _lstRigidBody)
{
	for (int i = 0; i < _lstRigidBody.size(); i++)
	{
		for (int j = i; j < _lstRigidBody.size(); j++) // On ne teste que la collision [a;b] et pas [b;a]
		{
			if (i != j)
			{
				RigidBody* rb1 = _lstRigidBody[i];
				RigidBody* rb2 = _lstRigidBody[j];

				if (rb1->contact(*rb2)) // Collision élargie
				{
					rb1->isColliding = true;
					rb2->isColliding = true;
					//repositionParticle(rb1, rb2, collision);

					//applyImpulsion(rb1, rb2, collision);
				}
				else {
					rb1->isColliding = false;
					rb2->isColliding = false;
				}
			}
		}
	}
}

void Collisionner::repositionParticle(RigidBody* _rb1, RigidBody* _rb2, Collisionner::CollisionResult& _collision)
{
	// Replace les particule pour qu'elles ne se supperposent pas
	float massP1 = _rb1->massCenter.getMass();
	float massP2 = _rb2->massCenter.getMass();

	Vec3 deltaP1 = -massP2 / (massP1 + massP2) * _collision.interPenetration * _collision.normal;
	Vec3 deltaP2 =  massP1 / (massP1 + massP2) * _collision.interPenetration * _collision.normal;

	_rb1->massCenter.getPos() += deltaP1;
	_rb2->massCenter.getPos() += deltaP2;
}

void Collisionner::applyImpulsion(RigidBody* _rb1, RigidBody* _rb2, Collisionner::CollisionResult& _collision)
{
	//Applique l'impulsion
	Vec3 velocityRelative = _rb1->massCenter.getVelocity() - _rb2->massCenter.getVelocity();

	float impulsionStrength = (	(restitutionCoef + 1.f) * velocityRelative.dot(_collision.normal) ) /
	//						  ----------------------------------------------------------------------
										(_rb1->massCenter.getinverseMass() + _rb2->massCenter.getinverseMass());

	_rb1->massCenter.addForce(-impulsionStrength * _collision.normal * _rb1->massCenter.getinverseMass(), _collision.collisionPoint);
	_rb2->massCenter.addForce(impulsionStrength * _collision.normal * _rb2->massCenter.getinverseMass(), _collision.collisionPoint);
}
