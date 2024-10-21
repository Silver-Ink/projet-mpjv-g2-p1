#pragma once

#include "../primitives/Vec3.h"

class IDrawsLine
{
public:
	virtual Vec3 getSecondEnd() = 0;

	bool doesLineTouch(Particle* _particle, int _x, int _y, float _maxDist)
	{
		Vec3 firstEnd = _particle->getPos();
		Vec3 secondEnd = getSecondEnd();

		// Calculating distance from line to point
		float a = secondEnd.y - firstEnd.y;
		float b = firstEnd.x - secondEnd.x;
		float c = secondEnd.x * firstEnd.y - firstEnd.x * secondEnd.y;

		float distance = fabs(a * _x + b * _y + c) / sqrt(a * a + b * b);

		// If distance is small enough, we consider the line touches the point
		return distance < _maxDist;
	}
};