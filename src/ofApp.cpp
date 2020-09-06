#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    post.init(ofGetWidth(), ofGetHeight());
//    post.createPass<BloomPass>()->setEnabled(true);
    ofSetFrameRate(60);
    
    ofHideCursor();
   
    // Add 6 clients to the world and set them up.
    clients.assign(6,Client());
    
    for(int i=0; i< clients.size(); i++){
        clients[i].setup();
    }
    backgroundController.setup();
    
//    // Load sounds
//    bgSound.load("bg_music2_loud.mp3");
//    bgSound.play();
//    bgSound.setLoop(true);
//    bgSound.setVolume(2);
//
    highBeep.load("beep_high.mp3");
    highBeep.setMultiPlay(true);
    highBeep.setVolume(0.4);
    
    droneLow.load("drone_low.mp3");
    droneLow.setMultiPlay(false);
    droneLow.setVolume(3);
    
    droneHigh.load("drone_high.mp3");
    droneHigh.setMultiPlay(false);
    droneHigh.setVolume(3);

    timerStartTime = ofGetElapsedTimeMillis();
    
    resetView();
    
    wifiReader.getNetworks();
    
    sender.setup("localhost",12345);
    
    m.setAddress("/flash");
    sender.sendMessage(m);

    cameraDistance = 380;
}

//--------------------------------------------------------------
void ofApp::update(){
    backgroundController.update();
    
    if(sceneManager.activeScene == 1){
            
        // Update all clients
        for(int i=0; i<clients.size(); i++){
            clients[i].update();
        }
        
        // Every x seconds, reset view and follow a new packet
        if(ofGetElapsedTimeMillis() - timerStartTime >= 3000){
            resetView();
        }
        
        // Zoom in or out of the camera
        cameraDistance += distanceSpeed;
    }else if(sceneManager.activeScene == 2){
        
        if(cameraDistance > 25){
            cameraDistance += distanceSpeed;
        }
    }
        
    // Log FPS
//    ofLog(OF_LOG_NOTICE, std::to_string(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    backgroundController.draw();
    
    if(sceneManager.activeScene == 1){
        drawOverviewScene();
    }else if(sceneManager.activeScene ==2 ){
        drawFocusScene();
    }
    
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
    
    sender.sendMessage(m);
}


void ofApp::drawOverviewScene(){
    ofNoFill();
        
    // Start of 3D context
    camera.begin();

    ofEnableDepthTest();
    // post.begin(camera);

    // Draw all Clients
    for(int i=0; i<clients.size(); i++){
      clients[i].draw();
    }

    // If the packet has reached its destination, set camera target to its destination
    // time check is an ugly for undefined target
    if(finishedFollowingPacket && ofGetElapsedTimeMillis() >= 4000){
      
      camera.setTarget(finishedTarget->position);
      
    }else{
      
      if(!cameraTarget){
          // Apparently draw fires before Setup????
          // so this is to make sure the cameraTarget points somewhere in the beginning
          cameraTarget = &clients[0].beacons[0].packets[0];
      }
      
      camera.setTarget(cameraTarget->position);
      
      // Switch Camera target over to the Packets' destination
      // so the packet can be deleted.
      if(cameraTarget->finished){
          finishedFollowingPacket = true;
          finishedTarget = cameraTarget->destination;
      }
    }

    camera.setDistance(cameraDistance);
    camera.end();
    
}
void ofApp::drawFocusScene(){
    distanceSpeed = -0.1;
   
    ofNoFill();
    camera.begin();

    // Main ball
    ofSetSphereResolution(10);
    ofSetColor(255,0,0);
    ofNoFill();
    ofPoint position;
    position.x=0;
    position.y=0;
    position.z=0;
    
    // Rotate main ball
    ofPushMatrix();
    int mainRotate = ofGetElapsedTimeMillis() % 360;
    ofRotateYDeg(mainRotate);
    ofDrawSphere(position, 20);
    ofPopMatrix();

    
    ofSetCircleResolution(360);
    int circleCount = 200;
    
    int progress = sceneManager.getSceneProgress();
    
    if(progress > 75000){
        sceneManager.startScene(1);
    }

    for(int i=0; i<circleCount; i++){
        
        int colorFade =  ofMap(sin(((ofGetElapsedTimef()*(progress/6000))+ PI*(circleCount-i)*0.01)*1.5), -1, 1, 255, 0);
         
        ofSetColor(255,255,255,colorFade);
        ofPushMatrix();

       if(progress % 15000 > 11000 ){
          
           int rotation = ofMap(sin((ofGetElapsedTimef())/4 + PI*(circleCount-i)*0.5), -1, 1, 0, 360);
           int rotation2 = ofMap(sin((ofGetElapsedTimef())/4 + PI*(circleCount-i)*0.5 + 0.5*PI), -1, 1, 0, 180);
           int rotation3 = ofMap(sin((ofGetElapsedTimef())/4 + PI*(circleCount-i)*0.5 + PI), -1, 1, 0, 360);

           ofRotateYDeg(rotation);
           ofRotateXDeg(rotation2);
           ofRotateZDeg(rotation3);
           
           if(ofGetElapsedTimeMillis() - playedDroneAt > 4000){
               playedDroneAt = ofGetElapsedTimeMillis();
               if(droneCount>0){
                 droneHigh.play();
               }else{
                 droneLow.play();
               }
               droneCount++;
           }

       }
       ofDrawCircle(position, 20+i*2);
       ofPopMatrix();
    }

    camera.setTarget(position);

    camera.setDistance(cameraDistance);
    camera.end();
}
