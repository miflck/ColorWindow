//
//  TestClassController.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "TestClassController.h"
#include "ApplicationController.h"


TestClassController::TestClassController(){
    init();
}


TestClassController::~TestClassController(){
    
}


//------------------------------------------------------
void TestClassController::init(){
    if(APPC->bUseKinect){
 /*       ofAddListener(APPC->kinect_manager->gestGen.gestureRecognized,this,&TestClassController::gestureRecognized);   
  */
        ofAddListener(APPC->inter.completedMove,this,&TestClassController::completedMove);
        ofAddListener(APPC->inter.gestureInit,this,&TestClassController::gestureInit);
        ofAddListener(APPC->inter.notGestureInit,this,&TestClassController::notGestureInit);

    }
    
    //__ color _______________________
    colorpos=0;
    mixspeed=20;
    
    
    
    cout<<"init TestClassController"<<endl;
    bAddedListeners = false;
  
    
    //__ofxOneDollar______________________________
    
    num_created_gestures = 0;
    createNewGesture();
    mode = 0;
    dollar.load(ofToDataPath("gestures.txt",true));    
    
    for(int i=0;i<8;i++){
        lineStruct l;
        l.myline.push_back(ofVec2f(0,0));
        lines.push_back(l);
    }
    for(int i=0;i<8;i++){
        lines[i].myline.clear();
    }
    
    
}


void TestClassController::update(){
    
    //__wave___________________________
        
    for(int i=0;i<wave.size();i++){
        cout<<"wave size"<<wave.size()<<endl;
        wave[i].update();    
        cout<<wave[i].getColor()<<endl;
        int wpos=wave[i].getWindowPosition();
        cout<<"wave pos"<<wpos<<endl;
        float speed=wave[i].getSpeed();
        cout<<"wave speed"<<wave[i].getSpeed()<<" pos "<<wpos<<endl;
        
        if(speed!=0){
            APPC->windows[wpos].setIsWave(true);                
            APPC->windows[wpos].setWaveColor(wave[i].getColor());

            //Set all Colors Back
           /* for(int k=0;k<APPC->windowNum;k++){
                if(k==wpos){
                APPC->windows[k].setIsWave(true);                
                }
                else{APPC->windows[k].setIsWave(false);
                }
            }*/
            
           // APPC->windows[wpos].setRunThroughColor(wave[i].getColor());
            //APPC->windows[wpos].setLerpSpeed(1);
            
            //APPC->windows[wpos].setLerpThereAndBackColor(wave[i].getColor());

        }else{
            APPC->windows[wpos].setColor(wave[i].getColor());
            wave.erase(wave.begin()+i);
        }
    }

    
    //__One Dollar________________________

    updateHandpos();
  
    
    for(int i=0;i<MAX_USERS;i++){
        // find the gesture which matches the current line.
        ofxUser  u=APPC->inter.users[i];
        if (u.bones) {
            ofxGesture* tmp = new ofxGesture();
            if(lines[i].myline.size()>0){
                for(int k = 0; k < lines[i].myline.size(); ++k) {
                    tmp->addPoint(lines[i].myline[k].x, lines[i].myline[k].y);
                }
                double score = 0.0;
                ofxGesture* match = dollar.match(tmp, &score);
                string result = "Matching score: " +ofToString(score);
                if(match != NULL && score >MATCH_SCORE) {
                    result +=", which matches with gesture: " +match->name;
                    lines[i].myline.clear();
                    
                    if(match->name=="forwards"){
                        //Event draus machen! 
                        mixspeed=lines[i].speed;
                        colorpos+=mixspeed;
                    }
                    else {
                        //Event draus machen! 
                        mixspeed=lines[i].speed;
                        colorpos-=mixspeed;
                    }
                  
                    ofBackground(255,0,0);    
                    cout<<"---------------- Mischen!----------------";
                    cout<<"score "<<score<<" name "<<match->name<<endl;
                    cout<<"pos"<<colorpos<<" speed "<<mixspeed<<endl;

                }
            }
        }
    }
    
    
    
    //muss nicht mehr mit dem fenster zu tun haben!
    
    if (colorpos>255) {
        colorpos=0;
    }if (colorpos<0) {
        colorpos=255;
    }
    
    float hue=colorpos;//ofMap(colorpos, 0, ofGetWidth(), 0, 255);
    colorposColor.setHsb(hue, 255, 255);    
    APPC->windows[0].setColor(colorposColor);

}
//--------------------------------------------------------------------

