//
//  ApplicationController.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//
#pragma once

#ifndef ColorWindows_ApplicationController_h
#define ColorWindows_ApplicationController_h


#include "ofMain.h"

#include "ofxColorFactory.h"
#include "Window.h"


//#include "KinectManager.h"
#include "SerialManager.h"
#include "ApplicationBase.h"

#include "ofxKinectUsers.h"
#include "ofxOneDollar.h"
#include "SimpleButton.h"
#include "UdpManger.h"


#define SET_COLOR 300
#define SET_TRIGGERVALUE 400
#define SET_DEBUG 500
#define ONE_RIGHT NUM_WINDOWS+1;
#define NUM_WINDOWS 16


//#include "ofxXmlSettings.h"

//#include "TextureManager.h"
//#include "SettingsManager.h"

//#include "SoundinputController.h"
//#include "BlobTrackingController.h"

//#include "Constants.h";
//#include "Observable.h"

//for convenience
#define APPC ApplicationController::getInstance()
/*
struct lineStruct {  
    vector<ofVec2f> myline;
};
*/

class ApplicationController {
	
public:
	
	static ApplicationController* getInstance();
	void initialize();
	bool isInitialized();
	
    void sayHello();
    
    void gestureRecognized(gesture &g);
    bool bUseKinect;
    
	//Manager:
//    KinectManager * kinect_manager;
    SerialManager * serial_manager;
    UdpManager *udp_manager;
    
    void setAppById(string _identifier);

    
    
    //ofxUser
    ofxKinectUsers	inter;
    ofxGestures		gest;
    
	void	inPose(ofxUser & user);
	void	inGesture(ofxUser & user);
	void	userIn(ofxUser & user);
	void	userMove(ofxUser & user);
	void	userOut(ofxUser & user);
    void	gestureInit(ofxUser & user);
    void    notGestureInit(ofxUser & user);
    
    void completedMove(ofxUser & user);    
    
    void gotMessage(ofMessage &msg);
    
    bool drawInterfaceDebug;

     
    
    
	
	//Windows
    ofxColorFactory colorfactory;
    vector<Window> windows;
    float windowNum;
    bool showWindows;
    
    void setIsInFront(int id, bool _isinfront);
    void setIsHalfInFront(int id, bool _isinfront);
    
    //color
    float colorpos;
    ofColor colorposColor;
    float mixspeed;
    void fadeAllWindows();
    
    
    void setGeneralLerpSpeed(float _lerpspeed);

	
    void startAWave();
    
	
private:

    
	ApplicationController();
	static ApplicationController* instance;
	bool initialized;
	void _update(ofEventArgs &e);
	void _draw(ofEventArgs &e);
    
    ApplicationBase* activeApplication;
	map<string, ApplicationBase*>applications;
	map<string,ApplicationBase*>::iterator app;
    
    void updateSendData();
    

    void fadeAllWindows(ofColor _col, int _time);

    
};

#endif
