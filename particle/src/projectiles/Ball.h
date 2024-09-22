#pragma once
#include "../Particle.h"

class Ball : public Particle
{
	public:
		Ball(float);
		void update(float) override;
		void draw() override;
};

