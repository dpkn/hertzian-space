#pragma once

#include "MovingBall.hpp"
#include "BackgroundController.hpp"
#include "Packet.hpp"
#include "Client.hpp"
#include "WifiReader.hpp"
#include "SceneManager.hpp"

#include "ofxPostProcessing.h"
#include "ofxOsc.h"
#include "ofMain.h"

#define PORT

class ofApp : public ofBaseApp{
    public:
    void setup();
    void update();
    void draw();
    void drawOverviewScene();
    void drawFocusScene();
    void resetView();
    
    WifiReader wifiReader;

    SceneManager sceneManager;
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
    ofSoundPlayer droneLow;
    ofSoundPlayer droneHigh;
    
    float playedDroneAt;
    int droneCount = 0;
    
    ofxPostProcessing post;
    
    ofxOscSender sender;
    ofxOscMessage m;
    
    ofEasyCam camera;

};
