#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
   
    // Add 6 clients to the world and set them up.
    clients.assign(6,Client());
    
    for(int i=0; i< clients.size(); i++){
        clients[i].setup();
    }
    backgroundController.setup();
    
    // Load sounds
    bgSound.load("bg_music2_loud.mp3");
    bgSound.play();
    bgSound.setLoop(true);
    bgSound.setVolume(2);
    
    highBeep.load("beep_high.mp3");
    highBeep.setMultiPlay(true);
    highBeep.setVolume(0.4);
    timerStartTime = ofGetElapsedTimeMillis();
    
    resetView();

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Update all clients
    for(int i=0; i<clients.size(); i++){
        clients[i].update();
    }
    
     backgroundController.update();
    
    // Every x seconds, reset view and follow a new packet
    if(ofGetElapsedTimeMillis() - timerStartTime >= 5000){
        resetView();
    }
    
    // Zoom in or out of the camera
    cameraDistance += distanceSpeed;
    
    // Log FPS
    ofLog(OF_LOG_NOTICE, std::to_string(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    
    backgroundController.draw();
    
    // Start of 3D context
    camera.begin();
    
    // Draw all Clients
    for(int i=0; i<clients.size(); i++){
        clients[i].draw();
    }
    
    // If the packet has reached its destination, s its destination
    if(finishedFollowingPacket){
        
        camera.setTarget(finishedTarget->position);
        
    }else{
        
        if(!cameraTarget){
            // Apparently draw fires before Setup????
            // so this is to make sure the cameraTarget points somewhere in the beginning
            cameraTarget = &clients[0].beacons[0].packets[0];
        }
        
        camera.setTarget(cameraTarget->position);
        
        // Switch Camera target over to the Packets' destinatio
        // so the packet can be deleted.
        if(cameraTarget->finished){
            finishedFollowingPacket = true;
            finishedTarget = cameraTarget->destination;
        }
    }

   camera.setDistance(cameraDistance);

   camera.end();
   // End of 3D context

    
}

// Function that is called when a new packet should be followed.
void ofApp::resetView(){
    // Play BEEP and show white flash
    highBeep.play();
    backgroundController.reset();
    
    // Reset timer
    timerStartTime = ofGetElapsedTimeMillis();

    // Pick new random packet to follow
    int randomClientId = ofRandom(clients.size());
    int randomBeaconId = ofRandom(clients[randomClientId].beacons.size());
    cameraTarget = &clients[randomClientId].beacons[randomBeaconId].packets[0];
    finishedFollowingPacket = false;

    // Random speed, direction and starting distance for camera
    float cameraDirection;
    if(ofRandom(1)>0.5){
      cameraDirection = -1;
      cameraDistance = ofRandom(250,400);
    }else{
      cameraDirection = 1;
      cameraDistance = ofRandom(50,150);
    }
    distanceSpeed = ofRandom(0.2,0.9) * cameraDirection;
}