void TestClassController::draw(){
    //APPC->showWindows=false;

   // cout<<"TestClassController is drawing"<<endl;
   ofBackground(0, 0, 0);
  
    /* 
    ofSetColor(colorposColor);
    ofFill();
    ofRect(0, 0, ofGetWidth(), ofGetHeight()-50);
    ofSetColor(255,255,255);
    ofRect(650,0,20,20);
*/
    
    
/*
    
    if(mode == 0) {	
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i < lines.size(); ++i) {
            if(lines[i].myline.size()>0){
                for(int k = 0; k < lines[i].myline.size(); ++i) {
                    glVertex2fv(lines[i].myline[k].getPtr());
                }
            }
		}
		glEnd();
        ofDrawBitmapString(message, 10, ofGetHeight()-40);
        
	}
 */
        
    //__windows___________________________
    if( APPC->showWindows){
        for(int i=1;i<APPC->windowNum;i++){
            APPC->windows[i].draw();
        }
    }
    APPC->windows[0].draw();    
    //__User______________________________
    
    if (APPC->drawInterfaceDebug){
		APPC->inter.debugDraw();
    }
    
    drawOneDollar();
    
}

//--------------------------------------------------------------------

void TestClassController::exit(){
    cout<<"exit TestClass"<<endl;
}


//--------------------------------------------------------------------


void TestClassController::updateHandpos(){
    
    for(int i=0;i<8;i++){
        if(lines[i].myline.size()>MAX_LINESIZE){
            lines[i].myline.clear();
        }
        
        ofxUser user=APPC->inter.users[i];
        if(user.bones){
            //right hand
            float vel=user.bonesVel.bone[11]->length();
            float x=user.bonesVel.bone[11]->x;
            float y=user.bonesVel.bone[11]->y;
            int g=int(255/8*i);
            ofSetColor(255,g,0);
            ofCircle(x, y, 30);
            
            ofCircle(user.bonesPoints.right_hand.x, user.bonesPoints.right_hand.y, 20);
            lines[i].myline.push_back(ofVec2f(user.bonesPoints.right_hand.x,user.bonesPoints.right_hand.y));
            
            //right hand
            vel=ofMap(vel,0,100,0,80);
            lines[i].speed=vel;
        }
        
        
    }
}



//--------------------------------------------------------------
void TestClassController::drawOneDollar(){
    
    for (int i=0;i<8;i++){
        
        if(mode == 0) {	
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINE_STRIP);
            for(int k = 0; k< lines[i].myline.size(); k++) {
                glVertex2fv(lines[i].myline[k].getPtr());
            }
            glEnd();
            ofDrawBitmapString(message, 10, ofGetHeight()-40);
            
        }
        else if (mode == 1) {
            glColor3f(0.0f, 0.0f, 1.0f);
            ofDrawBitmapString(message, 10, ofGetHeight()-40);
        }
        
        glColor3f(0.0, 1.0, 0.2);
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < found_gesture.size(); ++i) {
            glVertex2fv(found_gesture[i].getPtr());	
        }
        glEnd();
        
        glColor3f(1.0f, 1.0f, 0.0f);
        ofDrawBitmapString("Number of gestures: " +ofToString(dollar.gestures.size()), 10, ofGetHeight()-25);
        ofDrawBitmapString("Name of current gesture: " +oneDollarGest->name, 10, ofGetHeight()-10);
        
    }
}



 void TestClassController::createNewGesture() {
 ++num_created_gestures;
 oneDollarGest = new ofxGesture();
 oneDollarGest->setName("Gesture#" +ofToString(num_created_gestures));
 }








//KINECT LISTENER
//--------------------------------------------------------------------



void TestClassController::gestureInit(ofxUser & user){
	cout << "-INT-" << endl;
    if(!APPC->windows[0].isBlinking()){
        APPC->windows[0].startBlinking();
    }
    
}


