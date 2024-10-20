#include "ofApp.h"

#include <cstdio>
#include "primitives/Vec3.h"
#include "tests/TestClass.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//TestClass::s_testVec3();

	GameContext::getInstance().init();
}

//--------------------------------------------------------------
void ofApp::update(){
	float dt = ofGetLastFrameTime();
	if (dt <= 0.0001)
		dt = 1. / 60.;
	GameContext::getInstance().update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
	GameContext::getInstance().draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 57344)
		GameContext::getInstance().Testing();
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
	if (button == 0)
	{
		GameContext::getInstance().leftClickAt(x, y);
	}
	else if (button == 1)
	{
		GameContext::getInstance().rightClickAt(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button == 0)
	{
		GameContext::getInstance().releaseLeftClick(x, y);
	}
	else if (button == 1)
	{
		GameContext::getInstance().releaseRightClick(x, y);
	}
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
