#pragma once
#include "../Particle.h"

class CanonBall : public Particle
{
public:
	CanonBall(float _angle);

	virtual void update(float _dt) override;
	virtual void draw() override;

};

