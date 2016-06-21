//
// Adapted from: http://www.roxlu.com/2013/022/opencv
//



#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"

#define CAM_WIDTH              320
#define CAM_HEIGHT             240
#define AX                               20
#define AY                               20

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);

#ifdef _USE_LIVE_VIDEO
		ofVideoGrabber 		vidGrabber;
#else
		ofVideoPlayer 		vidPlayer;
#endif

		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvColorImage			colorImg;

		std::vector<cv::Point2f> prev_good_points;
		std::vector<cv::Point2f> curr_good_points;

		std::vector<unsigned char> status;
		std::vector<float> error;

 		ofxCvContourFinder 		contourFinder;

		int 				threshold;
		bool				bLearnBakground;
		bool 				useFAST;
};

IplImage* convert_to_8u(IplImage* img);

#endif
