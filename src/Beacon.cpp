//
//  Beacon.cpp
//  emptyExample
//
//  Created by Daan Korssen on 05/09/2019.
//

#include "Beacon.hpp"

Beacon::Beacon(){
    packetLimit = ofRandom(5,10);
}

void Beacon::setup(float _parentX,float _parentY,float _parentZ){
    
    float xDir = 1;
    if(ofRandom(1) > 0.5){
        xDir = -1;
    }
    float yDir = 1;
      if(ofRandom(1) > 0.5){
          yDir = -1;
      }
    float zDir = 1;
      if(ofRandom(1) > 0.5){
          zDir = -1;
      }
   int x = _parentX + ofRandom(50,300) *  xDir;
   int y = _parentY + ofRandom(50,300) *  yDir;
   int z = _parentZ + ofRandom(50,300) * zDir;
    
    position.set(x,y,z);
    
    speedX = ofRandom(-0.3, 0.3);
    speedY = ofRandom(-0.3, 0.3);
    speedZ = ofRandom(-0.3, 0.3);
    
}

void Beacon::update(ofPoint clientPosition){
    if(position.x < -600 ){
        position.x = -600;
        speedX *= -1;
    } else if(position.x >600){
        position.x = 600;
        speedX *= -1;
    }
    
    if(position.y < -600 ){
        position.y = -600;
        speedY *= -1;
    } else if(position.y > 600){
        position.y = 600;
        speedY *= -1;
    }
    
    if(position.z < -600 ){
        position.z = -600;
        speedZ *= -1;
    } else if(position.z > 600){
        position.z = 600;
        speedZ *= -1;
    }
    
     position.x+=speedX;
        position.y+=speedY;
    position.z+=speedZ;
    
    if(ofGetElapsedTimeMillis() % 2000 <= 300){
        ofLog(OF_LOG_NOTICE,"Changed packetLimit");
        packetLimit = ofRandom(5,10);
    }
    
    if(packets.size() < packetLimit){
        float speed = ofRandom(0.01,0.001);
        float direction = 1;
        if(ofRandom(1)>0.5){
            direction = -1;
        }
        Packet packet = Packet(speed,direction);
        packets.push_back(packet);
    }
    
  for(int i=0; i< packets.size(); i++){
      if(packets[i].finished){
          packets.erase(packets.begin() + i);
      }else{
        packets[i].update(position, clientPosition);
      }
  }
}

void Beacon::draw(ofTrueTypeFont * font){
    
    // White sphere
    ofSetSphereResolution(4);
    ofSetColor(255);
    ofNoFill();
    ofDrawSphere(position.x, position.y, position.z, 18);

    //font->drawString("BEACON", position.x,position.y);
    
    // Blue cross in the middle
    ofSetColor(0,0,255);
    ofDrawLine(position.x-5,position.y,position.z,position.x+5,position.y,position.z);
    ofDrawLine(position.x,position.y-5,position.z,position.x,position.y+5,position.z);
    ofNoFill();
    
    for(int i=0; i< packets.size(); i++){
         packets[i].draw();
     }
}
