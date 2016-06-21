#pragma once
// Adapted from https://processing.org/examples/bounce.html
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		int rad;        // Width of the shape
		float xpos, ypos;    // Starting position of shape    

		float xspeed;  // Speed of the shape
		float yspeed;  // Speed of the shape

		int xdirection;  // Left or Right
		int ydirection;  // Top to Bottom
		
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
		
};
