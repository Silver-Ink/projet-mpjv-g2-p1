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
#include "primitives/Octree.h"




void GameContext::init()
{
	camera.setDistance(100.);

	emptyScene();

	ParticleGravity* gravity = new ParticleGravity();

	RigidBody* rb1 = AddRigidBody(RigidBody{ {0, 0, 0}, 0.0001 });

	rb1->massCenter.addForce({ 0, 500, 0 }, { 30, 0, 0 });

	AddForceGenerator(gravity);
	particleForceRegistry.Add(&(rb1->massCenter), gravity);

}

void GameContext::update(float _dt)
{
	updateCamera(_dt);

	raycastData = raycast(
		Vec3::fromGLM_vec3(camera.getGlobalPosition()),
		Vec3::fromGLM_vec3(camera.getLookAtDir()),
		100, lstRigidBody);

	if (strength != 0. && raycastData.collisionner)
	{
		Vec3 force = Vec3::fromGLM_vec3(camera.getLookAtDir()).normalize() * 100.f;
		raycastData.collisionner->massCenter.addForce(force, raycastData.collisionPosAbsolute);
		strength = 0;
	}
	
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

	glm::vec3 pos = camera.getGlobalPosition();
	Octree octree{ {pos.x, pos.y-300.f, pos.z, 1000.f, 1000.f, 1000.f} };
	for (RigidBody* rb : lstRigidBody)
	{
		octree.insert(rb);
	}

	std::vector<RigidBody*> possibleCollision;
	for (RigidBody* rb : lstRigidBody)
	{
		octree.query(rb, possibleCollision);

		// Test collisions here

		possibleCollision.clear();
	}
	
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
		if (rb == raycastData.collisionner)
		{
			ofSetColor(ofColor::orangeRed);
		}
		rb->draw();
		ofSetColor(ofColor::white);
	}

	ofDrawSphere(camera.getGlobalPosition() + camera.getLookAtDir() * raycastData.rayLength, 1);


	//ofDrawArrow({ 0,0,0 }, (glm::vec3)testArrow);
	camera.end();
	//ofDrawCircle(glm:::vec3(0,0,  rc.rayLength), 5.);
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

void GameContext::spawnBox(float _length, float _height, float _width, float _density, bool _addGravity)
{
	_height = _height == -1.f ? _length : _height;
	_width= _width == -1.f ? _height : _width;

	float dist = std::max(std::max(_length, _height), _width);

	Vec3 pos = Vec3::fromGLM_vec3(camera.getGlobalPosition()) +
		Vec3::fromGLM_vec3(camera.getLookAtDir()).normalize() * dist * 1.5f;

	RigidBody* rb = new RigidBody(pos, _density, _length, _height, _width, Quaternion::IDENTITY);
	lstRigidBody.emplace_back(rb);

	if (_addGravity)
	{
		ParticleGravity* gravity = new ParticleGravity();
		AddForceGenerator(gravity);
		particleForceRegistry.Add(&(rb->massCenter), gravity);
	}
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
	float longStep= 10.;

	do {
		distance+=longStep;
		
		Vec3 rayHead = _startPoint + distance * _direction;

		for (RigidBody* rb : _lstRigidBody)
		{
			if (rb->containsPoint(rayHead))
			{
				float backAjustement = longStep / 2.;
				float dichoStep = backAjustement;
				for (size_t i = 0; i < 20; i++)
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
