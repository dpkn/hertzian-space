//
//  Beacon.cpp
//

#include "Beacon.hpp"
#include "Client.hpp"

Beacon::Beacon(){

}

void Beacon::setup(Client* _client){
    MovingBall::setup(900);
    client = _client;
    
    packetLimit = ofRandom(5,10);

    // Pick a random direction for every axis
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
    
    // Place beacon a random distance + direction from its parent Client
    int x = client->position.x + ofRandom(60,350) *  xDir;
    int y = client->position.y + ofRandom(60,350) *  yDir;
    int z = client->position.z + ofRandom(60,350) * zDir;

    position.set(x,y,z);
    
}

void Beacon::update(){
    
    // Update position and direction in parent class
    MovingBall::update();
    
    
    // Every X minutes change the amount of packets on a connection
    if(ofGetElapsedTimeMillis() % 5000 <= 10){
        ofLog(OF_LOG_NOTICE,"Changed packetLimit");
        packetLimit = ofRandom(5,10);
    }
    
    // If there are less packets on the connection than the limit
    // specifies, add one more.
    if(packets.size() < packetLimit){
        
        // Random speed
        float speed = ofRandom(0.01,0.001);

        // Decide if the packet goes from client>packet or reverse
        Packet packet;
        if(ofRandom(1)>0.5){
            packet.setup(client,this,speed);
        }else{
            packet.setup(this,client,speed);
        }
        
        packets.push_back(packet);
    }
    
    // Delete all packets that are ready to be deleted
    // and update the rest
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
    
    // Update the children
    for(int i=0; i< packets.size(); i++){
        packets[i].draw();
    }
}
