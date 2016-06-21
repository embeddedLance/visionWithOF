#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(TRUE);
	ofSetBackgroundAuto(FALSE);
	ofBackground(0, 0, 0);

#ifdef _USE_LIVE_VIDEO
	width 	= 640;
	height 	= 480;

    vidGrabber.setVerbose(true);
    vidGrabber.setDeviceID(1);
    vidGrabber.initGrabber(width, height);
#else
    vidPlayer.load("movingColors.mp4");
    vidPlayer.setLoopState(OF_LOOP_NORMAL);
    vidPlayer.play();

    width	= vidPlayer.getWidth();
    height 	= vidPlayer.getHeight();
#endif

	franklin.load("frabk.ttf", 12);
	
	gui.setup("Color Tracking", "settings.xml", 0, 0);
	gui.add(helpText.setup("Use Mouse",  "\n to select color\n to track", 200, 360));

	cvColorImage.allocate(width, height);

}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0, 0, 0);

	
    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            cvColorImage.setFromPixels(vidGrabber.getPixels());
	    #else
            cvColorImage.setFromPixels(vidPlayer.getPixels());
        #endif

        hsvImage = cvColorImage;
        hsvImage.convertRgbToHsv();
		threshedImage.setFromColorImage(hsvImage);

		cvInRangeS(hsvImage.getCvImage(), cvScalar(targetHue-5, 70,70/*targetSat - 70, targetVal-30*/), cvScalar(targetHue + 5, 255, 255), threshedImage.getCvImage());
		//threshedImage.draw(2*IMG_X_OFFSET, 0);


		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(threshedImage, 10, (width * height)/3, 10, true);	// find holes
	}
}

//--------------------------------------------------------------
void ofApp::draw(){	

	cvColorImage.draw(IMG_X_OFFSET, IMG_Y_OFFSET);

	//threshedImage.draw(IMG_X_OFFSET + width, IMG_Y_OFFSET);
	ofSetHexColor(0x333333);
	ofDrawRectangle(IMG_X_OFFSET+width,IMG_Y_OFFSET,width,height);
	ofSetHexColor(0xffffff);
	contourFinder.draw(IMG_X_OFFSET + width, IMG_Y_OFFSET);

	ofSetHexColor(0xffffff);
	//ofNoFill();
	ofDrawCircle(mouseX, mouseY, 5);
	ofSetHexColor(0xffffff);
	gui.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){

		default:
			cout << "key not supported"<< endl;
			break;

	}
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

	image.setFromPixels(cvColorImage.getPixels());
	ofColor color 	= image.getColor(x-IMG_X_OFFSET,y+IMG_Y_OFFSET);

	//cout << "Hue " << color.getHue() << " Saturation " << color.getSaturation() << " Lightness " << color.getLightness() << endl;
	targetHue 		= (int)(color.getHue() * 0.7);
	targetSat 		= (int)(color.getSaturation());
	targetVal 		= (int)(color.getLightness());
	cout << "Hue " << targetHue << " Saturation " << targetSat << " Lightness " << targetVal << endl;
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
