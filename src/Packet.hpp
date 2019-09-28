//
//  Packet.hpp
//  emptyExample
//
//  Created by Daan Korssen on 04/09/2019.
//

#ifndef Packet_hpp
#define Packet_hpp

#include <stdio.h>
#include "ofMain.h"

class Packet {
    
    public: // place public functions or variables declarations here
    
        void setup();
        void update(ofPoint beaconPosition, ofPoint clientPosition);
        void draw();
    
        float speed;
        float progress;
    float direction;
    
    bool finished;
    ofPoint position;
        Packet(float _speed, float _direction);
    ofPoint getDestinationPosition();
    private:
};

#endif /* Packet_hpp */
