#include "GameContext.h"
#include "../ofMain.h"
#include "particle/generators/Friction.h"
#include "particle/generators/RegularSpring.h"
#include "particle/generators/SpringRod.h"
#include "particle/Collisionner.h"
#include "particle/generators/SpringCable.h"



void GameContext::init()
{
	ParticleGravity* gravity = new ParticleGravity();
	AddForceGenerator(gravity);

	//Particle* p1 = new Particle(300., 0. );
	//Particle* p2 = new Particle(300., 250. );

	//AddParticle(p1);
	//AddParticle(p2);
	//Particle* p3 = AddParticle({100., 100.});


	//SpringBungee* springBungee1 = new SpringBungee( p1, 200., 1. );
	//AddForceGenerator(springBungee1);
	//particleForceRegistry.Add(p2, springBungee1);

	//generateTestInterpenetration(gravity);
	//generateTestRestContact(gravity);
	generateTestCable(gravity);

	//generateBlob(7, 1.);
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

	//particleForceRegistry.Clear();

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
		float angle = rng(0, 6.283);
		Particle* p = AddParticle({ x + cos(angle) * radius, y + sin(angle) * radius});
		lstBlobParticle.emplace_back(p);

		if (gravity)
		{
			ADD_GRAVITY(p)
		}
	}

	for (int i = 1; i < nbParticle; i++)
	{
		Particle* p1 = lstBlobParticle[i-1];
		Particle* p2;

		for (int j = 0; j < i; j++)
		{
			p2 = lstBlobParticle[j];

			//SpringBungee* bungee = new SpringBungee(p1, 200., 1);
			//AddForceGenerator(bungee);
			//particleForceRegistry.Add(p2, bungee);
			RegularSpring* spring = new RegularSpring(200., p1->getPos());
			AddForceGenerator(spring);
			particleForceRegistry.Add(p2, spring);
		}


	}

	Particle* p1 = lstBlobParticle[nbParticle - 1];
	Particle* p2 = lstBlobParticle[0];

	SpringBungee* bungee = new SpringBungee(p1, 200.);
	AddForceGenerator(bungee);
	particleForceRegistry.Add(p2, bungee);
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