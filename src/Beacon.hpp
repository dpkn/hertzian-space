//
//  Beacon.hpp
//  emptyExample
//
//  Created by Daan Korssen on 05/09/2019.
//

#ifndef Beacon_hpp
#define Beacon_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Packet.hpp"

class Client;

class Beacon {
    
public: // place public functions or variables declarations here
    
    Client* client;
    
    void setup(Client* _client);
    void update();
    void draw(ofTrueTypeFont * font);
    
    ofPoint position;
    float speedY;   // speed and direction
    float speedX;
    float speedZ;

    
    int packetLimit;
    
    vector<Packet> packets;
    
    Beacon();
private:
};

#endif /* Beacon_hpp */
