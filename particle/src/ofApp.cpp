#include "ofApp.h"

#include <cstdio>
#include "primitives/Vec3.h"
#include "tests/TestClass.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//TestClass::s_testVec3();

	GameContext::getInstance().init(GameContext::EsceneType::BlobScene);
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
	//if (key == 57344)
	//	GameContext::getInstance().Testing();

	std::cout << key << endl;

	switch (key) {
	// Q
	case 113: GameContext::getInstance().init(GameContext::EsceneType::BlobScene); break;
	// W
	case 119: GameContext::getInstance().init(GameContext::EsceneType::InterpenetrationScene); break;
	// E
	case 101: GameContext::getInstance().init(GameContext::EsceneType::RestContactScene); break;
	// R
	case 114: GameContext::getInstance().init(GameContext::EsceneType::CableScene); break;
	// T
	case 116: GameContext::getInstance().init(GameContext::EsceneType::RodScene); break;
	// Y
	case 121: GameContext::getInstance().init(GameContext::EsceneType::FixedSpringScene); break;
	// U
	case 117: GameContext::getInstance().init(GameContext::EsceneType::RegularSpringScene); break;
	// I
	case 105: GameContext::getInstance().init(GameContext::EsceneType::BungeeScene); break;
	// O
	case 111: GameContext::getInstance().init(GameContext::EsceneType::BlobSpringScene); break;
	}
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
