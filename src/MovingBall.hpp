//
//  MovingBall.hpp
//

#ifndef MovingBall_hpp
#define MovingBall_hpp

#include <stdio.h>
#include "ofMain.h"

class MovingBall {
public:
    
    // Position and Speed
    int boundingBoxSize;
    ofPoint position;
    float speedX, speedY, speedZ;
    
    void setup(int _boundingBoxSize);
    void update();

};

#endif /* MovingBall_hpp */
