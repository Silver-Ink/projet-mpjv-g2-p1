#include "ofApp.h"

#include <cstdio>
#include "primitives/Vec3.h"
#include "projectiles/Ball.h"
#include "tests/TestClass.h"
#include "projectiles/FireBall.h"

//--------------------------------------------------------------
void ofApp::setup(){
	TestClass::s_testVec3();
}

void spawParticle(int n)
{

}

//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofGetLastFrameTime();
	GameContext::getInstance().update(dt); 
	for (auto iter = GameContext::getInstance().lstParticle.begin(); iter != GameContext::getInstance().lstParticle.end();)
	{
		if ((*iter)->getlifeTime() < 0)
		{
			delete* iter;
			iter = GameContext::getInstance().lstParticle.erase(iter);
		}
		else
		{
			(*iter)->computeForces(dt);
			(*iter)->update(dt);
			iter++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (Particle* p : GameContext::getInstance().lstParticle)
	{
		p->draw();
	}
	GameContext::getInstance().draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
