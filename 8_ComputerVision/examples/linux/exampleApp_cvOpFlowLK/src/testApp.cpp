//
// cvOpFlowLKExample by Takashi Maekawa.
// An usage of example cvOpFlowBM class.
//

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(CAM_WIDTH,CAM_HEIGHT);		// windows direct show users be careful
											// some devices (dvcams, for example) don't
											// allow you to capture at this resolution.
											// you will need to check, and if necessary, change
											// some of these values from CAM_WIDTHxCAM_HEIGHT to whatever your camera supports
											// most webcams, firewire cams and analog capture devices will support this resolution.

	opticalFlow.allocate(CAM_WIDTH, CAM_HEIGHT);

	colorImg.allocate(CAM_WIDTH,CAM_HEIGHT);
	grayImage.allocate(CAM_WIDTH,CAM_HEIGHT);
	grayBg.allocate(CAM_WIDTH,CAM_HEIGHT);
	bLearnBakground = true;
	threshold = 80;
}

//--------------------------------------------------------------
void testApp::update(){

  	ofBackground(0,0,0);
  	vidGrabber.update();
    //do we have a new frame?
    if (vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixelsRef());
        grayImage = colorImg; // convert our color image to a grayscale image
        if (bLearnBakground == true) {
            grayBg = grayImage; // update the background image
            bLearnBakground = false;
        }
	    
		opticalFlow.calc(grayBg, grayImage, 11);

	    grayBg = grayImage;
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);

	colorImg.draw(AX,AY);

    opticalFlow.draw(AX, AY, CAM_WIDTH, CAM_HEIGHT);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case 's':
			vidGrabber.videoSettings();
			break;
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
}


IplImage* convert_to_8u(IplImage* img)
{
    IplImage* img8u = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,img->nChannels);
    CvScalar s;

    for(int i=0; i<img->height; i++)
    {
        for(int j=0; j<img->width; j++)
        {
            //cvSet2D(img8u,i,j,(unsigned char)cvGetReal2D(img,i,j));
          s.val[0]=cvGetReal2D(img,i,j); // get the (i,j) pixel value
          //printf("intensity=%f\n",s.val[0]);
          //s.val[0]=111;
          cvSet2D(img8u,i,j,s); // set the (i,j) pixel value
        }
    }
    return img8u;
}
