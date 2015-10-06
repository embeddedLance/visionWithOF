#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(TRUE);
	ofSetBackgroundAuto(FALSE);
	ofBackground(30,30,30);

	franklin.loadFont("frabk.ttf", 12);

	gui.setup("Face Detection", "settings.xml", width + 10, 10);
	gui.setSize(250, 20);


#ifdef _USE_LIVE_VIDEO

	width 	= 640;
	height 	= 480;

	//we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();

	char buffer[200];
	int n = 0;

    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
		n = sprintf(&buffer[n], "\n %d:  %s", devices[i].id, devices[i].deviceName.c_str());
       
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}

	std::string deviceNames = buffer;
	gui.add(helpText.setup("Press", deviceNames + "\n m:  track mouth  \n e:  track eyes \n n:  track nose \n f:  track face \n", 250, 200));

#else
	gui.add(helpText.setup("Press", "\n m:  track mouth  \n e:  track eyes \n n:  track nose \n f:  track face \n", 250, 200));

    vidPlayer.loadMovie("testVideo.mp4");
    vidPlayer.setLoopState(OF_LOOP_NORMAL);
    vidPlayer.play();

    width	= vidPlayer.width;
    height 	= vidPlayer.height;
#endif



	
	haarSetup = false;
}


//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(30,30,30);

	
    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
	 	if(vidGrabber.isInitialized()){
       		vidGrabber.update();
	   		bNewFrame = vidGrabber.isFrameNew();
	   	}
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){
		if(haarSetup)
			#ifdef _USE_LIVE_VIDEO
            	haarFinder.findHaarObjects((ofPixels&)(vidGrabber.getPixelsRef()));	
			#else
            	haarFinder.findHaarObjects((ofPixels&)(vidPlayer.getPixelsRef()));	
			#endif
	}	

}

//--------------------------------------------------------------
void ofApp::draw(){

	#ifdef _USE_LIVE_VIDEO
	if(vidGrabber.isInitialized()){
		ofSetHexColor(0xffffff);
		vidGrabber.draw(0,0);

		for(int i = 0; i < (int)haarFinder.blobs.size(); i++) {
			ofRect(haarFinder.blobs[i].boundingRect);
	     	ofNoFill();
	  	}
	}
	#else
		ofSetHexColor(0xffffff);
		vidPlayer.draw(0,0);
		for(int i = 0; i < (int)haarFinder.blobs.size(); i++) {
			ofRect(haarFinder.blobs[i].boundingRect);
	     	ofNoFill();
	  	}
	#endif
  	
  	gui.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 

	switch(key){

#ifdef _USE_LIVE_VIDEO
		case '0':
			if(vidGrabber.isInitialized())
				vidGrabber.close();

			vidGrabber.setDeviceID(0);
			vidGrabber.setDesiredFrameRate(30);
			vidGrabber.initGrabber(width,height);
			
			cameraSelected = TRUE;
			break;

		case '1':
			if(vidGrabber.isInitialized())
				vidGrabber.close();

			vidGrabber.setDeviceID(1);
			vidGrabber.setDesiredFrameRate(30);
			vidGrabber.initGrabber(width,height);
			
			cameraSelected = TRUE;
			break;

		case 'c':
			capture.setFromPixels(vidGrabber.getPixelsRef());
			capture.saveImage("capture.png");
			break;
#endif
		case 'f':
			ofBackground(30,30,30);
			haarFinder.setup("haarcascade_frontalface_default.xml"); 
			haarSetup = true;

			//draw caption
			franklin.drawString("Tracking Face", IMG_X_OFFSET, height + CAPTION_OFFSET +CAPTION_OFFSET);
			break;

		case 'n':
			ofBackground(30,30,30);
			haarFinder.setup("haarcascade_nose_25x15.xml"); 
			haarSetup = true;

			//draw caption
			franklin.drawString("Tracking Nose", IMG_X_OFFSET, height + CAPTION_OFFSET +CAPTION_OFFSET);
			break;

		case 'm':
			ofBackground(30,30,30);
			haarFinder.setup("haarcascade_mouth.xml");
			haarSetup = true;

			//draw caption
			franklin.drawString("Tracking Mouth", IMG_X_OFFSET, height + CAPTION_OFFSET +CAPTION_OFFSET);
			break;
	
		case 'e':
			ofBackground(30,30,30);
			haarFinder.setup("haarcascade_eyes_22x5.xml"); 
			haarSetup = true;

			//draw caption
			franklin.drawString("Tracking Eyes", IMG_X_OFFSET, height + CAPTION_OFFSET +CAPTION_OFFSET);
			break;

		case 'h':
			ofBackground(30,30,30);
			haarFinder.setup("haarcascade_head_shoulders.xml"); 
			haarSetup = true;

			//draw caption
			franklin.drawString("Tracking Head and Shoulders", IMG_X_OFFSET, height + CAPTION_OFFSET +CAPTION_OFFSET);
			break;

		case 'b':
			ofBackground(30,30,30);
			haarFinder.setup("haarcascade_fullbody.xml"); 
			haarSetup = true;

			//draw caption
			franklin.drawString("Tracking Face", IMG_X_OFFSET, height + CAPTION_OFFSET +CAPTION_OFFSET);
			break;

				

		default:
			cout << "key not supported"<< endl;
			break;

	}
	
	
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
