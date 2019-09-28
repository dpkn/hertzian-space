//
//  Client.hpp
//  emptyExample
//
//  Created by Daan Korssen on 05/09/2019.
//

#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Beacon.hpp"

class Client {
        
    public: // place public functions or variables declarations here
        
        void setup();
        void update();
        void draw(ofTrueTypeFont *);
    
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


