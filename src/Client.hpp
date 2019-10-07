//
//  Client.hpp
//

#ifndef Client_hpp
#define Client_hpp

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

#endif /* Client_hpp */


