#pragma once
#include "../Particle.h"

class CanonBall : public Particle
{
public:
	CanonBall(float _angle) : Particle() {
		velocity = {80*cos(_angle), -100 *sin(_angle), 0};
		setMass(100);
		lifeTime = 8;				
	};

	virtual void update(float _dt) override;
	virtual void draw() override;

};

