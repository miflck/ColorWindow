//
//  ApplicationBase.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_ApplicationBase_h
#define ColorWindows_ApplicationBase_h

#include "ofMain.h"
//#include "ApplicationController.h"


class ApplicationBase {
public:
    ApplicationBase();
    virtual ~ApplicationBase();
    
    
    //events
    virtual void addListeners		();
	virtual void removeListeners	();
    
    virtual void _update(ofEventArgs &e);
    virtual void _draw(ofEventArgs &e);
    virtual void _exit(ofEventArgs &e);
    virtual void keyPressed(ofKeyEventArgs &e);

    
    virtual bool isRunning();
    virtual void turnOn();
    virtual void turnOff();
    virtual void reset();
    virtual string getId();
    virtual void setId(string _id);

    
    
    //structure
   virtual void init();
   virtual void update();
   virtual void draw();
   virtual void exit();
    
    bool bAddedListeners;
    bool bIsRunning;
    
    

    
 private: 
    //events
     string myId;


    
    
};

#endif
