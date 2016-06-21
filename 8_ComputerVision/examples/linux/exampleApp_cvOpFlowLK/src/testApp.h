//
// cvOpFlowLKExample by Takashi Maekawa.
// An usage of example cvOpFlowBM class.
//


#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxCvOpticalFlowLK.h"
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

		ofVideoGrabber 		vidGrabber;

		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvColorImage			colorImg;

		ofxCvOpticalFlowLK		opticalFlow;
   		ofxCvContourFinder 		contourFinder;

		int 				threshold;
		bool				bLearnBakground;

};

IplImage* convert_to_8u(IplImage* img);

#endif
