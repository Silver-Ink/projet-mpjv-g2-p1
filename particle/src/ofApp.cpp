#include "ofApp.h"

#include <cstdio>
#include "primitives/Vec3.h"
#include "tests/TestClass.h"

//--------------------------------------------------------------
void ofApp::setup(){
	TestClass::s_testVec3();
	TestClass::s_testQuaternion();
	TestClass::s_testMatrix3();
	TestClass::s_testMatrix4();
	TestClass::s_test_Planes();
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
	//if (key == 57344)
	//	GameContext::getInstance().Testing();

	//std::cout << key << endl;

	float axisY = GameContext::getInstance().getCameraY();
	if (key == 101 || key == 32)
	{
		axisY = 1.; // UP
	}
	else if (key == 97 || key == 3680)
	{
		axisY = -1.; // DOWN
	}

	float axisZ = GameContext::getInstance().getCameraZ();
	if (key == 122 || key == 57357)
	{
		axisZ = 1.; // FORWARD
	}
	else if (key == 115 || key == 57359)
	{
		axisZ = -1.; // BACKWARD
	}

	float axisX = GameContext::getInstance().getCameraX();
	if (key == 100 || key == 57358)
	{
		axisX = 1.; // RIGHT
	}
	else if (key == 113 || key == 57356)
	{
		axisX = -1.; // LEFT
	}

	GameContext::getInstance().setInputCamera(axisX, axisY, axisZ);

	static bool addGravity = true;

	switch (key) {
	// Q
	case 113:
		break;
	// W	  //
	case 119: 
		break;
	// E	  //
	case 101: 
		break;
	// R	  //
	case 114: {GameContext::getInstance().ResetCamera(); break; }
	// T	  //
	case 116:
		break;
	// Y	  //
	case 121:
		break;
	// U	  //
	case 117: 
		break;
	// I	  //
	case 105:
		break;
	// O	  //
	case 111: 
		break;
	// F1
	case 57344: 
		GameContext::getInstance().spawnBox(20.f, 20.f, 500.f, 0.000001, false);
		break;
	// F2		//
	case 57345: 
		GameContext::getInstance().spawnBox(20.f, 20.f, 50.f, 0.00001, addGravity);
		break;
	// F3		//
	case 57346: 
		GameContext::getInstance().spawnBox(20.f, 20.f, 50.f, 0.00005, addGravity);
		break;
	// F4		//
	case 57347: 
		GameContext::getInstance().spawnBox(20.f, 20.f, 50.f, 0.0002, addGravity);
		break;
	// F5		//
	case 57348:
		addGravity = !addGravity;
		break;
	// F6		//
	case 57349:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	float axisY = GameContext::getInstance().getCameraY();
	if (key == 101 || key == 32 || key == 97 || key == 3680)
	{
		axisY = 0.;
	}

	float axisZ = GameContext::getInstance().getCameraZ();
	if (key == 122 || key == 57357 || key == 115 || key == 57359)
	{
		axisZ = 0.; // FORWARD
	}

	float axisX = GameContext::getInstance().getCameraX();
	if (key == 100 || key == 57358 || key == 113 || key == 57356)
	{
		axisX = 0.; // RIGHT
	}
	GameContext::getInstance().setInputCamera(axisX, axisY, axisZ);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	if (button == 1) // Scroll wheel Click tiny hit
		GameContext::getInstance().strength = 10.f;

	if (button == 2) //Right click heavy hit
		GameContext::getInstance().strength = 200.f;
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
