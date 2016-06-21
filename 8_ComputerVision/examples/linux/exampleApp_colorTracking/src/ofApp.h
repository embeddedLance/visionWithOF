#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"


#define CAPTION_OFFSET	20
#define IMG_X_OFFSET	260
#define IMG_Y_OFFSET	0

//#define _USE_LIVE_VIDEO	1


class ofApp : public ofBaseApp{
	
	public:
		int width;
		int height;
		void setup();
		void update();
		void draw();

		void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void loadImagePressed();
		void blurChanged(int & blur);
		void gaussianBlurChanged(int & gaussianBlur);
		
        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif

		ofImage image;
		ofxCvColorImage 		cvColorImage;
		ofxCvColorImage			hsvImage;
		ofxCvGrayscaleImage 	hueImage;
		ofxCvGrayscaleImage 	satImage;
		ofxCvGrayscaleImage 	valImage;
		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	threshedImage;

		ofxPanel gui;
		ofxLabel helpText;

		ofxCvContourFinder 	contourFinder;

		ofTrueTypeFont franklin;

		bool selectingColor;

		int targetHue, targetSat, targetVal;
};

