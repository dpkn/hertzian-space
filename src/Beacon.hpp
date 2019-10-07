//
//  Beacon.hpp
//

#ifndef Beacon_hpp
#define Beacon_hpp

#include <stdio.h>
#include "ofMain.h"
#include "MovingBall.hpp"
#include "Packet.hpp"

class Client;

class Beacon : public MovingBall{
    
public:
    
    Client* client;
    
    void setup(Client* _client);
    void update();
    void draw();
    
    int packetLimit;
    
    vector<Packet> packets;
    
    Beacon();
private:
};

#endif /* Beacon_hpp */
