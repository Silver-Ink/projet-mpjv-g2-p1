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
	float dt = ofGetLastFrameTime(); // TODO ; change to delta time
	GameContext::getInstance().update(dt); 
	for (Particle* p : GameContext::getInstance().lstParticle)
	{
		p->computeForces(dt);
		p->update(dt);
	}
	/*for(int i = GameContext::getInstance().lstParticle.size(); i>0 ; i--)
	{
		Particle* p = GameContext::getInstance().lstParticle[i];
		if (p->getlifeTime() < 0)
			GameContext::getInstance().lstParticle.;
		p->computeForces(dt);
		p->update(dt);
	}*/
	/*for(auto iter = GameContext::getInstance().lstParticle.rbegin(); iter!= GameContext::getInstance().lstParticle.rend();iter++)
	{
		if((*iter)->getlifeTime()<0)
		{
			iter
			auto temp = iter++;
			(*iter)
		}
		(*iter)->computeForces(dt);
		(*iter)->update(dt);
	}*/

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
