//
//  Window.cpp
//  emptyExample
//
//  Created by Michael Flueckiger on 29.07.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "Window.h"
#include "ApplicationController.h"

#define		IDLE_COLOR		0xFFFFFF
#define		OVER_COLOR		0x00FF00
#define		DOWN_COLOR		0xFF0000



Window::Window(){
    colorUpdated=false;
    
    generallerpspeed=0.1;
    
    fadeSpeed=0.5;
    isfadeing=false;
    islerping=false;
    isfadeing=false;
    
    isreaching=false;
    reached=false;
    goback=false;
   
    myColor.set(255,100,0);
    myColorBefore.set(myColor);
    mySetColor.set(myColor);
    actualColor=myColor;
    
    iswavecolor=false;
    
    runthrough=false;
   
    isblinking=false;
    myBlinkColor=ofColor(0,0,0);
    blinkfrequency=0.1;
    blinkingishigh=false;
    
    isfeedbacking=false;
    feedbackingishigh=false;
    maxfeedback=10;
    feedbackfrequenzy=0.05;
    myFeedbackColor=ofColor(255,255,255);
    
    then=ofGetElapsedTimef();
    
    hasjumped=false;
    
    infrontduration=5;
    
}

Window::~Window(){
}




void Window::update(){
      
    ofColor tempc;

    tempc=myColor;
    
    if(myId==0){
        //cout<<isreaching<<endl;
    }
    
    if(isreaching){
        tempc=fadeTo();
    }else if(isblinking){
        setGeneralLerpSpeed(FAST_LERP);
        tempc=blinking();
    }else if(isfeedbacking){
        setGeneralLerpSpeed(FAST_LERP);
        tempc=feedbacking();
    }else if(islerping){
        tempc=lerpTo();
    }else if(iswavecolor){
        tempc=myWaveColor;
    }else if(isfadeing){
        tempc=fadeTo();
    }
    
    if(bIsinfronttimer){
      //  cout<<"Window "<<myId<<"isinfront"<<isinfrontcolor<<"receive"<<isinfront<<endl;

    infrontTimer();
    }
    
    ofColor lerp=myColorBefore;
    lerp.lerp(tempc,generallerpspeed);
    
    ofColor dif;
    dif.set(myColorBefore-lerp);
    if(dif==ofColor(0,0,0)){
        iswavecolor=false;
    }
       
    if(lerp==myWaveColor)setIsWave(false);
    
    actualColor=lerp;
    if(myColorBefore!=actualColor){
        colorUpdated=true;
    }
    myColorBefore=actualColor;

}


void Window::draw(){
       
    ofSetColor(actualColor);
    ofRect(position.x, position.y, width, height);
    
	ofSetColor(255, 0, 0);
    stringstream msg;
    msg
    << "my Id " << myId<<endl;
    ofDrawBitmapString(msg.str(), position.x, position.y+height+10);


}


void Window::setId(int _id){
    myId=_id;
}



void Window::setPosition(ofVec2f _pos){
    position=_pos;
}


void Window::setColor (ofColor _col){
    
    myColor=_col;
    mySetColor=myColor;
    setGeneralLerpSpeed(normallerp);
    
}




ofColor Window::getColor(){
    return actualColor;
}

//Get the "original" setted color
ofColor Window::getSetColor(){
    return mySetColor;
}



void Window::setGeneralLerpSpeed(float _speed){
    generallerpspeed=_speed;
}




void Window::setRunThroughColor(ofColor _col){
    myTargetColor=_col;
    myOldColor=myColor;
    //  cout<<"set Fade to"<<myTargetColor<<endl;
    lerpfact=0.1;
    reachedTargetColor=false;
    colorUpdated=true;
    runthrough=true;
}

void Window::setFadeSpeed(float _speed){
    fadeSpeed=_speed;
    
}


void Window::setLerpSpeed(float _lerpspeed){
    lerpspeed=_lerpspeed;
}

float Window::getLerpSpeed(){
    return lerpspeed;
}


void Window::setFadeColor(ofColor _col, float _fadetime, bool _changecolor, bool _reaching, bool _goback){
    if(!isreaching){
    bool changecolor=_changecolor;
    isreaching=_reaching;
    goback=_goback;    
    
    if(isreaching)reached=false;
    myTargetColor=_col;
    
    if(changecolor){
        mySetColor=myTargetColor;
    }
    fadetime=_fadetime;
    startFadeing();
    }else return;
}

bool Window::isFadeing(){
    return isfadeing;
}

void Window::startFadeing(){
    isfadeing=true; 
    then=ofGetElapsedTimef();

}

void Window::stopFadeing(){
    isfadeing=false;
    isreaching=false;
    
    if(goback && !isinfrontcolor){
        setFadeColor(mySetColor,fadetime);
    }
    
}

ofColor Window::fadeTo(){
    
    ofColor fade=myColor;
    ofColor targetCol=myTargetColor;
    float fadefact;
    
    now=ofGetElapsedTimef();
    float temp=now-then;
    
    if(temp>fadetime){
        fade=myTargetColor;
        myColor=fade;
        stopFadeing(); 
    }else{
    fadefact=temp/fadetime;
    fade.lerp(targetCol,fadefact);
    }
    return fade;
}


void Window::setLerpColor(ofColor _lerpcol,float _lerpspeed){
    myTargetColor=_lerpcol;
    mySetColor=myTargetColor;
    startLerping();
    lerpspeed=_lerpspeed;
}



