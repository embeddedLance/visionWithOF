#include "ofApp.h"
// Adapted from https://processing.org/examples/bounce.html
//--------------------------------------------------------------
void ofApp::setup(){
	rad = 60;        // Width of the shape
	
	xspeed = 6;  // Speed of the shape
	yspeed = 4;  // Speed of the shape

	xdirection = 1;  // Left or Right
	ydirection = 1;  // Top to Bottom

	//Set the frame rate for the animation
	ofSetFrameRate(30);

	//get the current window width and height
	width  = ofGetScreenWidth();
	height = ofGetScreenHeight();
	// Set the starting position of the shape
	xpos = width/2;
	ypos = height/2;

	ofBackground(40,40,40);
	ofSetFullscreen(TRUE);
}

//--------------------------------------------------------------
void ofApp::update(){

	// Update the position of the shape
	xpos = xpos + ( xspeed * xdirection );
	ypos = ypos + ( yspeed * ydirection );

	// Test to see if the shape exceeds the boundaries of the screen
	// If it does, reverse its direction by multiplying by -1
	if (xpos > width-rad || xpos < rad) {
	xdirection *= -1;
	}
	if (ypos > height-rad || ypos < rad) {
	ydirection *= -1;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

  	ofSetColor(51, 204, 204);
  	// Draw the shape
  	ofCircle(xpos, ypos, rad);
  	ofFill();
  	//ofNoFill();
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
