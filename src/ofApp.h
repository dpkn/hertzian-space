#pragma once

#include "MovingBall.hpp"
#include "BackgroundController.hpp"
#include "Packet.hpp"
#include "Client.hpp"

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
    void setup();
    void update();
    void draw();
    void resetView();
    
    BackgroundController backgroundController;

    float cameraDistance;
    float distanceSpeed;
    Packet* cameraTarget;
    MovingBall* finishedTarget;
    bool finishedFollowingPacket = false;

    float timerStartTime;

    vector<Packet> packets;
    vector<Client> clients;

    ofSoundPlayer bgSound;
    ofSoundPlayer highBeep;

    ofEasyCam camera;

};
