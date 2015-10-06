#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(100);
    
    canvas.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
    canvas.begin();
    ofClear(255,255,255,255);
    canvas.end();

	gui.setup("Pen Settings", "settings.xml", 5, 5);
	gui.add(pen.setup("pen", true));
	gui.add(radius.setup( "radius", 5, 1, 30));
	gui.add(color.setup("color",ofColor(0x33,0xcc,0xcc),ofColor(0,0),ofColor(255,255)));
	gui.add(circleResolution.setup("circle res", 20, 3, 90));
	gui.add(screenSize.setup("screen size", ""));
	
	// we add this listener before setting up so the initial circle resolution is correct
	circleResolution.addListener(this, &ofApp::circleResolutionChanged);

	bHide = false;
	scribbling = false;
}


//--------------------------------------------------------------
void ofApp::update(){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw(){

	canvas.begin();
		if(scribbling)
			ofCircle(mouseX, mouseY, radius);
	canvas.end();

	ofSetHexColor(0xffffff);
	canvas.draw(0,0);
	if(!bHide)
	gui.draw();
	
}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
	ofSetCircleResolution(circleResolution);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 'h' ){
		bHide = !bHide;
	}
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == ' '){
		canvas.begin();
		ofClear(255,255,255,255);
        canvas.end();
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
    canvas.begin();
    
    if(pen)
		ofSetColor(color);
	else
		ofSetColor(255);
    
    canvas.end();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	scribbling = true;
	fprintf(stderr, "mousePressed = (%i,%i - button %i)\n", x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	scribbling = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
