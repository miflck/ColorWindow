//
//  SerialManager.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 11.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "SerialManager.h"
#include "ApplicationController.h"



SerialManager::SerialManager(){
    init();
}


SerialManager::~SerialManager(){
    
}


//------------------------------------------------------


void SerialManager::init(){
    cout<<"init SerialManager"<<endl;
    bAddedListeners = false;
    turnOn();
    
    //__arduino____________________________
    serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    serial.setup(deviceList[1].getDeviceName(),115200); // mac osx mega
    
    nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
    windowNum=0;

    
}


void SerialManager::update(){
   // cout<<"SerialManager is updating"<<endl;
    //__color buffer______________________
    updateColorBuffer();

}

void SerialManager::draw(){
  //  cout<<"SerialManager is Drawing"<<endl;
}


void SerialManager::exit(){
   // cout<<"exit SerialManager"<<endl;
}




//EVENTS
//------------------------------------------------------

void SerialManager::addListeners() {
    if(!bAddedListeners){
        ofAddListener(ofEvents().update, this, &SerialManager::_update);
        ofAddListener(ofEvents().draw, this, &SerialManager::_draw);
        ofAddListener(ofEvents().exit, this, &SerialManager::_exit);
        
    }
    bAddedListeners = true;
}


void SerialManager::removeListeners() {
	ofRemoveListener(ofEvents().update, this, &SerialManager::_update);
    ofRemoveListener(ofEvents().draw, this, &SerialManager::_draw);
    ofRemoveListener(ofEvents().exit, this, &SerialManager::_exit);
    
    bAddedListeners = false;
}


//EVENT HANDLER
//------------------------------------------------------

void SerialManager :: _update( ofEventArgs &e )
{
	update();
}

void SerialManager :: _draw( ofEventArgs &e )
{
	draw();
}


void SerialManager :: _exit( ofEventArgs &e )
{
	exit();
}






//--------------------------------------------------------------

void SerialManager::updateColorBuffer(){
    
    writeToArduino=false;
    if(ofGetFrameNum()%2==0)writeToArduino=true;
    
    if(writeToArduino){
        for(int i=0;i<windowNum;i++){
            if(APPC->windows[i].hasUpdatedColor()){
                APPC->windows[i].hasReadUpdateBuffer();
                ofColor sendCol= APPC->windows[i].getColor();
                colorbuffer.push_back(i);
                
                if(sendCol.r==26)sendCol.r=27;
                if(sendCol.g==26)sendCol.g=27;
                if(sendCol.b==26)sendCol.b=27;
                
                colorbuffer.push_back(sendCol.r);
                colorbuffer.push_back(sendCol.g);
                colorbuffer.push_back(sendCol.b);
                colorbuffer.push_back(26);
            }
        }
    }
    
    
    int shiftAmmount=10;
    if(colorbuffer.size()>=shiftAmmount){  
        for (int i=0;i<shiftAmmount;i++){
            serial.writeByte(colorbuffer[i]);
        }
        colorbuffer.erase(colorbuffer.begin(),colorbuffer.begin()+shiftAmmount);
    }
    else{
        int size=colorbuffer.size();
        for (int i=0;i<size;i++){
            serial.writeByte(colorbuffer[i]);
        }      
        colorbuffer.erase(colorbuffer.begin(),colorbuffer.begin()+size);
    }   
    if(colorbuffer.size()>0){
      //  cout<<"colorBuffer size"<<colorbuffer.size()<<endl;
    }
}












//Event Helper
//------------------------------------------------------

void SerialManager::turnOn(){
    if(!bAddedListeners){
        addListeners();
    }
}


void SerialManager::turnOff(){
    if(bAddedListeners){
        removeListeners();
    }
}


bool SerialManager::isRunning(){
    return bAddedListeners;
}


void SerialManager::reset(){
    //reset App
}

void SerialManager::setWindowNum(int _num){
    windowNum=_num;
}

