//
//  global.h
//  ColorWindows_2
//
//  Created by Michael Flueckiger on 27.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_global_h
#define ColorWindows_global_h

#include "ofMain.h"


struct lineStruct {
    vector<ofVec2f> myline;
    float speed;
};


extern float globalIsInFrontFadeSpeed;
extern float globalWaveDumping;
extern float maxwavespeed;
extern float maxwavespeedscale;


extern float factoryHueRange;
extern float factorySaturationRange;
extern float factorySaturationBase;
extern float factoryBrightnessRange;
extern float factoryBrightnessBase;

extern float generalFadeSpeed;
//extern float generalLerpSpeed;

extern bool bdebug;
extern bool arduinodebug;

extern float normallerp;
extern float wavelerp;

extern float fadeAllBrightness;
extern float fadeAllSaturation;

extern ofColor baseColor;


extern bool bIsjumping;


extern float colorshift;


extern float maestroFadeSpeed;



#endif
