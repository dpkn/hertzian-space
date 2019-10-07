//
//  Packet.cpp
//

#include "Packet.hpp"
#include "Client.hpp"
#include "Beacon.hpp"

Packet::Packet(float _speed,float _direction,Client* _client, Beacon* _beacon){
    speed = _speed;
    direction = _direction;
    if(direction == 1){
        progress = 0;
    }else{
        progress = 1;
    }
    
    finished = false;
    deletable = false;
        client = _client;
    beacon = _beacon;
}

void Packet::setup(){

}

ofPoint Packet::getDestinationPosition(){
    if(direction == 1){
        return client->position;
    }else{
        return beacon->position;
    }
}

int Packet::getDestinationType(){
    if(direction == 1){
        return 1;
    }else{
        return 2;
    }
}
void Packet::update(){

    position.x = ofLerp(beacon->position.x, client->position.x, progress);
    position.y = ofLerp(beacon->position.y, client->position.y, progress);
    position.z = ofLerp(beacon->position.z, client->position.z, progress);

    if(!finished){
        progress += speed * direction;
    }else if(finished && !deletable){
        float timer = ofGetElapsedTimeMillis() - startTime;
        if (timer >= 1000) {
            deletable = true;
        }
    }
    
    if(!finished && ((progress >= 1 && direction == 1) || (progress <= 0 && direction == -1))){
        finished = true;
        startTime = ofGetElapsedTimeMillis();
    }
    
}

void Packet::draw(){
    if(!finished){
        ofSetColor(0,255,0);
        ofDrawBox(position,3);
    }
}


