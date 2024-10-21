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
	case 97: GameContext::getInstance().init(GameContext::EsceneType::BlobScene); break;
	case 122: GameContext::getInstance().init(GameContext::EsceneType::InterpenetrationScene); break;
	case 101: GameContext::getInstance().init(GameContext::EsceneType::RestContactScene); break;
	case 114: GameContext::getInstance().init(GameContext::EsceneType::CableScene); break;
	case 116: GameContext::getInstance().init(GameContext::EsceneType::RodScene); break;
	case 121: GameContext::getInstance().init(GameContext::EsceneType::FixedSpringScene); break;
	case 117: GameContext::getInstance().init(GameContext::EsceneType::RegularSpringScene); break;
	case 105: GameContext::getInstance().init(GameContext::EsceneType::BungeeScene); break;
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
