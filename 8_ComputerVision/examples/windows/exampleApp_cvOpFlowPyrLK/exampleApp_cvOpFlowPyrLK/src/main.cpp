#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(320, 240, OF_WINDOW);	
	
	// this is my "app" :
	testApp APP;
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	ofRunApp(&APP);
	
}
