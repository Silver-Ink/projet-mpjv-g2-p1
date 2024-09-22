#pragma once
#include "../Particle.h"

class Laser : public Particle
{
public:
	Laser(float _angle);

	virtual void update(float _dt) override;
	virtual void draw() override;
};

