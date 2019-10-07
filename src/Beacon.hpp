//
//  Beacon.hpp
//

#ifndef Beacon_hpp
#define Beacon_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Packet.hpp"

class Client;

class Beacon {
    
public:
    
    Client* client;
    
    void setup(Client* _client);
    void update();
    void draw();
    
    ofPoint position;
    float speedY;
    float speedX;
    float speedZ;

    
    int packetLimit;
    
    vector<Packet> packets;
    
    Beacon();
private:
};

#endif /* Beacon_hpp */
