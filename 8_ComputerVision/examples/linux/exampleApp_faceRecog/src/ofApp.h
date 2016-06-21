#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCvHaarFinder.h"

#define CAPTION_OFFSET	20
#define IMG_X_OFFSET	260

//#define _USE_LIVE_VIDEO	1

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
		
        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif

		ofImage * probeImage;
		ofxCvHaarFinder		haarFinder;
		bool haarSetup;

		int 				width;
		int 				height;

		ofImage 			capture;

		bool cameraSelected;
};