void TestClassController::notGestureInit(ofxUser & user){
    if(APPC->windows[0].isBlinking()){
        APPC->windows[0].stopBlinking();
        cout << "-Stop Blinking-" << endl; 

    }
}





void TestClassController::completedMove(ofxUser & user){
	cout << "-------Completed Testclass---------" << endl; 
    
    //right hand
    float vel=user.bonesVel.bone[11]->length();
    cout<<user.bonesVel.bone[11]->length()<<endl;    
    
    //left hand
    float velleft=user.bonesVel.bone[5]->length();
    cout<<user.bonesVel.bone[5]->length()<<endl;    
    
    float s=vel>velleft ? vel : velleft;
    if(s>maxwavespeed)s=maxwavespeed;
    
    s=ofMap(s,0,maxwavespeed,0,maxwavespeedscale);
   // speed=ofToString(floor(ofClamp(ofMap(s, 5, 30, 60, 0),0,30)));    
    cout<<"wavespeed"<<s<<endl;
    wavespeed=s;
    ColorWave w=*new ColorWave();
    w.setSpeed(wavespeed);
    w.setColor(colorposColor);
    wave.push_back(w);
    
    
}




void TestClassController::gestureRecognized(gesture &g){
    //cout<<"Test Class FOUND"<<endl;
    //cout<<"name: "<<g.gesture_name<<endl;
    //cout<<"type: "<<g.gesture_type<<endl;
    
    if(g.gesture_name=="Click"){
        cout<<"--------------------------you clicked------------------- "<<endl;
        wavespeed=ofRandom(0.5);
        ColorWave w=*new ColorWave();
        w.setSpeed(wavespeed);
        w.setColor(ofColor(255,0,0));
        wave.push_back(w);
    }
    
}




//KEY LISTENER
//--------------------------------------------------------------
void TestClassController::keyPressed(ofKeyEventArgs &e){
    int key=e.key;
    
    switch (key) {
        case 'c':
            wavespeed=ofRandom(0.5);
            ColorWave w=*new ColorWave();
            //            w.setSpeed(0.03);
            w.setSpeed(wavespeed);
            w.setColor(ofColor((int)ofRandom(255),(int)ofRandom(255),(int)ofRandom(255)));
            wave.push_back(w);
            break;

    }
}



void TestClassController::turnOn(){
    if(!bAddedListeners){
        addListeners();
        colorposColor=APPC->windows[0].getColor();
        colorpos=colorposColor.getHue();
    }
    bAddedListeners=true;
}

void TestClassController::turnOff(){
    if(bAddedListeners){
        removeListeners();
    }
    bAddedListeners=false;
}




/*

 //EVENTS
 //------------------------------------------------------
 
 void TestClassController::addListeners() {
 ofAddListener(ofEvents().update, this, &TestClassController::_update);
 // ofAddListener(ofEvents().exit, this, &TestClassController::_exit);
 bAddedListeners = true;
 wavespeed=0.5;
 ColorWave w=*new ColorWave();
 //            w.setSpeed(0.03);
 w.setSpeed(wavespeed);
 w.setColor(ofColor(210,0,200));
 wave.push_back(w);
 }
 
 
 
void TestClassController::removeListeners() {
	ofRemoveListener(ofEvents().update, this, &TestClassController::_update);
    ofRemoveListener(ofEvents().exit, this, &TestClassController::_exit);
    bAddedListeners = false;
}


//EVENT HANDLER
//------------------------------------------------------

void TestClassController :: _update( ofEventArgs &e )
{
	update();
}

void TestClassController :: _draw( ofEventArgs &e )
{
	draw();
}


void TestClassController :: _exit( ofEventArgs &e )
{
	exit();
}



//Event Helper
//------------------------------------------------------

void TestClassController::turnOn(){
    if(!bAddedListeners){
        addListeners();
    }
}


void TestClassController::turnOff(){
    if(bAddedListeners){
        removeListeners();
    }
}


bool TestClassController::isRunning(){
    return bAddedListeners;
}


void TestClassController::reset(){
    //reset App
}
 */

