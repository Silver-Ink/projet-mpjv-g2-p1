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
	ParticleGravity* gravity = new ParticleGravity();
	AddForceGenerator(gravity);


	//generateTestInterpenetration(gravity);
	//generateTestRestContact(gravity);
	//generateTestCable(gravity);
	//generateTestRod(gravity);
	//generateTestFixedSpring(gravity);
	//generateTestRegularSpring(gravity);
	//generateTestBungee(gravity);
	//generateTestBlobSpring(gravity);

	generateBlob(10, 1., gravity);

	Particle* floor = AddParticle({ 300, 10600 });
	floor->radius = 10000.;
	floor->setMass(10000.);
}
void GameContext::Testing() {

	Particle* p = new Particle(500, 500);

	lstParticle.emplace_back(p);

	ParticleGravity* gravity = new ParticleGravity();

	lstForceGenerator.emplace_back(gravity);
	

	//doit on mettre la force normal avec la friction ou en dehors?
	Friction* friction = new Friction();
	lstForceGenerator.emplace_back(friction);
	particleForceRegistry.Add(p, friction);
	particleForceRegistry.Add(p, gravity);
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


	updateGrabbed();
}

void GameContext::draw()
{
	particleForceRegistry.DrawForces();
	for (auto particle : lstParticle)
	{
		particle->draw();
	}
}

void GameContext::generateBlob(int nbParticle, float firmness, ParticleGravity* gravity/* = nullptr*/)
{
	float radius = 150.;
	float x = 300.f;
	float y = 300.f;


	std::vector<Particle*> lstBlobParticle;
	lstBlobParticle.reserve(nbParticle);
	for (int i = 0; i < nbParticle; i++)
	{
		float angle = (float)i / nbParticle * 2 * PI;
		Particle* p = AddParticle({ x + cos(angle) * radius, y + sin(angle) * radius});
		lstBlobParticle.emplace_back(p);

		if (gravity)
		{
			ADD_GRAVITY(p)
		}
	}

	for (int i = 0; i < nbParticle; i++)
	{
		Particle* p1 = lstBlobParticle[i];
		for (int j = 0; j < nbParticle; j++)
		{
			if (i != j)
			{
				Particle* p2 = lstBlobParticle[j];
				float length = Vec3{ p1->getPos() - p2->getPos() }.length();

				BlobSpring* spring = new BlobSpring(p1, length, length * 1.6);
				AddForceGenerator(spring);
				particleForceRegistry.Add(p2, spring);
			}
		}
	}
}

void GameContext::generateTestInterpenetration(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300. , 0. });
	Particle* p2 = AddParticle({ 305. , 200. });
	Particle* p3 = AddParticle({ 248. , 400. });
	Particle* p4 = AddParticle({ 240. , 600. });

	p1->addForce({ 0., 1500., 0. });
	//ADD_GRAVITY(p1)
	//ADD_GRAVITY(p1)
	//ADD_GRAVITY(p1)
}

void GameContext::generateTestRestContact(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 305. , 0. }); 
	Particle* p2 = AddParticle({ 300. , 1100. }); //Contact point at 300; 100

	p2->setMass(10000.);
	p2->radius = 1000.;

	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)
	
}

void GameContext::generateTestCable(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300. , 1100. }); 

	Particle* p2 = AddParticle({ 260., 0. });
	Particle* p3 = AddParticle({ 340., 0. });

	p1->setMass(10000.);
	p1->radius = 1000.;

	SpringCable* cable = new SpringCable(p2, 250.);
	AddForceGenerator(cable);
	particleForceRegistry.Add(p3, cable);

	ADD_GRAVITY(p2)
	ADD_GRAVITY(p3)
}

void GameContext::generateTestRod(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300., 200. });
	Particle* p2 = AddParticle({ 350., 100. });

	SpringRod* rod = new SpringRod(p1, 200);
	AddForceGenerator(rod);
	particleForceRegistry.Add(p2, rod);

	ADD_GRAVITY(p2)
	ADD_GRAVITY(p2)
	ADD_GRAVITY(p2)
}

void GameContext::generateTestFixedSpring(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300., 200. });

	FixedSpring* spring = new FixedSpring(Vec3{350., 100., 0.}, 200);
	AddForceGenerator(spring);
	particleForceRegistry.Add(p1, spring);

	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)
	ADD_GRAVITY(p1)

}

void GameContext::generateTestRegularSpring(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300., 200. });
	Particle* p2 = AddParticle({ 350., 100. });

	RegularSpring* spring = new RegularSpring(p2, 200);
	AddForceGenerator(spring);
	particleForceRegistry.Add(p1, spring);

	ADD_GRAVITY(p2)
}

void GameContext::generateTestBungee(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300., 200. });
	Particle* p2 = AddParticle({ 350., 100. });

	RegularSpring* spring = new RegularSpring(p2, 200, true);
	AddForceGenerator(spring);
	particleForceRegistry.Add(p1, spring);

	ADD_GRAVITY(p2)
}

void GameContext::generateTestBlobSpring(ParticleGravity* gravity)
{
	Particle* p1 = AddParticle({ 300., 200. });
	Particle* p2 = AddParticle({ 350., 100. });

	BlobSpring* spring = new BlobSpring(p2, 200, 220);
	AddForceGenerator(spring);
	particleForceRegistry.Add(p1, spring);

	ADD_GRAVITY(p2)
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


void GameContext::leftClickAt(int _x, int _y)
{
	Vec3 mousePos{ static_cast<float>(_x), static_cast<float>(_y), 0. };

	grabbedParticle = nullptr; //Reset grabbed particle
	float shortestDist = 40.f * 40.f; //Shortest squared distance for grabbing a particle

	for (Particle* p : lstParticle)
	{
		grabOffset = p->getPos() - mousePos;
		float dist = grabOffset.sqLength();
		if (dist < shortestDist)
		{
			shortestDist = dist;
			grabbedParticle = p;
		}
	}

}

void GameContext::rightClickAt(int _x, int _y)
{}


void GameContext::releaseLeftClick(int _x, int _y)
{
	grabbedParticle = nullptr;
}
void GameContext::releaseRightClick(int _x, int _y)
{}

void GameContext::updateGrabbed()
{
	if (grabbedParticle)
	{
		grabbedParticle->getPos() = Vec3(ofGetMouseX(), ofGetMouseY(), 0.);
	}
}