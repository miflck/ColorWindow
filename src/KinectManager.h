//
//  KinectManager.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 05.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_KinectManager_h
#define ColorWindows_KinectManager_h
#endif


#define USE_IR // Uncomment this to use infra red instead of RGB cam...
# 

#pragma once
#include "ofMain.h"
#include "ofxOpenNI.h"
#include "ofxGestureGenerator.h"



class KinectManager {


public:
    KinectManager();
    virtual ~KinectManager();
    
    bool isConnected;    
	void addListeners		();
    void addDebugDrawListener ();
    void addKeyListener ();
    
	void removeListeners	();
    void removeDebugDrawListener();
    void removeKeyListener();
    
    void turnOnKeyListener();
    void turnOffKeyListener();
    bool isKeyListening();

    
    bool bAddedListeners;
    bool bAddedDrawListener;
    bool bAddedKeyListener;
    
    void _update(ofEventArgs &e);
    void _debugDraw(ofEventArgs &e);
    void _exit(ofEventArgs &e);
    void keyPressed(ofKeyEventArgs &e);
    
    void setDraw(bool b);
    void showDebug();
    void hideDebug();
    void toggleDebug();
    bool isDebugDrawing();
    
    bool doDraw;
    
    
    
    void init();
    void debugDraw();
    void update();
    void exit();
    

   

    void	setupRecording(string _filename = "");
	void	setupPlayback(string _filename);
	string	generateFileName();
    
    
    bool	isLive, isTracking, isRecording, isCloud, isCPBkgnd, isMasking;
	bool	isTrackingHands, isFiltering;

    ofxOpenNIContext	recordContext, playContext;
	ofxDepthGenerator	recordDepth, playDepth;

    ofxGestureGenerator gestGen;
    void gestureRecognized(gesture &g);
    
    
#ifdef USE_IR
	ofxIRGenerator		recordImage, playImage;
#else
	ofxImageGenerator	recordImage, playImage;
#endif
    
	ofxHandGenerator	recordHandTracker, playHandTracker;
    
	ofxUserGenerator	recordUser, playUser;
	ofxOpenNIRecorder	oniRecorder;

#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
	//ofxHardwareDriver	hardware;
#endif

    
    void				drawMasks();
	void				drawPointCloud(ofxUserGenerator * user_generator, int userID);
	int					nearThreshold, farThreshold;
	int					pointCloudRotationY;
	ofImage				allUserMasks, user1Mask, user2Mask, depthRangeMask;
	float				filterFactor;


    
    
private:
   
};