#include "FireBall.h"
#include "../ofMain.h"

void FireBall::update(float dt)
{
	Particle::update(dt);
}

void FireBall::draw()
{
	ofSetColor({ 255, 131, 48 });
	ofDrawCircle({ position.x, position.y}, 50.);
	ofSetColor(ofColor::white);
	
}
