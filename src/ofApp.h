#pragma once

#include "Packet.hpp"
#include "Client.hpp"

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void setupArduino(const int &version);
        void audioOut( ofSoundBuffer &outBuffer);
        void receiveString(const string& message);
    
        double phase;
        double frequency;
    
        int backgroundValue;
        int backgroundCounter;
        int backgroundFadeSpeed;
    
        int followTargetClient;
        int followTargetBeacon;
   float cameraDistance;
    float distanceSpeed;
    int finishedPositionType;
    
    Client* finishedClient;
    Beacon* finishedBeacon;
    
    bool finishedFollowingPacket = false;
   ofPoint finishedPosition;

    int backgroundMode;
    
        vector<Packet> packets;
        vector<Client> clients;
    
        ofArduino arduino;
        ofTrueTypeFont arialFont;
    
        ofSoundStream soundStream;
        ofSoundPlayer bgSound;
        ofSoundPlayer highBeep;
        ofSoundPlayer  buildUp;  
    
        ofEasyCam camera;
        ofLight light; 

};
