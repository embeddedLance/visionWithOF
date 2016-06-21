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

		void detectContours();
		void minAreaChanged(int &minArea);
		void maxAreaChanged(int &maxArea);
		void thresholdChanged(int &threshold);
		void nBlobsChanged(int &nBlobs);
		void detectHolesToggled(bool &detectHoles);

		ofImage image;
		ofxCvColorImage cvColorImage;
		ofxCvGrayscaleImage red;
		ofxCvGrayscaleImage green;
		ofxCvGrayscaleImage blue;

		ofxPanel gui;
		ofxIntSlider minArea;
		ofxIntSlider maxArea;
		ofxIntSlider nBlobs;
		ofxIntSlider threshold;
		ofxToggle detectHoles;
		ofxLabel helpText;

		ofxCvContourFinder 	contourFinder;

		ofTrueTypeFont franklin;

		int pressedKey;
		bool drawImage;

		bool imageLoaded;
};

