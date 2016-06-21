#include "ofApp.h"

void ofApp::segment(float x, float y, float a) {
	ofPushMatrix();
	ofTranslate(x, y);
	ofRotate(a);
    ofSetHexColor(0x75a928);
	ofLine(0, 0, segLength, 0);
	ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::setup(){
	x=100;
	y=100;
	angle1 = 0.0;
	segLength = 75;
    
    ofSetLineWidth(20);
	ofSetColor(220, 0, 220, 200);
    ofSetCircleResolution(100);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 2, 0);

	float dx = mouseX - x;
	float dy = mouseY - y;
	angle1 = atan2(dy, dx);  
	x = mouseX - (cos(angle1) * segLength);
	y = mouseY - (sin(angle1) * segLength);

	segment(x, y, angle1*57.295);
    ofSetColor(188, 17, 66, 200);
	ofCircle(x, y, 30);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
