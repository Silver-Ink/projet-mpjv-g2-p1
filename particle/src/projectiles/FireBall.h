#pragma once
#include "../Particle.h"

class FireBall : public Particle
{
public:
	virtual void update(float dt) override;
	virtual void draw() override;
	
};

