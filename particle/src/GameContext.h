#pragma once
#include "primitives/Vec3.h"
#include "particle/Particle.h"
#include "particle/generators/ParticleGravity.h"
#include "particle/ParticleForceRegistry.h"
#include "particle/generators/SpringBungee.h"
#include "rigidBody/RigidBody.h"
#include "primitives/Octree.h"


class RigidBody;
class EnclosingVolume;
//class Octree;

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
	void		init();
	void		update(float _dt);
	void		draw();
	void		emptyScene();

public:

	ParticleForceRegistry particleForceRegistry;
	std::vector<Particle*> lstParticle;
	std::vector<ParticleForceGenerator*> lstForceGenerator;

	std::vector<RigidBody*> lstRigidBody;
	std::vector<EnclosingVolume*> lstEnclosingVolume;

	void setInputCamera(float _axisX, float _axisY, float _axisZ);
	void updateCamera(float _dt);

	float getCameraX() { return axisX; }
	float getCameraY() { return axisY; }
	float getCameraZ() { return axisZ; }

	void ResetCamera();

	void spawnBox(float _length, float _height = -1, float _width = -1, float _density = 1., bool _addGravity = true);

	//Vec3 testArrow;

	float strength;

	std::vector<SatCollisionResult> collisionData;

	bool drawNormals = true;
	bool drawEnclosingBodies = true;
	bool drawOctree = true;
private:
	ParticleForceGenerator* AddForceGenerator(ParticleForceGenerator* _forceGenerator);

	Particle* AddParticle(Particle* _particle);
	Particle* AddParticle(const Particle& _particle);

	RigidBody* GameContext::AddRigidBody(RigidBody* _rigidBody);
	RigidBody* GameContext::AddRigidBody(const RigidBody& _rigidBody);

	struct raycastResult {
		RigidBody* collisionner{ nullptr };
		Vec3 collisionPosAbsolute{};
		float rayLength{ -1 };
	};

	raycastResult raycast(Vec3 _startPoint, Vec3 _direction, float _maxLength, std::vector<RigidBody*>& _lstRigidBody);

	ofEasyCam camera;

	float axisX{};
	float axisY{};
	float axisZ{};

	Plane* ground;

	raycastResult raycastData;
	Octree octree;

};



