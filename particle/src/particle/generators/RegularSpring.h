#pragma once

#include "../ParticleForceGenerator.h"

class RegularSpring : public ParticleForceGenerator
{
public:
	RegularSpring(Particle* _hinge, float _restLength, bool _isBungee = false) : hinge(_hinge), restLength(_restLength), isBungee(_isBungee) {}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

private:
	const float elasticConstant = 0.1;
	float restLength;
	Particle* hinge;
	bool isBungee;
};

