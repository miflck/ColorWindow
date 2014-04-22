//
//  ColorWave.cpp
//  emptyExample
//
//  Created by Michael Flueckiger on 06.08.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "ColorWave.h"

#include "ApplicationController.h"



ColorWave::ColorWave(){
    windowPosition=0;
    floatpos=0;
    //globalWaveDumping=0.98;
    speed=0;
}




ColorWave::~ColorWave(){
}

void ColorWave::update(){
    speed*=globalWaveDumping;
    cout<<"globalDumping"<<globalWaveDumping<<endl;
    if(abs(speed)<0.01)speed=0;
    floatpos+=speed;
    windowPosition=floor(floatpos);
    if(windowPosition>APPC->windowNum)speed*=-1;
    if(windowPosition<0)speed*=-1;

}


void ColorWave::setMaxWindows(int _max){
    maxWindows=_max;
}

int ColorWave::getMaxWindows(){
    return maxWindows;
}

void ColorWave::draw(){
    ofRect(floatpos, 100, 50, 50);
}

void ColorWave::setSpeed(float _speed){
    speed=_speed;
}

float ColorWave::getSpeed(){
    return speed;
}


void ColorWave::setPosition(ofVec2f _vec){
    position=_vec;

}



ofVec2f ColorWave::getPosition(){
    return position;

}

void ColorWave:: setWindowPosition(int pos){
    floatpos=pos;
}

int ColorWave::getWindowPosition(){
    return windowPosition;
}

void ColorWave::setColor(ofColor _col){
    myColor=_col;
}

ofColor ColorWave::getColor(){
    return myColor;
}