void Window::startLerping(){
    islerping=true;
    lerpfact=0;

}

void Window::stopLerping(){
    islerping=false;
}


ofColor Window::lerpTo(){
    
    ofColor lerp=myColor;
    ofColor targetCol=myTargetColor;
    lerp.lerp(targetCol,lerpfact);
    lerpfact+=lerpspeed;
    if(lerpfact>1){
        lerp=mySetColor;
        stopLerping();        
    }  
    if(myId==0){
        cout<<" myCol "<<myColor<<" lerp "<<lerp<<endl;
    
    }
    return lerp;
}


void Window::setWaveColor(ofColor _col){
    myWaveColor=_col;
}

void Window::setIsWave(bool _iswave){
    iswavecolor=_iswave;
  //  if(iswavecolor)setGeneralLerpSpeed(normallerp);
    if(iswavecolor)setGeneralLerpSpeed(wavelerp);

}

bool Window::isWave(){
    return iswavecolor;
}

void Window::setInfrontColor(ofColor _col){
    myIsInfrontColor=_col;
}

void Window::setIsInfront(bool _isinfront){
    cout<<"Window "<<myId<<"isinfront"<<isinfrontcolor<<"receive"<<_isinfront<<endl;
    if(isinfrontcolor && _isinfront)return;
    
    isinfrontcolor=_isinfront;
    
    if(isinfrontcolor){
            ofColor infrontcolor;
           // infrontcolor.set(255,0,0);
           infrontcolor=mySetColor;
           int h= infrontcolor.getHue();
            h+=127;
            if(h>255)h=h-255;
            infrontcolor.setHue(h);
            infrontcolor.setBrightness(255);
            infrontcolor.setSaturation(255);
            setFadeColor(infrontcolor, globalIsInFrontFadeSpeed,false,true,true);
        }else{
            startInfrontTimer();

            //setFadeColor(mySetColor, globalIsInFrontFadeSpeed);
        }
}


void Window::setIsHalfInfront(bool _isinfronthalf){
    if(bisinfronthalfcolor && _isinfronthalf)return;
    
    bisinfronthalfcolor=_isinfronthalf;
    
    if(bisinfronthalfcolor){
        ofColor infrontcolor;
        // infrontcolor.set(255,0,0);
        infrontcolor=mySetColor;
        int h=infrontcolor.getHue();
        int s=infrontcolor.getSaturation();
        int b=infrontcolor.getBrightness();
        s-=150;
        if(s<0)s=0;
        b+=150;
        if(b>255)b=255;
        infrontcolor.setBrightness(b);
        infrontcolor.setSaturation(s);
        setFadeColor(infrontcolor, globalIsInFrontFadeSpeed/2,false,true,true);
    }else{
        startInfrontTimer();
        
        //setFadeColor(mySetColor, globalIsInFrontFadeSpeed);
    }
}



bool Window::isInfront(){
    return isinfrontcolor;
}



void Window::startInfrontTimer(){
    isinfrontstarttime=ofGetElapsedTimef();
    bIsinfronttimer=true;
}


void Window::infrontTimer(){
    float now=ofGetElapsedTimef();
    if(now-isinfrontstarttime>infrontduration){
        setFadeColor(mySetColor, globalIsInFrontFadeSpeed);
        stopInfrontTimer();
    }
}

void Window::stopInfrontTimer(){
    bIsinfronttimer=false;
}


void Window::reset(){
    stopFadeing();
    stopBlinking();
    stopFeedbacking();
    

}


void Window::startBlinking(){
    isblinking=true;
    then=ofGetElapsedTimef();
   setGeneralLerpSpeed(FAST_LERP);
};

ofColor Window::blinking(){
    myBlinkColor=myColor;
    int b=myBlinkColor.getBrightness();
    myBlinkColor.setBrightness(b/2);
    
    ofColor blink;
    if(blinkingishigh){
        blink=myColor;
    }else{
        blink=myBlinkColor;
    }
    
    now=ofGetElapsedTimef();
    if(now-then>blinkfrequency){
        blinkingishigh=!blinkingishigh;
        then=now;
    }
    return blink;
}

void Window::stopBlinking(){
    isblinking=false;
    setGeneralLerpSpeed(normallerp);

};

bool Window::isBlinking(){
    return isblinking;
}

void Window::startFeedbacking(){
    isfeedbacking=true;
    then=ofGetElapsedTimef();
    feedbackcounter=0;
}

ofColor Window::feedbacking(){
    ofColor feedback;
    
    if(feedbackingishigh){
        feedback=myColor;
    }else{
        feedback=myFeedbackColor;
    }
    
    now=ofGetElapsedTimef();
    
    if(now-then>feedbackfrequenzy){
        feedbackingishigh=!feedbackingishigh;
        then=now;
        feedbackcounter++;
    }
    
    if (feedbackcounter>maxfeedback){
        stopFeedbacking();
    }
    return feedback;
}

void Window::stopFeedbacking(){
    isfeedbacking=false;
}

bool Window::isFeedbacking(){
    return isfeedbacking;
}


bool Window::hasUpdatedColor(){
    return colorUpdated;
}

void Window::hasReadUpdateBuffer(){
    colorUpdated=false;
}

bool Window::hasReachedTargetColor(){
    return reachedTargetColor;
}



void Window::setSize(int _w, int _h){
    width=_w;
    height=_h;
    
    
}