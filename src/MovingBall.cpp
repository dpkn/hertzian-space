//
//  MovingBall.cpp
//

#include "MovingBall.hpp"
void MovingBall::setup(int _boundingBoxSize){
    boundingBoxSize = _boundingBoxSize;
    speedX = ofRandom(-0.3, 0.3);
    speedY = ofRandom(-0.3, 0.3);
    speedZ = ofRandom(-0.3, 0.3);
}

void MovingBall::update(){
    
    // Check if the ball doesn't leave its boundaries
    if(position.x < -boundingBoxSize ){
        position.x =-boundingBoxSize;
        speedX *= -1;
    } else if(position.x > boundingBoxSize){
        position.x = boundingBoxSize;
        speedX *= -1;
    }

    if(position.y < -boundingBoxSize ){
        position.y = -boundingBoxSize;
        speedY *= -1;
    } else if(position.y > boundingBoxSize ){
        position.y = boundingBoxSize;
        speedY *= -1;
    }

    if(position.z < -boundingBoxSize ){
        position.z = -boundingBoxSize;
        speedZ *= -1;
    } else if(position.z > boundingBoxSize){
        position.z = boundingBoxSize;
        speedZ *= -1;
    }

    // Update position
    position.x+=speedX;
    position.y+=speedY;
    position.z+=speedZ;

};
