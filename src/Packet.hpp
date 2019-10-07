//
//  Packet.hpp
//

#ifndef Packet_hpp
#define Packet_hpp

#include <stdio.h>
#include "ofMain.h"

class Client;
class Beacon;

class Packet {
    
    public:
    
        void setup();
        void update();
        void draw();
    
        Client* client;
        Beacon* beacon;
    
        float speed;
        float progress;
    float direction;
    
    bool finished;
    bool deletable;
    float startTime;
    
    ofPoint position;
        Packet(float _speed, float _direction, Client* _client, Beacon* _beacon);
    ofPoint getDestinationPosition();
    int getDestinationType();
    private:
};

#endif /* Packet_hpp */
