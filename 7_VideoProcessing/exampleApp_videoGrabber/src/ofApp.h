#pragma once

#include "ofMain.h"
#include "ofxGui.h"


#define CAPTION_OFFSET	20
#define X_OFFSET	260
#define Y_OFFSET	20

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofxPanel gui;
		ofxLabel helpText;

		ofTrueTypeFont franklin;

		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;

		ofImage 			capture;

		bool cameraSelected;
};
