//
//  ApplicationController.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "ApplicationController.h"
#include "TestClassController.h"
#include "ScreenSaverController.h"
#include "MaestroController.h"



ApplicationController* ApplicationController::instance = 0;

ApplicationController* ApplicationController::getInstance() {
	if (!instance) {
		instance = new ApplicationController();
	}
	return instance;
}

ApplicationController::ApplicationController() {
	
}

void ApplicationController::initialize() {
 
	initialized=true;
    cout<<"init ApplicationController"<<endl;
    ofSetLogLevel(OF_LOG_SILENT);

    bUseKinect=true;
    drawInterfaceDebug=false;
    



 /*   if(bUseKinect){
        kinect_manager= new KinectManager();
        kinect_manager->showDebug();
        ofAddListener(kinect_manager->gestGen.gestureRecognized,this,&ApplicationController::gestureRecognized);    
    }
   */ 


    
    
    //__ofxUser______________________________
    
    ofRegisterGetMessages(this);
    
//    inter.setup(kinect_manager,"config.xml");
    inter.setup("config.xml");

	ofAddListener(inter.inPose,this,&ApplicationController::inPose);
	ofAddListener(inter.inGesture,this,&ApplicationController::inGesture);
	ofAddListener(inter.userIn,this,&ApplicationController::userIn);
	ofAddListener(inter.userMove,this,&ApplicationController::userMove);
	ofAddListener(inter.userOut,this,&ApplicationController::userOut);
    ofAddListener(inter.gestureInit,this,&ApplicationController::gestureInit);
	ofAddListener(inter.notGestureInit,this,&ApplicationController::notGestureInit);
    
    ofAddListener(inter.completedMove,this,&ApplicationController::completedMove);
    
    //Windows
    showWindows=true;
    ofColor c;
	c.r = 255;
	c.g = 255;
	c.b = 0;
    
    windowNum =NUM_WINDOWS;

    colorfactory.generateColorSwatchesFromColor(windowNum,5,c);
    int winSize=200;
    int winMargin=20;
    ofVec2f winPos(winMargin,winMargin);
    
    for(int i=0;i<windowNum;i++){
        Window win=*new Window();
        win.setId(i);
        win.setSize(winSize, winSize);
        win.setPosition(winPos);
        win.setColor(colorfactory.getSwatchAtIndex(i));
        winPos.x+=(winSize+winMargin);
        if(winPos.x+winSize>ofGetWidth()){
            winPos.x=winMargin;
            winPos.y+=winSize+winMargin;
        }
        winPos.set(winPos.x, winPos.y);
        windows.push_back(win);
    }    
    
    udp_manager=new UdpManager();
    udp_manager->sendToId(0, ofColor(255,0,0), 0.5,100);
   // udp_manager->turnOn();
    
    activeApplication=NULL;
	
        
	applications["testClass"]=new TestClassController();
    applications["testClass"]->setId("testClass");
	applications["screenSaver"]=new ScreenSaverController();
    applications["screenSaver"]->setId("screenSaver");
    
	applications["maestro"]=new MaestroController();
    applications["maestro"]->setId("maestro");

    
    setAppById("screenSaver");

    ofAddListener(ofEvents().update, this, &ApplicationController::_update);
    ofAddListener(ofEvents().draw, this, &ApplicationController::_draw);

}

bool ApplicationController::isInitialized(){
	return initialized;
}

void ApplicationController::_update(ofEventArgs &e) {
    
    if(bUseKinect){
    
    //__User______________________________
    inter.update();
    string id;
    if(activeApplication!=NULL){
    id=activeApplication->getId();
    }
    
    
 int trackedUser=inter.openni.userGenerator.getNumberOfTrackedUsers();
    
   if(trackedUser>0 && id=="screenSaver"){
        for (int i=0;i<MAX_USERS;i++){
            ofxUser  u=inter.users[i];
            if (u.bones) {
                setAppById("maestro");
                fadeAllWindows();
                return;
            }
        }
        
    }
    
    else if(trackedUser<1 && id=="maestro"){
            setAppById("screenSaver");
    }
  
    }
     
    //__color___________________________

    if (colorpos>ofGetWidth()) {
        colorpos=0;
    }
    
    float hue=ofMap(colorpos, 0, ofGetWidth(), 0, 255);
    colorposColor.setHsb(hue, 255, 255);    
    
	
    //__windows___________________________
    
    for(int i=0;i<windowNum;i++){
        windows[i].update();        
    }
    
    //__UDP ___________________________
    updateSendData();

    udp_manager->update();
}

