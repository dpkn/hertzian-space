#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableSmoothing();
    
    ofSetFrameRate(60);
    
    ofHideCursor();
   
    // Add 6 clients to the world and set them up.
    clients.assign(6,Client());
    
    for(int i=0; i< clients.size(); i++){
        clients[i].setup();
    }
    backgroundController.setup();

    timerStartTime = ofGetElapsedTimeMillis();
    
    
    //    // Load sounds
        bgSound.load("bg_music2_loud.mp3");
        bgSound.setLoop(true);
        bgSound.setVolume(2);
    //
        highBeep.load("beep_high.mp3");
        highBeep.setMultiPlay(true);
        highBeep.setVolume(0);
       // highBeep.setVolume(0.4);
        
        droneLow.load("drone_low.mp3");
        droneLow.setMultiPlay(false);
        droneLow.setVolume(3);
        
        droneHigh.load("drone_high.mp3");
        droneHigh.setMultiPlay(false);
        droneHigh.setVolume(3);
        
        tickLow.load("tick_low.mp3");
        tickLow.setLoop(true);
        tickLow.setVolume(3);
        tickLow.setMultiPlay(false);
        
        font.load("cour.ttf", 12);
    
    wifiReader.getNetworks();
    
    sender.setup("localhost",12345);
    
    m.setAddress("/flash");
    sender.sendMessage(m);
    
    screenHeight = ofGetScreenHeight();
    screenWidth = ofGetScreenWidth();

    changeScene(2);
}

//--------------------------------------------------------------
void ofApp::update(){
    backgroundController.update();
    int progress = sceneManager.getSceneProgress();
    
    if(sceneManager.activeScene == 1){
        
           if(cameraDistance > 25){
               cameraDistance += distanceSpeed;
           }
        if(progress > 75000){
            changeScene(2);
        }
    
    }else if(sceneManager.activeScene == 2){
        
         // Update all clients
         for(int i=0; i<clients.size(); i++){
             clients[i].update();
         }
         
         // Every x seconds, reset view and follow a new packet
         if(ofGetElapsedTimeMillis() - timerStartTime >= 10000){
             resetView();
         }
         
         // Zoom in or out of the camera
         cameraDistance += distanceSpeed;
        
        if(progress > 5000){
               changeScene(1);
           }

    }
        
    // Log FPS
//    ofLog(OF_LOG_NOTICE, std::to_string(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    backgroundController.draw();
    
    ofEnableDepthTest();
    
    if(sceneManager.activeScene == 1){
        drawFocusScene();
    }else if(sceneManager.activeScene ==2 ){
        drawOverviewScene();
    }
    
    ofDisableDepthTest();
    // border
    //    ofNoFill();
    //    ofSetColor(255,0,0,255);
    //    ofDrawRectangle(0, 1, ofGetScreenWidth()-1,ofGetScreenHeight()-1);
    
    // Fade in start of scene
    int progress = sceneManager.getSceneProgress();
    if(progress < 5000){
        ofFill();
        ofSetColor(0,0,0, ofMap(sceneManager.getSceneProgress(),0,5000,255,0));
        ofDrawRectangle(0,0,screenWidth,screenHeight);
    }
    
    // Letterbox
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(0, 0, screenWidth, 50);
    ofDrawRectangle(0, screenHeight-50, screenWidth, 50);
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

    // Draw all Clients
    for(int i=0; i<clients.size(); i++){
      clients[i].draw();
    }
    int progress = sceneManager.getSceneProgress();
    // If the packet has reached its destination, set camera target to its destination
    if(finishedFollowingPacket && progress > 0){
      
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
//          ofLog(OF_LOG_NOTICE, std::to_string(cameraTarget.));
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
    float progressF = sceneManager.getSceneProgressF();

    for(int i=0; i<circleCount; i++){

        
        int colorFade =  ofMap(sin(((progressF*(progressF/13))+ PI*(circleCount-i)*0.01)*1.5), -1, 1, 255, 0);
         
        ofSetColor(255,255,255,colorFade);
        ofPushMatrix();

       if(progress % 15000 > 11000 ){
          
           int rotation = ofMap(sin((progressF)/4 + PI*(circleCount-i)*0.5), -1, 1, 0, 360);
           int rotation2 = ofMap(sin((progressF)/4 + PI*(circleCount-i)*0.5 + 0.5*PI), -1, 1, 0, 180);
           int rotation3 = ofMap(sin((progressF)/4 + PI*(circleCount-i)*0.5 + PI), -1, 1, 0, 360);

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
    
    
    if(progress > 69000){
        if(progress > 73000){
//                if(!highPitchIsPlaying){
//                    highPitch.play();
//                    highPitchIsPlaying = true;
//                 }
               ofFill();
               ofSetColor(255);
               ofDrawRectangle(0, 0, screenWidth, screenHeight);
        }else{
            int chance = ofRandom(1,4);
            ofFill();
            ofSetColor(255);

            if(chance == 1){
                ofDrawRectangle(0, 0, screenWidth/2, screenHeight);
            }else if(chance==2){
               ofDrawRectangle(screenWidth/2, 0, screenWidth/2, screenHeight);
            }
        }
    }
    
    if(progress > 64000){
        
        if(!tickLowIsPlaying){
            tickLow.play();
            tickLowIsPlaying = true;
        }
        
        ofFill();
           
           int random = ofRandom(1,5);
           ofColor color(0,0,0,255);
           if(random==1){
               color.r = 255;
           }else if(random==2){
               color.g = 255;
           }else if (random ==3){
               color.b = 255;
           }else if (random == 4){
               color.r = 255;
               color.g = 255;
               color.b = 255;
           }
           ofSetColor(color);
        
        int bars;
        int maxThick;

        
        if(progress > 69000){
            bars = ofRandom(30,100);
            maxThick = 300*(1/bars);
        }else{
            bars = ofRandom(10,30);
            maxThick = ofRandom(2,4);
        }
        
        for(int i=0; i< bars; i++){
            float height1 = ofRandom(1,maxThick);
            float height2 = ofRandom(1,maxThick);
          
            float y1 = ofRandom(0,screenHeight);
            float y2 = ofRandom(0,screenHeight);
         
            ofDrawRectangle(1, y1, screenWidth/2, height1);
             ofDrawRectangle(screenWidth/2, y2, screenWidth, height2);
          
        };
        for(int i=0; i< 10; i++){
          float height3 = ofRandom(1,20);
          float y3 = ofRandom(0,screenHeight);
          ofDrawRectangle(1, y3, screenWidth, height3);
        }

        ofSetColor(255,255,255,255);
        ofNoFill();
    }
    
    if(progress > 65000){
           
           for (int i=0; i < wifiReader.networks.size(); i++) {
              WifiNetwork network = wifiReader.networks[i];
                font.drawString(network.strength + "dB", 110,100+i*15);
              font.drawString(network.ssid, 200,100+i*15);
              font.drawString(network.id, 400,100+i*15);
               font.drawString(network.security, 600,100+i*15);
    
           }
           
       }


}

void ofApp::changeScene(int scene){
    switch(scene){
        case 1:
            bgSound.stop();
            camera.reset();
            cameraDistance = 380;
            break;
        case 2:
            resetView();
            bgSound.play();
            tickLow.stop();
            break;
            
    }
    sceneManager.startScene(scene);
}
