//
//  Window.h
//  emptyExample
//
//  Created by Michael Flueckiger on 29.07.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_Window_h
#define ColorWindows_Window_h


#define NORMAL_LERP 0.2//war 0.2 
#define FAST_LERP 0.8
#define SLOW_LERP 0.03

#include "ofMain.h"
#include "global.h"

class Window {
public:
    Window();
    virtual ~Window();
    void draw();
    void update();

    void setPosition(ofVec2f);
    
    int getWidth();
    int getHeight();
    
    void setWidth(int _w);
    void setHeight(int _h);
    void setSize(int _w,int _h);
    
    
    void setId(int _id);
    
    void setColor(ofColor _col);
    ofColor getSetColor();
    
    void setWaveColor(ofColor _col);
    bool iswavecolor;
    void setIsWave(bool _iswave);
    bool isWave();

    
    void setInfrontColor(ofColor _col);
    bool isinfrontcolor;
    bool bisinfronthalfcolor;
    void setIsInfront(bool _isinfront);
    bool isInfront();

    void setIsHalfInfront(bool _isinfronthalf);

    bool isInfrontHalf();
    ofColor myIsInfrontColor;
    ofColor myIsInfrontHalfColor; //-> Vor/ nach dem infrontfenster
    
    
    
    void startInfrontTimer();
    void stopInfrontTimer();

    void infrontTimer();
    bool bIsinfronttimer;
    float isinfrontstarttime;
    float infrontduration;
    
    bool isfadeing;
    void startFadeing();
    void setFadeColor(ofColor _col, float _fadetime, bool _changecolor=true, bool _reaching=false, bool _goback=false);
    ofColor fadeTo();
    void stopFadeing();
    bool isFadeing();
    float fadetime;
    bool isreaching;
    bool reached;
    bool goback;

    
    void setFadeSpeed(float speed);
    void reset();
    void setRunThroughColor(ofColor _col);
    
    
    bool hasUpdatedColor();
    void hasReadUpdateBuffer();
    
    bool hasReachedTargetColor();
    
    ofColor getColor();

    
    bool islerping;
    void startLerping();
    ofColor lerpTo();
    void stopLerping();
    bool isLerping();
    float lerpspeed;
    
    
    void setLerpColor(ofColor _targetColor, float _lerpspeed=0.01);
    ofColor getLerpColor();
    
    void setLerpSpeed(float _lerpspeed);
    float getLerpSpeed();
    
    void setGeneralLerpSpeed(float _speed);
    
        
    
    bool isblinking;
    bool blinkingishigh;
    void startBlinking();
    ofColor blinking();
    void stopBlinking();
    bool isBlinking();
    float blinkfrequency;
    
    
    bool isfeedbacking;
    bool feedbackingishigh;
    void startFeedbacking();
    ofColor feedbacking();
    void stopFeedbacking();
    bool isFeedbacking();
    float feedbackfrequenzy;
    int feedbackcounter;
    
    int myId;
    // myTestObject obj;
    
    
    bool hasjumped;
    
    
private:
    
    float wavespeed;
    float fadespeed;
    
    float generallerpspeed;
    
    ofVec2f position;
    int width;
    int height;
    int r,g,b;
    float hue;
    
    ofColor color;
    
    //color at the moment
    ofColor actualColor;
    ofColor myColor;
    
    //color of old frame
    ofColor myColorBefore;
    
    //color to get in actual frame
    ofColor myColorToBecome;

    
    //sort of Original Color;
    ofColor mySetColor;
    
    //Wave
    ofColor myWaveColor;
    
    
    ofColor myTargetColor;
    
    ofColor myOldColor;
    ofColor myOriginalColor;
    
    ofColor myBlinkColor;
    ofColor myFeedbackColor;
    int maxfeedback;
    
    bool colorUpdated;
    float fadeSpeed;
    float lerpfact;
    bool reachedTargetColor;
    bool runthrough;
    
    float time;
    float then;
    float now;
    
    
};

#endif