void ApplicationController::_draw(ofEventArgs &e) {
   
    //ofBackground(colorposColor);
    
    
    if(showWindows){
        //__windows___________________________
        for(int i=0;i<windowNum;i++){
           // windows[i].draw();
        }
    }
    
    

    
    
    //__User______________________________

    if (drawInterfaceDebug){
		//inter.debugDraw();
        }

    }

void ApplicationController::setAppById(string _identifier){
	
	
	if(activeApplication!=NULL){
		activeApplication->turnOff();
	}
	
        
    app=applications.find(_identifier);
		activeApplication=(*app).second;
	
    
	if(activeApplication!=NULL && !activeApplication->isRunning()){
        activeApplication->turnOn();
	}
	
	
}


void ApplicationController::setIsInFront(int _id, bool _isinfront){
    int id=_id;
    bool isinfront=_isinfront;
   cout<<isinfront<<endl;
    string  appId;
    if(activeApplication!=NULL){
        appId=activeApplication->getId();
    }
    if(appId=="screenSaver"){
        
        if(id-1>=0)windows[id-1].setIsHalfInfront(isinfront);
        
        windows[id].setIsInfront(isinfront);
        
        if(id+1<windowNum)windows[id+1].setIsHalfInfront(isinfront);

    }
}

//not used
void ApplicationController::setIsHalfInFront(int _id, bool _isinfront){
    int id=_id;
    bool isinfront=_isinfront;
    cout<<isinfront<<endl;
    string  appId;
    if(activeApplication!=NULL){
        appId=activeApplication->getId();
    }
    if(appId=="screenSaver"){
        windows[id].setIsHalfInfront(isinfront);
        
    }
}



void ApplicationController::startAWave(){
    string  appId;

    if(activeApplication!=NULL){
        appId=activeApplication->getId();
    }
    if(appId=="screenSaver"){
        windows[0].setIsHalfInfront(true);
    }

}


void ApplicationController::setGeneralLerpSpeed(float _lerpspeed){
    float speed=_lerpspeed;
    string  appId;
    if(activeApplication!=NULL){
        appId=activeApplication->getId();
    }
    if(appId=="screenSaver"){
        for(int i=0;i<NUM_WINDOWS;i++){
        windows[i].setGeneralLerpSpeed(speed);
        }
    }
}



void ApplicationController::sayHello(){
    cout<<"hello"<<endl;
}



void ApplicationController::gestureRecognized(gesture &g){

}


//--------------------------------------------------------------

void ApplicationController::updateSendData(){
    
    for(int i=0;i<NUM_WINDOWS;i++){
        
        if(windows[i].hasUpdatedColor()){
            if(ofGetFrameNum()%1==0){
                ofColor sendCol= windows[i].getColor();
                udp_manager->sendToId(i,sendCol,0,SET_COLOR);
                windows[i].hasReadUpdateBuffer();
            }
            
            
        }
    }
}


void ApplicationController::fadeAllWindows(ofColor _col, int _time){
    for(int i=0;i<NUM_WINDOWS;i++){
                ofColor fadecol= windows[i].getColor();
        
        fadecol.setBrightness(0);
        
        windows[i].setFadeColor(fadecol,1);

        
        }

}


void ApplicationController::fadeAllWindows(){
    for(int i=0;i<NUM_WINDOWS;i++){
        ofColor fadecol= windows[i].getColor();
        fadecol.setBrightness(fadeAllBrightness);
        fadecol.setSaturation(fadeAllSaturation);

        
        windows[i].setFadeColor(fadecol,1);
        
        
    }
    
}




//--------------------------------------------------------------
void ApplicationController::gotMessage(ofMessage &msg){
    
    cout<<"gotmessage:"<<msg.message<<endl;
    if(msg.message=="in Gesture"){
        
    }else{
        windows[0].startFeedbacking();
    }
}






//--------------------------------------------------------------
void ApplicationController::inPose(ofxUser & user){
	cout << "INPOSE" << endl;
}

//--------------------------------------------------------------
void ApplicationController::gestureInit(ofxUser & user){
    }

//--------------------------------------------------------------
void ApplicationController::notGestureInit(ofxUser & user){
   }


void ApplicationController::inGesture(ofxUser & user){
	//cout << "INGESTURE" << endl; 
   }

void ApplicationController::userIn(ofxUser & user){
	cout << "USERIN" << endl; 
    
    if(user.bones){
        cout<<"user is alredy tracked";
        windows[0].startFeedbacking();
    }
   }

void ApplicationController::userMove(ofxUser & user){
}

void ApplicationController::userOut(ofxUser & user){
	cout << "USEROUT" << endl; 
}


void ApplicationController::completedMove(ofxUser & user){

}



