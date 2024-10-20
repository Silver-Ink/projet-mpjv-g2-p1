#pragma once

#include "../ParticleForceGenerator.h"

class BlobSpring : public ParticleForceGenerator // Mix between a cable and a regular spring
{
public:
	BlobSpring(Particle* _hinge, float _restLength, float _maxLength) : hinge(_hinge), restLength(_restLength), maxLength(_maxLength) {}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

private:
	const float elasticConstant = 0.1;
	float restLength;
	float maxLength;
	Particle* hinge;
};

