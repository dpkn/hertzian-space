//
//  Client.hpp
//

#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Beacon.hpp"

class Client {
        
    public:
        
        void setup();
        void update();
        void draw();
    
        int id;
        ofPoint position;
        float t;
    
        float speedY; 
        float speedX;
        float speedZ;;
    
        vector<Beacon> beacons;
    
        Client();
    private:
};

#endif /* Client_hpp */


