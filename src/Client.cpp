//
//  Client.cpp
//
#include "Client.hpp"
using namespace glm;

Client::Client(){
    
}

void Client::setup(){
    MovingBall::setup(550);
    
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

    // Update position and direction in parent class
    MovingBall::update();
    
    // Update the beacons that belong to this Client
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
      
    // Draw the beacons
    for(int i=0; i< beacons.size(); i++){
        
        beacons[i].draw();
        
        // Draw line between beacon and client
        ofSetColor(255);
        ofDrawLine(position.x, position.y, position.z, beacons[i].position.x, beacons[i].position.y, beacons[i].position.z);

    }

}
