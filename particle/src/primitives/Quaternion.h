#pragma once

#include <cmath>
#include <cstdio>
#include "ofMain.h"

struct Quaternion
{
public:
	Quaternion() = default;

	Quaternion		operator*		(float _s);
	Quaternion&		operator*=		(float _s);
	
	Quaternion		operator+		(Quaternion& _q);
	Quaternion&		operator+=		(Quaternion& _q);

	Quaternion		operator-		(Quaternion& _q);
	Quaternion&		operator-=		(Quaternion& _q);
	
	Quaternion		operator*		(Quaternion& _q);
	Quaternion&		operator*=		(Quaternion& _q);

	Quaternion		operator-		();
	
	Quaternion		getConjugate	();
	Quaternion&		conjugate		();
	
	Quaternion		getInverse		();
	Quaternion&		inverse			();

	float			dotProduct		(Quaternion& _q);
	
	Quaternion		getExpo			(float _t);
	Quaternion&		expo			(float _t);


	float			length			();
	Quaternion		getNormalized	();
	Quaternion&		normalize		();

	void			print			() {printf("%.2f %+.2f i %+.2f j %+.2f k", a, b, c, d); }

public:
	static Quaternion	IDENTITY;

public:
	float a; //Real part
	float b; //i factor
	float c; //j factor
	float d; //k factor
};

Quaternion		operator*		(float _s, Quaternion& _q);

