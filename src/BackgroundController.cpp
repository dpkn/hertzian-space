//
//  backgroundController.cpp
//  hertzianSpace
//

#include "BackgroundController.hpp"
void BackgroundController::setup(){
   reset();
}

// is called everytime the background needs to appear for a fading flash
void BackgroundController::reset(){
    // Pick a mode (Grid or Full color) and speed.
    if(ofRandom(1) > 0.5){
        mode = 1;
        fadeSpeed = 3;
    }else{
        mode = 0;
        fadeSpeed = 5;
    }
    brightness = 255;
}

void BackgroundController::update(){
    // Fade out the background
    if(brightness>0){
       brightness -= fadeSpeed;
    }
}


void BackgroundController::draw(){
    // BackgroundMode 1 is a grid overlay
    if(mode == 1 && brightness != 0){

        // Calculate size of the grid and placement of the lines
        int blockSize = 50;
        int width = ofGetScreenWidth();
        int height = ofGetScreenHeight();
        int blockRows =   height/blockSize;
        int blockColumns = width/blockSize;
        ofSetColor(brightness);

        // Draw grid
        for(int row = 0; row<blockRows; row++){
            ofDrawLine(0, row*blockSize, width, row*blockSize);
        }
        for(int column = 0; column<blockColumns; column++){
            ofDrawLine(column*blockSize,0,column*blockSize,height);
        }

    }else{
        // Mode 0 is a solid bg
        ofBackground(brightness);
    }
    
}
