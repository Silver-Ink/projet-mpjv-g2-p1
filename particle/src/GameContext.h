#pragma once
#include "primitives/Vec3.h"
#include "particle/Particle.h"
#include "particle/generators/ParticleGravity.h"
#include "particle/ParticleForceRegistry.h"
#include "particle/generators/SpringBungee.h"

class GameContext
{
	// SINGLETON
public:
	static GameContext& getInstance()
	{
		static GameContext instance;
		return instance;
	}
private:
	GameContext() {}

public:
	GameContext(const GameContext&) = delete;
	void operator=(const GameContext&) = delete;

	// INTERFACE
public:
	enum EsceneType;
	void		init(EsceneType sceneType);
	void		Testing();
	void		update(float _dt);
	void		draw();
	void		emptyScene();

public:

	enum EsceneType {
		BlobScene,
		InterpenetrationScene,
		RestContactScene,
		CableScene,
		RodScene,
		FixedSpringScene,
		RegularSpringScene,
		BungeeScene,
		BlobSpringScene
	};

	ParticleForceRegistry particleForceRegistry;
	std::vector<Particle*> lstParticle;
	std::vector<ParticleForceGenerator*> lstForceGenerator;

	void generateBlob(int nbParticle, float firmness, ParticleGravity* gravity = nullptr);
	void generateTestInterpenetration(ParticleGravity* gravity);
	void generateTestRestContact(ParticleGravity* gravity);
	void generateTestCable(ParticleGravity* gravity);
	void generateTestRod(ParticleGravity* gravity);
	void generateTestFixedSpring(ParticleGravity* gravity);
	void generateTestRegularSpring(ParticleGravity* gravity);
	void generateTestBungee(ParticleGravity* gravity);
	void generateTestBlobSpring(ParticleGravity* gravity);
	void generateTestFloor();

	void leftClickAt(int _x, int _y);
	void middleClickAt(int _x, int _y);
	void rightClickAt(int _x, int _y);

	void releaseLeftClick(int _x, int _y);
	void releaseRightClick(int _x, int _y);

	void updateGrabbed();

	void changeLinkCreationMode(int _newMode);
	void drawLinePreview();

private:
	ParticleForceGenerator* AddForceGenerator(ParticleForceGenerator* _forceGenerator);
	Particle* AddParticle(Particle* _particle);

	Particle* AddParticle(const Particle& _particle);

	Vec3 grabOffset;
	Particle* grabbedParticle{ nullptr };
	Particle* currentLinkedParticle{ nullptr };

	int linkCreationMode{ 0 };
};



