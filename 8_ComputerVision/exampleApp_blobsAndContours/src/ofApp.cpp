#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(TRUE);
	ofBackground(30,30,30);

	franklin.loadFont("frabk.ttf", 12);
	
	gui.setup("Image Processing", "settings.xml", 5, 5);
	gui.add(minArea.setup("min Area", 10,  1, 200));
	gui.add(maxArea.setup("max Area", 100, 1, 5000));
	gui.add(nBlobs.setup("nBlobs", 10, 1, 50));
	gui.add(threshold.setup("Gray Threshold", 30, 1, 255));
	gui.add(detectHoles.setup("Detect Holes", true));
	gui.add(helpText.setup("Press",  "\n d:  display \n s:  subtract \n c: find contours", 200, 800));

	minArea.addListener(this, &ofApp::minAreaChanged);
	maxArea.addListener(this, &ofApp::maxAreaChanged);
	nBlobs.addListener(this, &ofApp::nBlobsChanged);
	threshold.addListener(this, &ofApp::thresholdChanged);
	detectHoles.addListener(this, &ofApp::detectHolesToggled);

	imageLoaded = false;
	
	image.loadImage("lowerKachura.jpg");
	width  = ofGetWidth() - 320;
	height = (float)(width)/(float)(image.width) * image.height;
	image.resize(width, height);
	imageLoaded = true;

	cout<< width << " " << height;

	cvColorImage.setFromPixels(image.getPixelsRef());


	red.allocate(width, height);
	green.allocate(width, height);
	blue.allocate(width, height);

	pressedKey = 'd';
	drawImage  = true;
}

//--------------------------------------------------------------
void ofApp::update(){
		

}

//--------------------------------------------------------------
void ofApp::draw(){	

	if(drawImage)
		switch(pressedKey){
			case 'd':
				ofBackground(30,30,30);
				ofSetHexColor(0xffffff);
				image.draw(IMG_X_OFFSET, 0);
				franklin.drawString("Basic Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
				break;


			case 's':
				ofBackground(30,30,30);
				cvColorImage.setFromPixels(image.getPixelsRef());
				cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
				blue += green;
				red -= blue;
				ofSetHexColor(0xffffff);
				red.draw(IMG_X_OFFSET, 0);
				franklin.drawString("Red channel with blue and green subtracted from  it", IMG_X_OFFSET, height +CAPTION_OFFSET);
				break;

			case 'c':
				detectContours();
				drawImage = false;

				break;
			default:
				cout << "key not supported"<< endl;
				break;

		}

	else {
		drawImage = false;
		ofSetHexColor(0xffffff);
		red.draw(IMG_X_OFFSET, 0);
		franklin.drawString("Detected Blobs", IMG_X_OFFSET, height +CAPTION_OFFSET);
	
		for (int i = 0; i < contourFinder.nBlobs; i++){
		    contourFinder.blobs[i].draw(IMG_X_OFFSET, 0);
		
			// draw over the centroid if the blob is a hole
			if(contourFinder.blobs[i].hole){
				ofSetHexColor(0x00dd33);
				ofCircle(contourFinder.blobs[i].boundingRect.getCenter().x,
						contourFinder.blobs[i].boundingRect.getCenter().y,
						5);
			}
		}
	}

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::minAreaChanged(int &minArea){
	detectContours();
}

//--------------------------------------------------------------
void ofApp::maxAreaChanged(int &maxArea){
	detectContours();
}

//--------------------------------------------------------------
void ofApp::thresholdChanged(int &threshold){
	detectContours();
}

//--------------------------------------------------------------
void ofApp::nBlobsChanged(int &nBlobs){
	detectContours();
}

//--------------------------------------------------------------
void ofApp::detectHolesToggled(bool &detectHoles){
	detectContours();
}

//--------------------------------------------------------------
void ofApp::detectContours(){
	ofBackground(30,30,30);
	
	cvColorImage.setFromPixels(image.getPixelsRef());
	cvColorImage.convertToGrayscalePlanarImages(red, green, blue);

	blue += green;
	red -= blue;
	red.threshold(threshold);

	contourFinder.findContours(red, minArea, maxArea, nBlobs, detectHoles, true);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	drawImage 	= true;
	pressedKey  = key;
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit(){
}
