//
//  Packet.hpp
//

#ifndef Packet_hpp
#define Packet_hpp

#include <stdio.h>
#include "MovingBall.hpp"
#include "ofMain.h"

class Client;
class Beacon;

class Packet {
    
public:
    
    void setup(MovingBall* _origin, MovingBall* _destination, float _speed);
    void update();
    void draw();

    MovingBall* origin;
    MovingBall* destination;

    float speed;
    float progress;
    
    bool finished;
    bool deletable;
    float finishTime;
    
    ofPoint position;
    Packet();
    
    private:
};

#endif /* Packet_hpp */
