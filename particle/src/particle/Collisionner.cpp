#include "Collisionner.h"

void Collisionner::HandleAllCollision(Octree& _emptyOctree, std::vector<RigidBody*>& _lstRigidBody)
{
	for (RigidBody* rb : _lstRigidBody)
	{
		_emptyOctree.insert(rb);
	}

	std::vector<RigidBody*> possibleCollision;

	using RbPair = std::pair<RigidBody*, RigidBody*>;
	std::vector<RbPair> lstCollisionProcessed; //Normalement pas très grand

	for (RigidBody* rb1 : _lstRigidBody)
	{
		_emptyOctree.query(rb1, possibleCollision);

		for (RigidBody* rb2 : possibleCollision) // Collision élargie (Octree)
		{
			bool isNewCollision = true;
			//Vérifie si la collision n'as pas déjà eu lieu dans l'autre sens
			for (RbPair& pair : lstCollisionProcessed)
			{
				if (pair.first	== rb2 && 
					pair.second == rb1)
				{
					isNewCollision = false;
					break;
				}
			}

			if (isNewCollision && rb1->contact(*rb2)) // Collision élargie (Volume englobant)
			{
				rb1->isColliding = true;
				rb2->isColliding = true;

				SatCollisionResult collisionData = rb1->checkCollision(*rb2);
				if (collisionData.isCollisionPresent)
				{
					repositionBody(rb1, rb2, collisionData);
					applyImpulsion(rb1, rb2, collisionData);

				}

				lstCollisionProcessed.emplace_back(RbPair{ rb1, rb2 });
			}
		}

		//possibleCollision.clear();
	}

	//for (int i = 0; i < _lstRigidBody.size(); i++)
	//{
	//	for (int j = i; j < _lstRigidBody.size(); j++) // On ne teste que la collision [a;b] et pas [b;a]
	//	{
	//		if (i != j)
	//		{
	//			RigidBody* rb1 = _lstRigidBody[i];
	//			RigidBody* rb2 = _lstRigidBody[j];

	//			if (rb1->contact(*rb2)) // Collision élargie
	//			{
	//				rb1->isColliding = true;
	//				rb2->isColliding = true;
	//				//repositionParticle(rb1, rb2, collision);

	//				//applyImpulsion(rb1, rb2, collision);
	//			}
	//			else {
	//				rb1->isColliding = false;
	//				rb2->isColliding = false;
	//			}
	//		}
	//	}
	//}
}

void Collisionner::repositionBody(RigidBody* _rb1, RigidBody* _rb2, SatCollisionResult& _collisionData)
{
	// Replace les particule pour qu'elles ne se supperposent pas
	float massP1 = _rb1->massCenter.getMass();
	float massP2 = _rb2->massCenter.getMass();

	Vec3 normal = _collisionData.normal;

	Vec3 deltaP1 = -massP2 / (massP1 + massP2) * _collisionData.interpenetration * normal;
	Vec3 deltaP2 =  massP1 / (massP1 + massP2) * _collisionData.interpenetration * normal;

	//if (deltaP1.length() > 2)
	{
		std::cout << deltaP1.length() << endl;

	}

	_rb1->massCenter.getPos() += deltaP1;
	_rb2->massCenter.getPos() += deltaP2;
}

void Collisionner::applyImpulsion(RigidBody* _rb1, RigidBody* _rb2, SatCollisionResult& _collisionData)
{
	Vec3 normal = _collisionData.normal;

	//Applique l'impulsion
	Vec3 velocityRelative = _rb1->massCenter.getVelocity() - _rb2->massCenter.getVelocity();

	float impulsionStrength = (	(restitutionCoef + 1.f) * velocityRelative.dot(normal) ) /
	//						  ----------------------------------------------------------------------
							(_rb1->massCenter.getinverseMass() + _rb2->massCenter.getinverseMass());

	//if (impulsionStrength < 0.)
		//std::cout << impulsionStrength << "    " << velocityRelative.x << "; " << velocityRelative.y << "; " << velocityRelative.z << " -> " << velocityRelative.length() << endl;

	_rb1->massCenter.addImpulsion(-impulsionStrength * normal * _rb1->massCenter.getinverseMass(), _collisionData.collisionPoint);
	_rb2->massCenter.addImpulsion(impulsionStrength * normal * _rb2->massCenter.getinverseMass(), _collisionData.collisionPoint);
}
