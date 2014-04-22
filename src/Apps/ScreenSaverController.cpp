//
//  ScreenSaverController.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "ScreenSaverController.h"
#include "ApplicationController.h"


ScreenSaverController::ScreenSaverController(){
    init();
}


ScreenSaverController::~ScreenSaverController(){
    
}


//------------------------------------------------------


void ScreenSaverController::init(){
    cout<<"init ScreenSaverController"<<endl;
    bAddedListeners = false;
    then=ofGetElapsedTimef();
    
    float time =ofRandom(CIRCLE_TIME);
    for(int i=0;i<APPC->windowNum;i++){
        time =ofRandom(CIRCLE_TIME);
        jumptime.push_back(time);
    }
    
}


void ScreenSaverController::update(){
    //cout<<"ScreenSaverController is updating"<<endl;
    
    if(!bdebug){
        now=ofGetElapsedTimef();
        if(now-then>CIRCLE_TIME){
            then=now;
            generateNewJumptimes();
            generateNewColors();
        }
        //__windows___________________________
        for(int i=0;i<APPC->windowNum;i++){
            if(bIsjumping){
                if(now-then>jumptime[i]){
                    if(!APPC->windows[i].hasjumped){
                        cout<<"jump"<<i<<endl;
                        APPC->windows[i].setFadeColor(APPC->colorfactory.getSwatchAtIndex(i),generalFadeSpeed);
                        APPC->windows[i].hasjumped=true;
                    }
                }
            }
        }
    }
}

void ScreenSaverController::draw(){
  //  cout<<"ScreenSaverController is drawing"<<endl;
    ofBackground(0, 0, 100);
    
    //__windows___________________________
    for(int i=0;i<APPC->windowNum;i++){
        APPC->windows[i].draw();
    }
    
   
    //__User______________________________
    
    if (APPC->drawInterfaceDebug){
		APPC->inter.debugDraw();
    }

    
}


void ScreenSaverController::generateNewJumptimes(){
    float time =ofRandom(CIRCLE_TIME);
    for(int i=0;i<16;i++){
        time =ofRandom(CIRCLE_TIME);
        cout <<"jumptime"<<time<<endl;
        jumptime[i]=time;
        APPC->windows[i].hasjumped=false;
    }

}


void ScreenSaverController::generateNewColors(){
    ofColor c = ofColor::fromHsb( 0, 255, 255 ); // bright red
    float hue;
    hue=ofRandom(0,255);
    c.setHue(hue);

    //c.setSaturation(ofClamp(ofRandom(0,10)+factorySaturationRange,50,255));
    c.setSaturation(ofClamp(ofRandom(0,factorySaturationBase)+factorySaturationRange,50,255));
    //c.setBrightness(ofClamp(ofRandom(0,150)+factoryBrightnessRange, 100,255));
    c.setBrightness(ofClamp(ofRandom(0,factoryBrightnessBase)+factoryBrightnessRange, 100,255));    
    cout<<"setHue"<<c.getHue()<<"factoryHueRange"<<factoryHueRange<<" factorySaturationRange "<<factorySaturationRange<<endl;
    baseColor=c;
        
    APPC->colorfactory.generateColorSwatchesFromColor(APPC->windowNum,factoryHueRange,baseColor);
    
    //__windows___________________________
    if(!bIsjumping){
        for(int i=0;i<APPC->windowNum;i++){
            //APPC->windows[i].setFadeColor(APPC->colorfactory.getSwatchAtIndex(i),ofRandom(0,CIRCLE_TIME));
            APPC->windows[i].setFadeColor(APPC->colorfactory.getSwatchAtIndex(i),generalFadeSpeed);
        }
    }
}

void ScreenSaverController::generateNewColorsFromColor(ofColor _col){
    ofColor c =_col;
      
    APPC->colorfactory.generateColorSwatchesFromColor(APPC->windowNum,5,c);
   }


void ScreenSaverController::turnOn(){
    then=ofGetElapsedTimef();
    cout<<"screenSaver on"<<bAddedListeners<<endl;
    generateNewColors();

    if(!bAddedListeners){
        addListeners();
        bAddedListeners=true;
 }
}


void ScreenSaverController::turnOff(){
    //__windows___________________________
    for(int i=0;i<APPC->windowNum;i++){
        
        ofColor col= APPC->windows[i].getColor(); 
        APPC->windows[i].stopFadeing();
        APPC->windows[i].setColor(col);
        

    }
 if(bAddedListeners){
    removeListeners();
     bAddedListeners=false;
 }
}

void ScreenSaverController::exit(){
    cout<<"exit ScreenSaverController"<<endl;
}







