//
//  Client.hpp
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "MovingBall.hpp"
#include "Beacon.hpp"

class Client : public MovingBall {
        
    public:
        
        void setup();
        void update();
        void draw();
    
        vector<Beacon> beacons;
    
        Client();
    private:
};
