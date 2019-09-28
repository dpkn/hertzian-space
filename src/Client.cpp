//
//  Client.cpp
//  emptyExample
//
//  Created by Daan Korssen on 05/09/2019.
//

#include "Client.hpp"
using namespace glm;

Client::Client(){
    
}

void Client::setup(){
    
    t = 0;
    
    id = ofRandom(233245,99999);
    
    float x = ofRandom(-600,600);
    float y = ofRandom(-600,600);
    float z = ofRandom(-600,600);
    
    position.set(x,y,z);
    
    beacons.assign(15,Beacon());
    
    speedX = ofRandom(0, 0.5);           // and random speed and direction
    speedY = ofRandom(0, 0.5);
    speedZ = ofRandom(0, 0.5);
    
    for(int i=0; i< beacons.size(); i++){
        beacons[i].setup(this);
    }
}

void Client::update(){
    if(position.x < -600 ){
        position.x =-600;
        speedX *= -1;
    } else if(position.x > 600){
        position.x = 600;
        speedX *= -1;
    }
    
    if(position.y < -600 ){
        position.y = -600;
        speedY *= -1;
    } else if(position.y > 600 ){
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
    
    for(int i=0; i< beacons.size(); i++){
        beacons[i].update();
    }
    
}

void Client::draw(ofTrueTypeFont * font){
    
    // Red Sphere
    ofSetSphereResolution(10);
    ofSetColor(255,0,0);
    ofDrawSphere(position.x,position.y,position.z,40);
    
    // plus sign
    ofDrawLine(position.x-5,position.y,position.z,position.x+5,position.y,position.z);
    ofDrawLine(position.x,position.y-5,position.z,position.x,position.y+5,position.z);
    
   // font->drawString("CLIENT", position.x,position.y);
      
    
    if(t>=1){
        t = 0;
    }
    
    for(int i=0; i< beacons.size(); i++){
        
        // Draw beacons
        beacons[i].draw(font);
        
        // Draw line between beacons and client
        ofSetColor(255);
        ofDrawLine(position.x, position.y, position.z, beacons[i].position.x, beacons[i].position.y, beacons[i].position.z);
        


    }
    t += 0.001;
}
