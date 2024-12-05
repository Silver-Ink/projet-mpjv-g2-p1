#pragma once
#include "RigidBody.h"

class EnclosingVolume 
{
public:
	EnclosingVolume(RigidBody _rb) : rb(_rb) 
	{
		radius = rb.getMaxRadius();
	}

	bool contact(EnclosingVolume _other);
	void resolveCollision(EnclosingVolume _other);

	void update(float _dt);
	void drawCollisionVolume();


private:
	RigidBody rb;
	float radius;
};

