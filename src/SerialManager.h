//
//  SerialManager.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 11.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_SerialManager_h
#define ColorWindows_SerialManager_h
#include "ofMain.h"



class SerialManager {
public:
    SerialManager();
    virtual ~SerialManager();

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
