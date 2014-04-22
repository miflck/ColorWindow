//
//  UdpManger.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 24.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//



#ifndef ColorWindows_UdpManger_h
#define ColorWindows_UdpManger_h

#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"

#define NUM_WINDOWS 16

#define SET_COLOR 300
#define SET_TRIGGERVALUE 400
#define SET_DEBUG 500
#define ONE_RIGHT NUM_WINDOWS+1;

class UdpManager {
public:
    UdpManager();
    virtual ~UdpManager();
    
    bool isConnected;    
	void addListeners		();
    
	void removeListeners	();
    bool bAddedListeners;
    
    void _update(ofEventArgs &e);
    void _draw(ofEventArgs &e);
    void _exit(ofEventArgs &e);
    
    
    void turnOn();
    void turnOff();
    bool isRunning();
    bool bIsRunning;
    
    
    
    
    void setWindowNum(int _num);    
    
    //structure
    void init();
    void update();
    void draw();
    void exit();
    
    void reset();
    
    
    void setDebug(bool _d);
    
    bool toBool(std::string const& s);

    
    
    void setAllTriggervalues(int _t);
    void setTriggervaluesAtId(int _id, int _t);
    
    
    //udp
    ofxUDPManager udpConnection[NUM_WINDOWS+1];
    ofxUDPManager udpmyself;

    
    //void sendToId(int _id, ofColor _col, float _speed, int _mode);
    void sendToId(int _id, ofColor _col, float _speed, int _mode, int _trigger=0, int _garbage=0);

    void updateUdpSendData();
    
    //Serial
    bool writeToArduino;
    
    //--------COLOR BUFFER------------------
    void updateColorBuffer();
    vector<int> colorbuffer;
    
    
    bool		bSendSerialMessage;			// a flag for sending serial
    char		bytesRead[3];				// data from serial, we will be trying to read 3
    char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
    int			nBytesRead;					// how much did we read?
    int			nTimesRead;					// how many times did we read?
    float		readTime;					// when did we last read?	
    
    ofSerial	serial;
    
    int windowNum;
    
    
};


#endif
