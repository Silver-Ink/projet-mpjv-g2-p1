#pragma once

#include "../ParticleForceGenerator.h"

class RegularSpring : public ParticleForceGenerator
{
public:
	RegularSpring(float _restLength, Vec3 _springOriginPoint) : restLength(_restLength), springOriginPoint(_springOriginPoint) {}
	virtual void updateForce(Particle* _particle, float _dt) override;
	virtual void drawForce(Particle* _particle) override;

private:
	const float elasticConstant = 0.1;
	float restLength;
	Vec3 springOriginPoint;
};

