#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(50,50,50);
    ofSetBackgroundAuto(FALSE);
	ofSetVerticalSync(TRUE);

    gui.setup("VideoPlayer", "settings.xml", 0, 20);
    gui.setSize(250, 20);
    gui.add(helpText.setup("Press",  "\n l:   to load \n p:   to play/pause \n >/<: forward/rewind \n 0:   reset \n -:   decrease speed \n =:   increase speed" , 250, 200));


}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(50,50,50);
    if(movie.isPlaying()){
    	ofSetHexColor(0xFFFFFF);

        //display the movie
        movie.draw(X_OFFSET, 0);

        //display progress bar only if the mouse is in the bottom
        if(mouseY > movie.height - 40){
            ofEnableAlphaBlending();    // turn on alpha blending
            ofSetColor(255, 64, 64, 127);    // pinkish red, 50% transparent

            //display a rectangle for the progress bar
            ofRect(X_OFFSET, (movie.height - movie.height/20), (movie.getPosition() * movie.width), movie.height/20);
            ofDisableAlphaBlending(); 
        }
    }

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){


    switch(key){        

        case 'l':{
            //show a dialog box to select movie
            //ofFileDialogResult res = ofSystemLoadDialog("Please Select movie to load", false, "/home/dimitri/" );
            //string loadPath = res.filePath;
            string loadPath = "movies/fingers.mov";

            //load movie from the input path
            movie.loadMovie(loadPath);

            //start playing
            movie.play();
            }
            break;

        case 'p':
            if(movie.isPaused()){
                //if the movie is paused play it
                movie.setPaused(FALSE);
            }

            else if(movie.isPlaying()){
                //if the movie is playing pause it
                movie.setPaused(TRUE);
            }
            
            break;

        case OF_KEY_LEFT:
            //go 300 frames backwards
            movie.setFrame(movie.getCurrentFrame() - 300);
            break;
        
        case OF_KEY_RIGHT:
            //go 300 frames forwards
            movie.setFrame(movie.getCurrentFrame() + 300);
            break;
        
        case '-':  
            //decrease playback speed  
            movie.setSpeed(movie.getSpeed() - 0.05);      
            break;

        case '=':
            //increase playback speed
            movie.setSpeed(movie.getSpeed() + 0.05);
            break;
            
        case '0':
            //take movie to the start
            movie.firstFrame();
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

    if(y > (movie.height - movie.height/10))
    {
        //fast forward propotional to the mouse position
        movie.setFrame(((float)mouseX/(float)movie.width) * movie.getTotalNumFrames());

    }
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
