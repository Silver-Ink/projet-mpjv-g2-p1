﻿#pragma once
#include "../primitives/vec3.h"
#include "../rigidBody/RigidBody.h"

class Plane
{

private:
	Vec3 origin;
	Vec3 normal;
	float impulsionStrength;

public:
	Plane(Vec3 _origin, Vec3 _normal);
	Plane(Vec3 _p1, Vec3 _p2, Vec3 _p3);

	Vec3 getOrigin();
	Vec3 getNormal();

	Vec3 projectPoint(Vec3 _point);
	float getDistance(Vec3 _point);

	void draw();

	void collisionResolve(RigidBody* _rb);



};
