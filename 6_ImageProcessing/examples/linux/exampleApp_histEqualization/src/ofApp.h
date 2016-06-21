#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#define CAPTION_OFFSET	20
#define IMG_X_OFFSET	260

class ofApp : public ofBaseApp{

	public:
		int width;
		int height;

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

		ofImage image;
		ofxCvColorImage cvColorImage;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage eqGrayImage;

		unsigned char * pixels;
		unsigned char * eqPixels;

		int histogram[255];
		int eqHistogram[255];
		int cdf[255];
		
		int pressedKey;
		
};
