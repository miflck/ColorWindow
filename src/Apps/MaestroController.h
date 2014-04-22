//
//  TestClassController.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_MaestroContorller_h
#define ColorWindows_MaestroContorller_h


#define MAX_LINESIZE 100
#define MATCH_SCORE  0.9

#pragma once
#include "ofMain.h"
#include "ApplicationBase.h"
#include "KinectManager.h"
#include "ofxOneDollar.h"
#include "SimpleButton.h"
#include "ofxUser.h"
#include "ColorWave.h"
#include   "global.h"







class MaestroController :public ApplicationBase{
    
public:
    MaestroController();
    virtual ~MaestroController();

    

 /*
    //events
    void addListeners		();
	void removeListeners	();
    
    void _update(ofEventArgs &e);
    void _draw(ofEventArgs &e);
    void _exit(ofEventArgs &e);
    
    bool isRunning();
    void turnOn();
    void turnOff();
    void reset();

  */ 
    void turnOn();
    void turnOff();

    void gestureRecognized(gesture &g);


    
    //structure
    void init();
    void update();
    void draw();
    void exit();
    
    
    
    
    //oneDollar
    void createNewGesture();
    void showMessage(string sMessage, int nDelay = 2000);
    void drawOneDollar();
    void updateHandpos();
    
    SimpleButton save_to_file;		
    SimpleButton clear_line;
    SimpleButton create_gesture;
    SimpleButton find;
    SimpleButton load_from_file;
    
    vector<ofVec2f> line;
    vector<lineStruct> lines;
    vector<ofVec2f> found_gesture;
    ofxOneDollar dollar;
    ofxGesture* oneDollarGest;
    int num_created_gestures;
    
    int mode;
    string message;
    int hide_message_on;
    
    
    //USER
    void completedMove(ofxUser & user);    
    void gestureInit(ofxUser & user);    
    void notGestureInit(ofxUser & user);
    
    
    void keyPressed(ofKeyEventArgs &e);

    
    void generateColors();
    ofColor generateColorVariantFromColor(float range, ofColor _col);
    
 private: 
    
    //events
    bool bAddedListeners;
    bool bIsRunning;

    
    //color
    int colorpos;
    ofColor colorposColor;
    float mixspeed;
    
    
    //Wave
    vector<ColorWave> wave;
    bool startANewWave;
    float wavespeed;

    
};
#endif

