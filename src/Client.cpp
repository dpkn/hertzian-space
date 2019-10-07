//
//  Client.cpp
//
#include "Client.hpp"
using namespace glm;

Client::Client(){
    
}

void Client::setup(){
    
    t = 0;
    
    id = ofRandom(233245,99999);
    
    float x = ofRandom(-550,550);
    float y = ofRandom(-550,550);
    float z = ofRandom(-550,550);
    
    position.set(x,y,z);
    
    beacons.assign(ofRandom(10,15),Beacon());
    
    speedX = ofRandom(0, 0.5);
    speedY = ofRandom(0, 0.5);
    speedZ = ofRandom(0, 0.5);
    
    for(int i=0; i< beacons.size(); i++){
        beacons[i].setup(this);
    }
}

void Client::update(){
    if(position.x < -550 ){
        position.x =-550;
        speedX *= -1;
    } else if(position.x > 550){
        position.x = 550;
        speedX *= -1;
    }
    
    if(position.y < -550 ){
        position.y = -550;
        speedY *= -1;
    } else if(position.y > 550 ){
        position.y = 550;
        speedY *= -1;
    }
    
    if(position.z < -550 ){
        position.z = -550;
        speedZ *= -1;
    } else if(position.z > 550){
        position.z = 550;
        speedZ *= -1;
    }
    
    position.x+=speedX;
    position.y+=speedY;
    position.z+=speedZ;
    
    for(int i=0; i< beacons.size(); i++){
        beacons[i].update();
    }
    
}

void Client::draw(){
    
    // Draw a red sphere
    ofSetSphereResolution(10);
    ofSetColor(255,0,0);
    ofDrawSphere(position.x,position.y,position.z,40);
    
    // Draw a plus (+) sign at the center of the sphere
    ofDrawLine(position.x-5,position.y,position.z,position.x+5,position.y,position.z);
    ofDrawLine(position.x,position.y-5,position.z,position.x,position.y+5,position.z);
      
    if(t>=1){
        t = 0;
    }
    
    for(int i=0; i< beacons.size(); i++){
        
        // Draw beacons
        beacons[i].draw();
        
        // Draw line between beacons and client
        ofSetColor(255);
        ofDrawLine(position.x, position.y, position.z, beacons[i].position.x, beacons[i].position.y, beacons[i].position.z);

    }
    
    t += 0.001;
}
