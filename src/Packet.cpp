//
//  Packet.cpp
//  emptyExample
//
//  Created by Daan Korssen on 04/09/2019.
//

#include "Packet.hpp"

Packet::Packet(float _speed,float _direction){
    speed = _speed;
    direction = _direction;
    if(direction == 1){
        progress = 0;
    }else{
        progress = 1;
    }
    
    finished = false;
}

void Packet::setup(){

    
}

ofPoint Packet::getDestinationPosition(){
////    if(direction == 1){
////        return clientPosition;
////    }else{
////        return beaconPosition;
////    }
}

void Packet::update(ofPoint beaconPosition, ofPoint clientPosition){

    position.x = ofLerp(beaconPosition.x, clientPosition.x, progress);
    position.y = ofLerp(beaconPosition.y, clientPosition.y, progress);
    position.z = ofLerp(beaconPosition.z, clientPosition.z, progress);

    if(!finished){
        progress += speed * direction;
    }
    
    if((progress >= 1 && direction == 1) || (progress <= 0 && direction == -1)){
        finished = true;
    }
    
    ofLog(OF_LOG_NOTICE, std::to_string(progress));
    
}

void Packet::draw(){
    if(!finished){
        ofSetColor(0,255,0);
        ofDrawBox(position,3);
    }
}


