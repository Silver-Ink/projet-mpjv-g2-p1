#include "GameContext.h"
#include "../ofMain.h"
#include "projectiles/Ball.h"
#include "projectiles/CanonBall.h"
#include "projectiles/FireBall.h"
#include "projectiles/Laser.h"

void GameContext::update(float _dt)
{
	int x = ofGetMouseX();
	int y = ofGetMouseY() - ofGetHeight();

	aimAngle = -atan2(y, x);

	if (updateThrower(_dt))
	{
		Particle* f;
		switch (currentProjectile)
		{
		case EProjectile_Ball:			f = new Ball{};					break;
		case EProjectile_CanonBall:		f = new CanonBall{aimAngle};	break;
		case EProjectile_FireBall:		f = new FireBall{aimAngle};				break;
		case EProjectile_Laser:			f = new	Laser{};				break;
		}
		lstParticle.emplace_back(f);
	}
}

void GameContext::draw()
{
	//Draw the arrow
	ofSetColor(255, 255, 255);

	float r = 100.;
	float a = -aimAngle;

	float x1 = 0;
	float y1 = ofGetHeight();
	float x2 = x1 + cosf(a) * r;
	float y2 = y1 + sinf(a) * r;
	ofDrawLine(x1, y1, x2, y2);

	//Draw the head of the arrow
	float arrowSharpness = 2.7; 
	float arrowHead = 20.;
	ofDrawTriangle(
		x2, y2,
		x2 + cosf(a + arrowSharpness) * arrowHead, y2 + sinf(a + arrowSharpness) * arrowHead,
		x2 + cosf(a - arrowSharpness) * arrowHead, y2 + sinf(a - arrowSharpness) * arrowHead);
}

bool GameContext::updateThrower(float _dt)
{
	if (ofGetKeyPressed(OF_KEY_F1))
	{
		currentProjectile = EProjectile_Ball;
		throwerCooldown = 0.3;
		throwerCooldownTimer = 0;
	}
	else if (ofGetKeyPressed(OF_KEY_F2))
	{
		currentProjectile = EProjectile_CanonBall;
		throwerCooldown = .8;
		throwerCooldownTimer = 0;
	}
	else if (ofGetKeyPressed(OF_KEY_F3))
	{
		currentProjectile = EProjectile_FireBall;
		throwerCooldown = .6;
		throwerCooldownTimer = 0;
	}
	else if (ofGetKeyPressed(OF_KEY_F4))
	{
		currentProjectile = EProjectile_Laser;
		throwerCooldown = 1./20.;
		throwerCooldownTimer = 0;
	}

	if (ofGetMousePressed(OF_MOUSE_BUTTON_1))
	{
		throwerCooldownTimer -= _dt;
		if (throwerCooldownTimer <= 0)
		{
			throwerCooldownTimer = throwerCooldown;
			return true;
		}
	}
	else
	{
		throwerCooldownTimer = 0;
	}
	return false;
}