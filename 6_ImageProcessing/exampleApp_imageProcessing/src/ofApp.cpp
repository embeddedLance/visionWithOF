#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(30,30,30);

	franklin.load("frabk.ttf", 12);
	
	gui.setup("Image Processing", "settings.xml", 5, 5);
	gui.add(blur.setup("Blur", IMG_X_OFFSET, 1, 25));
	gui.add(gaussianBlur.setup("Gaussian Blur", IMG_X_OFFSET, 1, 25));
	gui.add(helpText.setup("Press",  "\n d:  display \n o:  save \n w:  Grayscale Image \n m:  mirror \n n:  negative \n c:  histogram \n     equalization \n e:  edge Detection \n r:  red channel \n g:  green channel \n b:  blue channel \n h:  hue \n s:  saturation \n v:  brightness", 200, 800));

	blur.addListener(this, &ofApp::blurChanged);
	gaussianBlur.addListener(this, &ofApp::gaussianBlurChanged);

	imageLoaded = false;
	
	image.load("lowerKachura.jpg");
	width  = ofGetWidth() - 320;
	height = (float)(width)/(float)(image.getWidth()) * image.getHeight();
	image.resize(width, height);
	imageLoaded = true;

	cout<< width << " " << height;
    canvas.allocate(width, height+CAPTION_OFFSET, GL_RGBA, 4);
    canvas.begin();
    ofClear(30,30,30,255);
    canvas.end();

	cvColorImage.setFromPixels(image.getPixels());

	red.allocate(width, height);
	green.allocate(width, height);
	blue.allocate(width, height);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){	
	
	if(displayBlurImage)
		cvColorImage.draw(IMG_X_OFFSET, 0);
	else
    	switch(pressedKey){
		case 'l':	/*{
			ofFileDialogResult res = ofSystemLoadDialog("Please Select Image to display", false, "/home/dimitri/" );
			string loadPath = res.filePath;
			cout << "Load Path :" << loadPath <<endl;
			image.loadImage(loadPath);
			image.resize(image.width / 4, image.height / 4);
			imageLoaded = true;
			image.draw(IMG_X_OFFSET, 0);

			width = image.width/4;
			height = image.height/4;

			cout << "init cvColorImage : ";
			cvColorImage.setFromPixels(image.getPixels());
			cout << "width " << cvColorImage.getWidth() << ", height " << cvColorImage.getHeight();
			}*/
			break;

		case 'd':
            ofClear(30,30,30,255);
			image.draw(IMG_X_OFFSET, 0);
			cvColorImage.setFromPixels(image.getPixels());
			franklin.drawString("Basic Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'o':	{
			image.grabScreen(IMG_X_OFFSET,0,width,height);
			ofFileDialogResult selectedPath = ofSystemLoadDialog("Please Select Folder to save Image", true, "/home/dimitri/" );
			string savePath = selectedPath.filePath + "/image.png";
			image.save(savePath);
			}
			franklin.drawString("Save Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'w':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			grayImage.setFromColorImage(cvColorImage);
			grayImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Grayscale Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'n':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.invert();
			cvColorImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Negative Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'm':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.mirror(FALSE, TRUE);
			cvColorImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Mirror Image", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'c':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			grayImage.setFromColorImage(cvColorImage);
			grayImage.contrastStretch();
			grayImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Histogram Equalization - Contrast Stretching", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'e':{
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cannyImage.setFromColorImage(cvColorImage);
			grayImage.setFromColorImage(cvColorImage);

			int minVal = 60;   
			int maxVal = 150;   
			cvCanny(grayImage.getCvImage(), cannyImage.getCvImage(), minVal,  maxVal, 3);  
			cannyImage.flagImageChanged(); 
			cannyImage.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Edge Detection using Canny Edge Detection", IMG_X_OFFSET, height +CAPTION_OFFSET);
			}
			break;

		/*case 'x':
			canvas.begin();
            ofClear(30,30,30,255);            
			cvColorImage.setFromPixels(image.getPixels());
			sobelImage.setFromColorImage(cvColorImage);
			grayImage.setFromColorImage(cvColorImage);

			cvSobel(grayImage.getCvImage(), sobelImage.getCvImage(), 1, 0, 3); 
			sobelImage.draw(IMG_X_OFFSET, 0);
            canvas.end();
			break;

		case 'y':
			canvas.begin();
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			sobelImage.setFromColorImage(cvColorImage);
   			grayImage.setFromColorImage(cvColorImage);

			cvSobel(grayImage.getCvImage(), sobelImage.getCvImage(), 0, 1, 3);  
			sobelImage.flagImageChanged(); 
			sobelImage.draw(IMG_X_OFFSET, 0);
            canvas.end();
			break;*/

		case 'r':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			red.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Red Channel", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'g':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			green.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Green Channel", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'b':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			blue.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Blue Channel", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'h':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertRgbToHsv();
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			red.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Hue", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 's':
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertRgbToHsv();
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			green.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Saturation", IMG_X_OFFSET, height +CAPTION_OFFSET);
			break;

		case 'v':
			
            ofClear(30,30,30,255);
			cvColorImage.setFromPixels(image.getPixels());
			cvColorImage.convertRgbToHsv();
			cvColorImage.convertToGrayscalePlanarImages(red, green, blue);
			blue.draw(IMG_X_OFFSET, 0);
			franklin.drawString("Brightness", IMG_X_OFFSET, height +CAPTION_OFFSET);
            
			break;

		default:
			cout << "key not supported"<< endl;
			break;

	}
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::blurChanged(int & blur){
    
	if(imageLoaded){
		cvColorImage.setFromPixels(image.getPixels());
		cvColorImage.blur(blur);
	}
	displayBlurImage = true;
}

//--------------------------------------------------------------
void ofApp::gaussianBlurChanged(int & gaussianBlur){

	if(imageLoaded){
		cvColorImage.setFromPixels(image.getPixels());
		cvColorImage.blurGaussian(gaussianBlur);
	}
	displayBlurImage = true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	displayBlurImage = false;
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
	blur.removeListener(this, &ofApp::blurChanged);
	gaussianBlur.removeListener(this, &ofApp::gaussianBlurChanged);
}
