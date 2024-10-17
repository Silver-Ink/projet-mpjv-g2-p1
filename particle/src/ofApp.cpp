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
