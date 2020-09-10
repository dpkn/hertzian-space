//
//  Packet.cpp
//

#include "Packet.hpp"
#include "Client.hpp"
#include "Beacon.hpp"

#include "MovingBall.hpp"

//--------------------------------------------------------------
Packet::Packet(){
    
}

//--------------------------------------------------------------
void Packet::setup(MovingBall* _origin, MovingBall* _destination, float _speed){
    origin = _origin;
    position = _origin->position;
    destination = _destination;
    speed = _speed;
    
    finished = false;
    deletable = false;
}

//--------------------------------------------------------------
void Packet::update(){

    position.x = ofLerp(origin->position.x, destination->position.x, progress);
    position.y = ofLerp(origin->position.y, destination->position.y, progress);
    position.z = ofLerp(origin->position.z, destination->position.z, progress);

    if(!finished && progress >= 1){
        finished = true;
        finishTime = ofGetElapsedTimeMillis();
        
    }else if(!finished){
        progress += speed;
        
    }else if(finished && !deletable){
        float timer = ofGetElapsedTimeMillis() - finishTime;
        
        if (timer >= 15000) {
            deletable = true;
        }
    }
}

//--------------------------------------------------------------
void Packet::draw(){
    if(!finished){
        ofSetColor(0,255,0);
        ofDrawBox(position,3);
    }
}


