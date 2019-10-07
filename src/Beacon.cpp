//
//  Beacon.cpp
//

#include "Beacon.hpp"
#include "Client.hpp"

Beacon::Beacon(){
    packetLimit = ofRandom(5,10);
}

void Beacon::setup(Client* _client){
    
    client = _client;
    
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
   int x = client->position.x + ofRandom(60,350) *  xDir;
   int y = client->position.y + ofRandom(60,350) *  yDir;
   int z = client->position.z + ofRandom(60,350) * zDir;
    
    position.set(x,y,z);
    
    speedX = ofRandom(-0.3, 0.3);
    speedY = ofRandom(-0.3, 0.3);
    speedZ = ofRandom(-0.3, 0.3);
    
}

void Beacon::update(){
    if(position.x < -900 ){
        position.x = -900;
        speedX *= -1;
    } else if(position.x >900){
        position.x = 900;
        speedX *= -1;
    }
    
    if(position.y < -900 ){
        position.y = -900;
        speedY *= -1;
    } else if(position.y > 900){
        position.y = 900;
        speedY *= -1;
    }
    
    if(position.z < -900 ){
        position.z = -900;
        speedZ *= -1;
    } else if(position.z > 900){
        position.z = 900;
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
        Packet packet = Packet(speed,direction,client,this);
        packets.push_back(packet);
    }
    
  for(int i=0; i< packets.size(); i++){
      if(packets[i].deletable){
          packets.erase(packets.begin() + i);
      }else{
        packets[i].update();
      }
  }
}

void Beacon::draw(){
    
    // Draw white sphere
    ofSetSphereResolution(4);
    ofSetColor(255);
    ofNoFill();
    ofDrawSphere(position.x, position.y, position.z, 18);
    
    // Blue plus Sign in the middle (+)
    ofSetColor(0,0,255);
    ofDrawLine(position.x-5,position.y,position.z,position.x+5,position.y,position.z);
    ofDrawLine(position.x,position.y-5,position.z,position.x,position.y+5,position.z);
    ofNoFill();
    
    for(int i=0; i< packets.size(); i++){
         packets[i].draw();
     }
}
