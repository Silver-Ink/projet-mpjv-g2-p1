#include "GameContext.h"
#include "../ofMain.h"
#include "particle/generators/Friction.h"
#include "particle/generators/RegularSpring.h"
#include "particle/generators/SpringRod.h"
#include "particle/Collisionner.h"
#include "particle/generators/SpringCable.h"
#include "particle/generators/FixedSpring.h"
#include "particle/generators/BlobSpring.h"
#include "rigidBody/RigidBody.h"




void GameContext::init()
{
	camera.setDistance(100.);

	emptyScene();

	ParticleGravity* gravity = new ParticleGravity();

	RigidBody* rb1 = AddRigidBody(RigidBody{ {0, 0, 0}, 0.0001 });
	//rb1->setAngularSpeed({ 1, 1, 1 });
	rb1->massCenter.addForce({ 0, 500, 0 }, { 30, 0, 0 });

	AddForceGenerator(gravity);
	particleForceRegistry.Add(&(rb1->massCenter), gravity);

}

void GameContext::update(float _dt)
{
	
	particleForceRegistry.UpdateForces(_dt);

	Collisionner::HandleAllCollision(lstParticle);

	for (auto particle : lstParticle)
	{
		particle->computeForces(_dt);
	}

	for (auto particle : lstParticle)
	{
		particle->update(_dt);
	}
	for (RigidBody* rb : lstRigidBody)
	{
		rb->update(_dt);
	}


	updateCamera(_dt);
}

void GameContext::draw()
{

	camera.begin();
	ofNoFill();
	//ofDrawBox(30.);
	//ofDrawCylinder({0., 30., 0.}, 5., 30.);


	//particleForceRegistry.DrawForces();
	//for (auto particle : lstParticle)
	//{
	//	particle->draw();
	//}

	raycastResult rc = raycast(
		Vec3::fromGLM_vec3(camera.getGlobalPosition()),
		Vec3::fromGLM_vec3(camera.getLookAtDir()),
		100, lstRigidBody);

	for each (RigidBody* rb in lstRigidBody)
	{
		if (rb == rc.collisionner)
		{
			ofSetColor(ofColor::orangeRed);
		}
		rb->draw();
		ofSetColor(ofColor::white);
	}

	ofDrawSphere(camera.getGlobalPosition() + camera.getLookAtDir() * rc.rayLength, 1);


	//ofDrawArrow({ 0,0,0 }, (glm::vec3)testArrow);
	camera.end();
}

void GameContext::emptyScene()
{
	particleForceRegistry.Clear();
	for (auto p : lstParticle)
	{
		delete p;
	}
	lstParticle.clear();
	for (auto fg : lstForceGenerator)
	{
		delete fg;
	}
	lstForceGenerator.clear();
}

void GameContext::setInputCamera(float _axisX, float _axisY, float _axisZ)
{
	axisX = _axisX;
	axisY = _axisY;
	axisZ = _axisZ;
}


void GameContext::updateCamera(float _dt)
{
	if (axisX || axisY || axisZ)
	{
		glm::vec3 forward = camera.getLookAtDir() * axisZ;
		glm::vec3 side = camera.getSideDir() * axisX;

		//float left = forward + PI / 2.;
		//std::cout << forward << "  " << left << endl;
		float speed = 100. * _dt;

		camera.setPosition(camera.getGlobalPosition() + glm::vec3{
			forward.x + side.x ,
			axisY,
			forward.z + side.z }
			*speed);
	}
}

void GameContext::ResetCamera()
{
	camera.reset();
	camera.setDistance(100.);
}

ParticleForceGenerator* GameContext::AddForceGenerator(ParticleForceGenerator* _forceGenerator)
{
	lstForceGenerator.emplace_back(_forceGenerator);
	return _forceGenerator;
}

Particle* GameContext::AddParticle(Particle* _particle)
{
	lstParticle.emplace_back(_particle); 
	return _particle;
}

Particle* GameContext::AddParticle(const Particle& _particle)
{
	Particle* newParticle = new Particle(_particle);
	lstParticle.emplace_back(newParticle);
	return newParticle;
}

RigidBody* GameContext::AddRigidBody(RigidBody* _rigidBody)
{
	lstRigidBody.emplace_back(_rigidBody);
	return _rigidBody;
}

RigidBody* GameContext::AddRigidBody(const RigidBody& _rigidBody)
{
	RigidBody* newRigidBody = new RigidBody(_rigidBody);
	lstRigidBody.emplace_back(newRigidBody);
	return newRigidBody;
}

GameContext::raycastResult GameContext::raycast(Vec3 _startPoint, Vec3 _direction, float _maxLength, std::vector<RigidBody*>& _lstRigidBody)
{
	_direction.normalize();

	float distance = 0.;

	do {
		distance++;
		
		Vec3 rayHead = _startPoint + distance * _direction;

		for (RigidBody* rb : _lstRigidBody)
		{
			if (rb->containsPoint(rayHead))
			{
				float backAjustement = .5;
				float dichoStep = backAjustement;
				for (size_t i = 0; i < 10; i++)
				{
					dichoStep /= 2.;
					if (rb->containsPoint(rayHead - backAjustement * _direction))
						//Intersection is closer
						backAjustement += dichoStep;
					else
						//Intersection is farther
						backAjustement -= dichoStep;
				}
				raycastResult r{};
				r.collisionner = rb;
				r.collisionPosAbsolute = rayHead - backAjustement * _direction;
				r.rayLength = distance - backAjustement;
				return r;
			}
		}

	} while (distance < _maxLength);

	return raycastResult();
}
