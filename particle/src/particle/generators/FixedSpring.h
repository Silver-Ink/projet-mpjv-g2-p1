#pragma once

#include "../ParticleForceGenerator.h"

class FixedSpring : public ParticleForceGenerator
{
public:
	FixedSpring(Vec3 _springOriginPoint, float _restLength) : springOriginPoint(_springOriginPoint), restLength(_restLength) {}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

private:
	const float elasticConstant = 0.1;
	float restLength;
	Vec3 springOriginPoint;
};

