//
//  ScreenSaverController.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_ScreenSaverController_h
#define ColorWindows_ScreenSaverController_h


#pragma once

#define CIRCLE_TIME 10

#include "ofMain.h"
#include "ScreenSaver.h"
#include "ApplicationBase.h"
#include  "global.h"
    class ScreenSaverController: public ApplicationBase {
public:
    ScreenSaverController();
    virtual ~ScreenSaverController();
    
    
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
        
        
        


        
    //structure
    void init();
    void update();
    void draw();
    void exit();
    
    void generateNewColors();
    void generateNewColorsFromColor(ofColor _col);
    
    void jump(int _id, int _fadespeed);
    
    vector<float> jumptime;
        

        
    void generateNewJumptimes();
        
        
private: 
    //events
    bool bAddedListeners;
    bool bIsRunning;
    float now;
        float then;
    
};


#endif
