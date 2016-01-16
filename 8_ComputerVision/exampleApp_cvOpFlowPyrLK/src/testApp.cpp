//
// Adapted from: http://www.roxlu.com/2013/022/opencv
//

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	#ifdef _USE_LIVE_VIDEO
				vidGrabber.setVerbose(true);
				vidGrabber.initGrabber(CAM_WIDTH,CAM_HEIGHT);
				vidGrabber.setDeviceID(1);
	#else
				vidPlayer.load("fingers.mov");
				vidPlayer.play();
	#endif

	colorImg.allocate(CAM_WIDTH,CAM_HEIGHT);
	grayImage.allocate(CAM_WIDTH,CAM_HEIGHT);
	grayBg.allocate(CAM_WIDTH,CAM_HEIGHT);
	bLearnBakground = true;
	useFAST = false;
	threshold = 80;
}

//--------------------------------------------------------------
void testApp::update(){
		bool bNewFrame = false;

  	ofBackground(0,0,0);
#ifdef _USE_LIVE_VIDEO
		vidGrabber.update();
		bNewFrame = vidGrabber.isFrameNew();
#else
		vidPlayer.update();
		bNewFrame = vidPlayer.isFrameNew();
#endif
    //do we have a new frame?
    if (bNewFrame){

#ifdef _USE_LIVE_VIDEO
    colorImg.setFromPixels(vidGrabber.getPixels().getData(), 320,240);
#else
    colorImg.setFromPixels(vidPlayer.getPixels().getData(), 320,240);
#endif
        grayImage = colorImg; // convert our color image to a grayscale image
        if (bLearnBakground == true) {
            grayBg = grayImage; // update the background image
            bLearnBakground = false;
        }

   		cv::Mat mat_curr(CAM_HEIGHT, CAM_WIDTH, CV_8UC1, grayImage.getPixels().getData(), cv::Mat::AUTO_STEP);
  		cv::Mat mat_prev(CAM_HEIGHT, CAM_WIDTH, CV_8UC1, grayBg.getPixels().getData(), cv::Mat::AUTO_STEP);

 		if(useFAST){
 			vector<cv::KeyPoint> keyPoints;
			cv::FAST(mat_prev, keyPoints,30,true);
			cv::KeyPoint::convert(keyPoints, prev_good_points);
		}
		else  {
			cv::goodFeaturesToTrack(mat_prev,            // input, the image from which we want to know good features to track
									prev_good_points,    // output, the points will be stored in this output vector
									100,                 // max points, maximum number of good features to track
									0.05,                // quality level, "minimal accepted quality of corners", the lower the more points we will get
									10,                  // minDistance, minimum distance between points
									cv::Mat(),           // mask
									4,                   // block size
									false,               // useHarrisDetector, makes tracking a bit better when set to true
									0.04                 // free parameter for harris detector
									);
		}


		cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,prev_good_points.size(),0.03);


		cv::calcOpticalFlowPyrLK(mat_prev,            // prev image
								mat_curr,             // curr image
								prev_good_points,     // find these points in the new image
								curr_good_points,     // result of found points
								status,               // output status vector, found points are set to 1
								error,                // each point gets an error value (see flag)
								cv::Size(21, 21),     // size of the window at each pyramid level
								0,                    // maxLevel - 0 = no pyramids, > 0 use this level of pyramids
								termcrit,             // termination criteria
								0,                    // flags OPTFLOW_USE_INITIAL_FLOW or OPTFLOW_LK_GET_MIN_EIGENVALS
								0.1                   // minEigThreshold
								);
	    grayBg = grayImage;
	}
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);

	colorImg.draw(0,0);

	for( uint32_t i=0; i < status.size(); i++ ){
		if(!status[i])
      		continue;
    	ofSetHexColor(0xff2f88);
		ofDrawLine(	ceil( prev_good_points[i].x ), ceil( prev_good_points[i].y ),
				ceil( curr_good_points[i].x ), ceil( curr_good_points[i].y ) );
				ofDrawCircle(ceil( curr_good_points[i].x ), ceil( curr_good_points[i].y ),2);

	}

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	switch (key){
		case 'f':
			useFAST = true;
			break;
		case 'g':
			useFAST = false;
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
