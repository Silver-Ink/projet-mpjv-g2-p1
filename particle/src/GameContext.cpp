#include "GameContext.h"
#include "../ofMain.h"
#include "particle/generators/Friction.h"
#include "particle/generators/RegularSpring.h"
#include "particle/generators/SpringRod.h"
#include "particle/Collisionner.h"
#include "particle/generators/SpringCable.h"
#include "particle/generators/FixedSpring.h"
#include "particle/generators/BlobSpring.h"



void GameContext::init()
{
	camera.setDistance(100.);

	emptyScene();

	ParticleGravity* gravity = new ParticleGravity();

	RigidBody* rb1 = AddRigidBody(RigidBody{ {0, 0, 0} });
	rb1->setAngularSpeed({ 1, 1, 1 });

	AddForceGenerator(gravity);

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

	for each (RigidBody* rb in lstRigidBody)
	{
		rb->draw();
	}
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

GameContext::raycastResult GameContext::raycast(Vec3 _direction, float _maxLength, std::vector<RigidBody*>& lstRigidBody)
{
	return raycastResult();
}
