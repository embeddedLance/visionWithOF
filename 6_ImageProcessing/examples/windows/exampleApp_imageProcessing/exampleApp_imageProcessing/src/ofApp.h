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

		void loadImagePressed();
		void blurChanged(int & blur);
		void gaussianBlurChanged(int & gaussianBlur);
		
		ofImage image;
		ofxCvColorImage cvColorImage;
		ofxCvGrayscaleImage red;
		ofxCvGrayscaleImage green;
		ofxCvGrayscaleImage blue;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage cannyImage;
		ofxCvGrayscaleImage sobelImage;

		ofxPanel gui;
		ofxIntSlider blur;
		ofxIntSlider gaussianBlur;
		ofxLabel helpText;

        ofFbo canvas;
		int pressedKey;
    
		ofTrueTypeFont franklin;

		bool imageLoaded;
		bool displayBlurImage;
};

