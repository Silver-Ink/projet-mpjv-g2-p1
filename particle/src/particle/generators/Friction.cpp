#include "Friction.h"

void Friction::updateForce(Particle* _particle, float _dt)
{
	Vec3 n = -normal.dot(gravity) * normal;
	Vec3 gk = gravity + n;
	Vec3 F = Vec3() - gk;
	F.normalize();
	F *= n.length();
	if (gk.sqLength() < mu_stat * F.sqLength())
		_particle->addForce(Vec3() - gk);
	else
	{
		_particle->addForce(F*mu_dyn);
	}
	
	_particle->addForce(n);
}
void Friction::drawForce(Particle* _particle)
{
	Vec3 n = -normal.dot(gravity) * normal ;
	Vec3 gk = gravity + n;
	Vec3 F = Vec3() - gk;
	F.normalize();
	F *= n.length();
	if (gk.sqLength() < mu_stat * F.sqLength())
		F = Vec3() - gk;
	else
	{
		F *= mu_dyn;
	}
	Vec3 pos = _particle->getPos();
	Vec3 pos2 = pos +n * 10;
	Vec3 pos3 = pos + gk*10;

	//printf("\n F: %f, %f / n: %f, %f", F.x, F.y, n.x, n.y);
	//ofSetColor(ofColor::red);
	//ofDrawLine(pos.x, pos.y, pos2.x, pos2.y);
	//ofSetColor(ofColor::blue);
	//ofDrawLine(pos.x, pos.y, pos3.x, pos3.y);
}
;
