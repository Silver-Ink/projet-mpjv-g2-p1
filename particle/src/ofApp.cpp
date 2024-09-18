#include "ofApp.h"

#include <cstdio>
#include "primitives/vec3.h"
#include "tests/testClass.h"
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
	float dt = 1. / 60.; // TODO ; change to delta time
	GameContext::getInstance().update(dt); 
	for (Particle* p : GameContext::getInstance().lstParticle)
	{
		p->computeForces(dt);
		p->update(dt);
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
