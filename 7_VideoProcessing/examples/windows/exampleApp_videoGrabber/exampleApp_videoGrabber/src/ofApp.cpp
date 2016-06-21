#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(50,50,50);
	ofSetBackgroundAuto(FALSE);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
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

	franklin.loadFont("frabk.ttf", 12);

	gui.setup("VideoGrabber", "settings.xml", 5, 5);
	gui.setSize(250, 20);
	gui.add(helpText.setup("Press",  deviceNames + "\n c:  capture \n" , 250, 200));

	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	ofSetVerticalSync(true);
    
}


//--------------------------------------------------------------
void ofApp::update(){

	if(cameraSelected){
		ofBackground(50,50,50);
		
		vidGrabber.update();
		
		if (vidGrabber.isFrameNew()){
			int totalPixels = camWidth*camHeight*3;
			unsigned char * pixels = vidGrabber.getPixels();
			for (int i = 0; i < totalPixels; i++){
				videoInverted[i] = 255 - pixels[i];
			}
			videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
		
	if(cameraSelected){
		ofSetHexColor(0xffffff);
		vidGrabber.draw(X_OFFSET,Y_OFFSET);
		videoTexture.draw(X_OFFSET + camWidth, Y_OFFSET,camWidth,camHeight);
	}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	if(key == '0'){

		if(vidGrabber.isInitialized())
			vidGrabber.close();

		vidGrabber.setDeviceID(0);
		vidGrabber.setDesiredFrameRate(60);
		vidGrabber.initGrabber(camWidth,camHeight);
		
		cameraSelected = TRUE;
	}

	if(key == '1'){

		if(vidGrabber.isInitialized())
			vidGrabber.close();

		vidGrabber.setDeviceID(1);
		vidGrabber.setDesiredFrameRate(60);
		vidGrabber.initGrabber(camWidth,camHeight);
		
		cameraSelected = TRUE;
	}

	if(key == 'c'){

		if (vidGrabber.isFrameNew()){
			capture.setFromPixels(vidGrabber.getPixelsRef());
			capture.saveImage("capture.png");
		}
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
