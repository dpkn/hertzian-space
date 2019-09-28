#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    backgroundValue = 0;
    backgroundCounter = 0;
    backgroundFadeSpeed = 5;
    
    phase = 0;
    frequency = 0;
    
    // Connect to arduino
    arduino.connect("/dev/cu.usbserial-1410", 57600);
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    ofAddListener(arduino.EStringReceived, this, &ofApp::receiveString);
    
    clients.assign(5,Client());
    
    for(int i=0; i< clients.size(); i++){
        clients[i].setup();
    }
    
   // ofLog(OF_LOG_NOTICE, "hallo pls log");
    
    arialFont.load("arial.ttf", 10, true, false);
    
    bgSound.load("background_loop.mp3");
    bgSound.play();
    bgSound.setLoop(true);
    
    highBeep.load("beep_high.mp3");
    highBeep.setMultiPlay(true);
    
    buildUp.load("build_up.mp3");
    buildUp.setLoop(true);
    buildUp.play();

}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i=0; i<clients.size(); i++){
        clients[i].update();
    }
    
    
    arduino.update();
    
    if(backgroundCounter >= 900){
        backgroundValue = 255;
        backgroundCounter = 0;
        highBeep.play();
        followTargetClient = ofRandom(clients.size());
        followTargetBeacon = ofRandom(clients[followTargetClient].beacons.size());
        finishedFollowingPacket = false;
        
        float cameraDirection;
        if(ofRandom(1)>0.5){
            cameraDirection = -1;
            cameraDistance = ofRandom(100,250);
        }else{
            cameraDirection = 1;
            cameraDistance = ofRandom(200,400);
        }
        distanceSpeed = ofRandom(0.1,0.8) * cameraDirection;
        
        if(ofRandom(1) > 0.5){
            backgroundMode = 1;
            backgroundFadeSpeed = 3;
        }else{
            backgroundMode = 0;
            backgroundFadeSpeed = 5;
        }
    }
    
    if(backgroundValue <= 0){
        backgroundCounter++;
    }else{
        backgroundValue -= backgroundFadeSpeed;
    }
    
   cameraDistance += distanceSpeed;
    

}

//--------------------------------------------------------------
void ofApp::draw(){
        ofNoFill();
    
        if(backgroundMode == 1 && backgroundValue != 0){
            int blockSize = 50;
           int width = ofGetScreenWidth();
           int height = ofGetScreenHeight();
           int blockRows =   height/blockSize;
           int blockColumns = width/blockSize;
           ofSetColor(backgroundValue);
           for(int row = 0; row<blockRows; row++){
               ofDrawLine(0, row*blockSize, width, row*blockSize);
           }
           for(int column = 0; column<blockColumns; column++){
               ofDrawLine(column*blockSize,0,column*blockSize,height);
           }
        }else{
            ofBackground(backgroundValue);
        }
    


    camera.begin();
   //       ofLog(OF_LOG_NOTICE, "camera"+std::to_string(camera.getPosition()));
    
    for(int i=0; i<clients.size(); i++){
        clients[i].draw(&arialFont);
    }
    
    
    if(finishedFollowingPacket){
        camera.setTarget(finishedPosition);

    }else{
        camera.setTarget(clients[followTargetClient].beacons[followTargetBeacon].packets[0].position);
        if(clients[followTargetClient].beacons[followTargetBeacon].packets[0].progress >= 0.9){
            finishedFollowingPacket = true;
            finishedPosition = clients[followTargetClient].beacons[followTargetBeacon].packets[0].position;
        }
    }
  //   camera.setTarget(clients[followTargetClient].beacons[followTargetBeacon].packets[0].position);
    
    camera.setDistance(cameraDistance);
    
    if(backgroundCounter >=300){
    
    }
    
   camera.end();
     
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    
}
//--------------------------------------------------------------
void ofApp::receiveString(const string& message){
    ofLog(OF_LOG_NOTICE, message);
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &outBuffer) {
        // Set up sound
    //    ofSoundStreamSettings settings;
    //    settings.setOutListener(this);
    //    settings.sampleRate = 44100;
    //    settings.numOutputChannels = 2;
    //    settings.numInputChannels = 0;
    //    settings.bufferSize = 512;
    //    soundStream.setup(settings);
//    for(int i = 0; i < outBuffer.size(); i += 2) {
//        float sample = sin(phase)*frequency +  sin(phase*frequency); // generating a sine wave sample
//        //float sample = 0;
//        outBuffer[i] = sample; // writing to the left channel
//        outBuffer[i + 1] = sample; // writing to the right channel
//        phase += 0.05;
//    }
}
