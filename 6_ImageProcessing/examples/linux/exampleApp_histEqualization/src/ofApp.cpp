//with some help from Joon http://visiblevisible.org/teaching/setpixel/students/jun/02/02.html
//and https://en.wikipedia.org/wiki/Histogram_equalization

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetVerticalSync(TRUE);
	ofSetBackgroundAuto(FALSE);
	ofBackground(30,30,30);

	franklin.load("frabk.ttf", 12);

	gui.setup("Hist Equalization", "settings.xml", 5, 5);
	gui.add(helpText.setup("Press",  "\n d:  display \n w:  Grayscale Image \n e:  manual histogram \n     equalization \n c:  contrast stretching \n", 200, 400));

	image.load("lowerKachura.jpg");
	//image.setImageType(OF_IMAGE_GRAYSCALE);

	width  = ofGetWidth() - 320;
	height = (float)(width)/(float)(image.getWidth()) * image.getHeight();
	image.resize(width, height);

	cvColorImage.setFromPixels(image.getPixels());
	grayImage.setFromColorImage(cvColorImage);

	pixels = grayImage.getPixels().getData();

	for(int i=0; i<255; i++){
		histogram[i]   = 0;
		eqHistogram[i]   = 0;
		cdf[i] = 0;
	}

	for(int i=0; i<width * height; i++){
			histogram[pixels[i]]++;
	}

	int cdfMin = width * height;
	eqPixels   = new unsigned char [width * height];
	
	cdf[0] = histogram[0];
	for(int i=1; i<255; i++){
		cdf[i] = histogram[i] + cdf[i-1];

		//find the minimum value for the cumulative distribution function
		if(cdfMin > cdf[i]){
			cdfMin = cdf[i];
		}
	}

	for(int i=0; i<width*height; i++){
		int eqVal = (float)(cdf[pixels[i]] - cdfMin)/(width * height - cdfMin)*255;
		eqPixels[i] = eqVal;
		eqHistogram[eqPixels[i]]++;
	}

	eqGrayImage.setFromPixels(eqPixels, width, height);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	switch(pressedKey){
		case 'd':
			ofBackground(30,30,30);
			image.draw(IMG_X_OFFSET, 0);
			
			//draw caption
			franklin.drawString("Basic Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'w':
			ofBackground(30,30,30);
			cvColorImage.setFromPixels(image.getPixels());
			grayImage.setFromColorImage(cvColorImage);
			grayImage.draw(IMG_X_OFFSET, 0);
			
			//draw histogram
			for(int i=0;i<255;i++){
					ofDrawLine(i,height-histogram[i]/20,i,height);
			}
			
			//draw caption
			franklin.drawString("Grayscale Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'c':
			ofBackground(30,30,30);
			cvColorImage.setFromPixels(image.getPixels());
			grayImage.setFromColorImage(cvColorImage);
			grayImage.contrastStretch();
			grayImage.draw(IMG_X_OFFSET, 0);
			
			//draw caption
			franklin.drawString("Histogram Equalization - Contrast Stretching", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;
	
		case 'e':
			ofBackground(30,30,30);
			eqGrayImage.draw(IMG_X_OFFSET, 0);

			//draw histogram
			for(int i=0;i<255;i++){
				ofDrawLine(i,height-eqHistogram[i]/20,i,height);
			}
			
			//draw caption
			franklin.drawString("Manual Histogram Equalization", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;
				

		default:
			cout << "key not supported"<< endl;
			break;

	}

	gui.draw();	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	pressedKey = key;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
