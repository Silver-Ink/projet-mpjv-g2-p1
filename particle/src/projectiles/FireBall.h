#pragma once
#include "../Particle.h"

class FireBall : public Particle
{
public:
	FireBall(float angle);

	virtual void update(float _dt) override;
	virtual void draw() override;
	
};

