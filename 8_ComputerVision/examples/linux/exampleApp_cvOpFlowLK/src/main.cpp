#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(360, 280, OF_WINDOW);			// <-------- setup the GL context
	
	// this is my "app" :
	testApp APP;
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	ofRunApp(&APP);
	
}
