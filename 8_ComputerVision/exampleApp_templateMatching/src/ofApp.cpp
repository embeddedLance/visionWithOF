#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(TRUE);
	ofSetBackgroundAuto(FALSE);
	ofBackground(30,30,30);

	franklin.loadFont("frabk.ttf", 12);
	
	gui.setup("Image Processing", "settings.xml", 5, 5);
	gui.add(helpText.setup("Press",  "\n d:  display \n 1:  CV_TM_SQDIFF \n 2:  CV_TM_SQDIFF_NORMED \n 3:  CV_TM_CCORR \n 4:  CV_TM_CCORR_NORMED \n 5:  CV_TM_CCOEFF \n 6:  CV_TM_CCOEFF_NORMED", 200, 800));

	imageLoaded = false;
	
	image.loadImage("test.jpg");
	width  = ofGetWidth() - 320;
	height = (float)(width)/(float)(image.width) * image.height;
	image.resize(width, height);
	imageLoaded = true;

	cout<< width << " " << height;

	cvColorImage.setFromPixels(image.getPixelsRef());

	showResult = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){	

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::matchTemplate(int method){
	ofBackground(30, 30, 30);

	//basic image
	cvColorImage.setFromPixels(image.getPixelsRef());

	//template image
	subjImage.allocate(roiRect.width, roiRect.height); //Allocate space for the template
	cvColorImage.setROI(roiRect); //Set region of interest (ROI)
	subjImage = cvColorImage; //Copy the specific area to the subject image
	cvColorImage.resetROI(); //Reset the ROI or everything downstream will go crazy
	
	//result image
	IplImage *result;
	result = cvCreateImage(cvSize(cvColorImage.getWidth() - subjImage.getWidth() +1, cvColorImage.getHeight() - subjImage.getHeight() +1), 32, 1);
	cvMatchTemplate(cvColorImage.getCvImage(), subjImage.getCvImage(), result, method);
	resultImage.allocate(result->width, result->height);

	//find location of the new roi
	double minVal, maxVal;
	CvPoint minLoc, maxLoc;
	cvMinMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, 0);
	ofSetHexColor(0xFFFFFF);
	if(showResult){
		resultImage = result;
		resultImage.draw(IMG_X_OFFSET, 0);
	}
	else
	image.draw(IMG_X_OFFSET, 0);
	
	ofSetHexColor(0x00FF00);  ofFill();  ofNoFill();
	int px, py;

	if((method == CV_TM_SQDIFF) || (method == CV_TM_SQDIFF_NORMED)){

		if(showResult){
			px = minLoc.x + roiRect.width;
			py = minLoc.y;// + roiRect.height;
		}
		else{
			px = minLoc.x;
			py = minLoc.y;
		}

	}
	else{
		if(showResult){
			px = maxLoc.x + roiRect.width;
			py = maxLoc.y ;//+ roiRect.height;
		}
		else{
			px = maxLoc.x;
			py = maxLoc.y;
		}
	}

	ofRect(px, py, roiRect.width, roiRect.height);		
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){

		case 'd':
			ofBackground(30,30,30);
			ofSetHexColor(0xFFFFFF);
			image.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Basic Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'o':	{
			image.grabScreen(IMG_X_OFFSET,0, width, height);
			//ofFileDialogResult selectedPath = ofSystemLoadDialog("Please Select Folder to save Image", true, "/home/dimitri/" );
			//string savePath = selectedPath.filePath + "/image.png";
			image.saveImage("image.png");
			}
			franklin.drawString("Save Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case '1':
			ofBackground(30,30,30);
			matchTemplate(CV_TM_SQDIFF);
			ofSetHexColor(0xFFFFFF);
			franklin.drawString("CV_TM_SQDIFF", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case '2':
			ofBackground(30,30,30);
			matchTemplate(CV_TM_SQDIFF_NORMED);
			ofSetHexColor(0xFFFFFF);
			franklin.drawString("CV_TM_SQDIFF_NORMED", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case '3':
			ofBackground(30,30,30);
			matchTemplate(CV_TM_CCORR);
			ofSetHexColor(0xFFFFFF);
			franklin.drawString("CV_TM_CCORR", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case '4':
			ofBackground(30,30,30);
			matchTemplate(CV_TM_CCORR_NORMED);
			ofSetHexColor(0xFFFFFF);
			franklin.drawString("CV_TM_CCORR_NORMED", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case '5':
			ofBackground(30,30,30);
			matchTemplate(CV_TM_CCOEFF);
			ofSetHexColor(0xFFFFFF);
			franklin.drawString("CV_TM_CCOEFF", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case '6':
			ofBackground(30,30,30);
			matchTemplate(CV_TM_CCOEFF_NORMED);
			ofSetHexColor(0xFFFFFF);
			franklin.drawString("CV_TM_CCOEFF_NORMED", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'r':
			showResult = !showResult;

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
	if(button == 0){
		ofSetHexColor(0xFFFFFF);
		image.draw(IMG_X_OFFSET, 0);
		startX = x;
		startY = y;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if(button == 0){
		endX = x;
		endY = y;
	}
	ofSetHexColor(0xFF0000);
	ofFill();
	ofNoFill();
	roiRect = ofRectangle(startX, startY, endX-startX, endY-startY);
	ofRect(roiRect);
	ofSetHexColor(0xFFFFFF);

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
