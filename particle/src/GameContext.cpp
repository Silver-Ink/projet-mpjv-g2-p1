#include "GameContext.h"
#include "../ofMain.h"

void GameContext::update(float dt)
{
	int x = ofGetMouseX();
	int y = ofGetMouseY() - ofGetHeight();

	aimAngle = -atan2(y,x);
}

void GameContext::draw()
{
	//Draw the arrow
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
