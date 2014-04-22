//
//  ColorWave.h
//  emptyExample
//
//  Created by Michael Flueckiger on 06.08.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_ColorWave_h
#define ColorWindows_ColorWave_h



#include "ofMain.h"

class ColorWave {
public:
    ColorWave();
    virtual ~ColorWave();
    void draw();
    void update();
    
    void setMaxWindows(int _max);
    int getMaxWindows();
    int maxWindows;
    
    void setPosition(ofVec2f);
    
    void setWindowPosition(int pos);

    
    ofVec2f getPosition();
    int getWindowPosition();
    
    
    void setSpeed(float _speed);
    float getSpeed();
    
    void setColor(ofColor _col);
    ofColor getColor();
    int myId;
    
    
 

    
private:
    ofColor myColor;
    ofVec2f position;
    int windowPosition;
    float speed;
    float floatpos;
    float dumping;
 };
#endif
