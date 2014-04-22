//
//  global.cpp
//  ColorWindows_2
//
//  Created by Michael Flueckiger on 27.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "global.h"


float globalIsInFrontFadeSpeed=1;
float globalWaveDumping=0.98;
float maxwavespeed=50;
float maxwavespeedscale=0.3;


 float factoryHueRange=5;
 float factorySaturationRange=100;
float factorySaturationBase=10;

 float factoryBrightnessRange=100;
float factoryBrightnessBase=150;

float generalFadeSpeed=0.2;
bool bdebug=false;


float normallerp=0.2;
float wavelerp=0.1;

bool arduinodebug=false;

float fadeAllBrightness=200;
float fadeAllSaturation=200;

ofColor baseColor;

bool bIsjumping=true;


float  colorshift=0;

float maestroFadeSpeed=0.6;