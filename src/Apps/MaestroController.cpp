//
//  TestClassController.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "MaestroController.h"
#include "ApplicationController.h"


MaestroController::MaestroController(){
    init();
}


MaestroController::~MaestroController(){
    
}


//------------------------------------------------------
void MaestroController::init(){
    if(APPC->bUseKinect){
 /*       ofAddListener(APPC->kinect_manager->gestGen.gestureRecognized,this,&TestClassController::gestureRecognized);   
  */
        ofAddListener(APPC->inter.completedMove,this,&MaestroController::completedMove);
        ofAddListener(APPC->inter.gestureInit,this,&MaestroController::gestureInit);
        ofAddListener(APPC->inter.notGestureInit,this,&MaestroController::notGestureInit);

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


void MaestroController::update(){
    
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
                  
                  //  ofBackground(255,0,0);
                    cout<<"---------------- Mischen!----------------";
                    cout<<"score "<<score<<" name "<<match->name<<endl;
                    cout<<"pos"<<colorpos<<" speed "<<mixspeed<<endl;
                   

                    
                   
                    float vel=lines[i].speed;
                    if(vel>maxwavespeed)vel=maxwavespeed;
                    
                    vel=ofMap(vel,0,maxwavespeed,0,maxwavespeedscale);
                    // speed=ofToString(floor(ofClamp(ofMap(s, 5, 30, 60, 0),0,30)));
                    cout<<"wavespeed"<<vel<<endl;
                    ColorWave w=*new ColorWave();
                    int win=0;//ofMap(lines[i].myline.back().x,0,500,0,APPC->windowNum,true);

                    w.setSpeed(vel*10);
                    ofColor c;
                    c.setHsb(ofRandom(0,255), ofRandom(200,255), ofRandom(240,255));
                    w.setColor(c);
                    w.setWindowPosition(win);
                    wave.push_back(w);
                    
                     lines[i].myline.clear();


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
    
    
    for(int i=0;i<MAX_USERS;i++){
      //  for(int i=0;i<2;i++){
        ofxUser  u=APPC->inter.users[i];
        if (u.bones) {
            
            //Get window to manipulate
            int win=ofMap(u.bonesPoints.right_hand.x,100,600,0,APPC->windowNum,true);
            int win2=ofMap(u.bonesPoints.left_hand.x,100,500,0,APPC->windowNum,true);

                float vel=u.bonesVel.bone[11]->length();
              //float x=u.bonesVel.bone[11]->x;
            //float y=u.bonesVel.bone[11]->y;
               //float y=u.bonesPoints.bone[11]->y;
                    
                //float mY=ofMap(y,0,500,0,255,true);
                //h+=u.bonesVel.right_hand.y;
                //h=ofMap(u.bonesPoints.right_hand.y,0,500,0,255,true);
            
           // float hue=ofMap(u.bonesPoints.left_hand.y,u.bonesPoints.left_shoulder.y-200,u.bonesPoints.left_shoulder.y+200,0,255,true);
            
            
            //Set Brightness of all other Windows
            ofColor col;
            float lH=ofMap(u.bonesPoints.left_hand.y,u.bonesPoints.left_shoulder.y-200,u.bonesPoints.left_shoulder.y+200,255,0,true);
            for(int i=0;i<APPC->windowNum;i++){
                col= APPC->windows[i].getColor();
                float s=col.getSaturation();
                if(!u.isIdle)col.setBrightness(lH); // Damits beim weglaufen nicht dunkel bleibt…
                if(!APPC->windows[i].isFadeing())APPC->windows[i].setColor(col);
                //if(!APPC->windows[i].isFadeing())APPC->windows[i].setFadeColor(col,globalIsInFrontFadeSpeed);
            }
            
            
            
            
            //hue deviation-> some sort of autogradient while hands increase distance
            float handdist = u.bonesPoints.left_hand.distance(u.bonesPoints.right_hand);
            float deviation=ofMap(handdist,50,800,0,150,true);
            
            //Get new Hue
            float newHue =ofMap(u.bonesPoints.right_hand.y,u.bonesPoints.right_shoulder.y-200,u.bonesPoints.right_shoulder.y+200,-deviation,255+deviation,true);
            
            newHue+=ofRandom(-vel,vel);
            if(newHue>255)newHue=newHue-255;
            if(newHue<0)newHue=255-newHue;
            
        
            ofVec3f upperArm;
            upperArm.set(u.bonesPoints.right_elbow-u.bonesPoints.right_shoulder);
           
            //upperArm-u.bonesPoints.right_shoulder.x;
            ofVec3f lowerArm;
            lowerArm.set(u.bonesPoints.right_hand);
            lowerArm-=u.bonesPoints.right_elbow;

            
            float armlength=upperArm.length();//+lowerArm.length();

            float neckZ=u.bonesPoints.neck.z;
            float handYZ=u.bonesPoints.left_hand.z;
            float deltaYZ =ofMap(handYZ,neckZ-300,neckZ-100,100,-100,true);
            
            float handZ=u.bonesPoints.right_hand.z;
            float deltaZ =ofMap(handZ,neckZ-600,neckZ-300,0,180,true);
           // cout<<"armlength"<<armlength<<endl;
            
          //  b=255;
            
            //ofColor newCol=generateColorVariantFromColor(50,col);
            //col.setHue(h);
            
   
            
            maestroFadeSpeed=ofMap(u.bonesPoints.left_hand.y,u.bonesPoints.left_shoulder.y-200,u.bonesPoints.left_shoulder.y+200,0,1,true);
            
            
            maestroFadeSpeed=0.1;
            
            float singleFadeSpeed=ofMap(vel,0,100,1,0,true);
            maestroFadeSpeed=singleFadeSpeed;
            //cout<<vel<<" "<<singleFadeSpeed<<endl;

            col.setHsb(newHue+ofRandom(-vel,vel), 255-deltaZ, 255);

           // if(!APPC->windows[win].isWave())APPC->windows[win].setColor(col);
            APPC->windows[win].setColor(col);

         APPC->windows[win].setFadeColor(col,singleFadeSpeed);

            //if(!APPC->windows[win-1].isWave())APPC->windows[win-1].setFadeColor(col, maestroFadeSpeed,true);

          //  if(!APPC->windows[win].isWave())APPC->windows[win].setLerpColor(col);

            //Speedabhängig machen…
            
            
          if(vel>20){
                if(win-1){
                 //   col.setHsb(h-ofRandom(-deviation,deviation), b+ofRandom(-deviation,deviation), 255-ofRandom(deviation));
                    col.setHsb(newHue-ofRandom(-2*vel,2*vel), 255-ofRandom(-2*vel,2*vel), 255-ofRandom(-2*vel,2*vel));
                   // if(!APPC->windows[win-1].isWave())APPC->windows[win-1].setFadeColor(col, maestroFadeSpeed);
                    APPC->windows[win-1].setFadeColor(col, maestroFadeSpeed);

                }
                if(win+1){
                    col.setHsb(newHue-ofRandom(-2*vel,2*vel),255-ofRandom(-2*vel,2*vel), 255-ofRandom(-2*vel,2*vel));
                   // col.setHsb(h-ofRandom(-deviation,deviation), b+ofRandom(-deviation,deviation), 255-ofRandom(deviation));
                    //if(!APPC->windows[win+1].isWave())APPC->windows[win+1].setColor(col);
                    if(!APPC->windows[win+1].isWave())APPC->windows[win+1].setFadeColor(col, maestroFadeSpeed);
              APPC->windows[win+1].setFadeColor(col, maestroFadeSpeed);

                }
                
            }
            
            if(vel>40){
                
                if(win-2){
                    col.setHsb(newHue-ofRandom(-2*vel,2*vel), 255-ofRandom(-3*vel,3*vel), 255);
                    if(!APPC->windows[win-2].isWave())APPC->windows[win-2].setColor(col);
                }
                if(win+2){
                    col.setHsb(newHue-ofRandom(-2*vel,2*vel), 255-ofRandom(-2*vel,2*vel), 255);
                    if(!APPC->windows[win+2].isWave())APPC->windows[win+2].setColor(col);
                }
                
            }
          
            
            
   
            
            
            
  
            }
    
    }
    


}
//--------------------------------------------------------------------

void MaestroController::draw(){
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
    for(int i=0;i<MAX_USERS;i++){
        //  for(int i=0;i<2;i++){
        ofxUser  u=APPC->inter.users[i];
        if (u.bones) {
    
            ofCircle(u.bonesPoints.right_elbow,20);
    
        }
    }
    //__windows___________________________
    if( APPC->showWindows){
        for(int i=0;i<APPC->windowNum;i++){
            APPC->windows[i].draw();
        }
    }
    //APPC->windows[0].draw();
    //__User______________________________
    
    if (APPC->drawInterfaceDebug){
		APPC->inter.debugDraw();
    }
    
    drawOneDollar();
    
}

//--------------------------------------------------------------------

void MaestroController::exit(){
    cout<<"exit TestClass"<<endl;
}


//--------------------------------------------------------------------


void MaestroController::updateHandpos(){
    
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
void MaestroController::drawOneDollar(){
    
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



 void MaestroController::createNewGesture() {
 ++num_created_gestures;
 oneDollarGest = new ofxGesture();
 oneDollarGest->setName("Gesture#" +ofToString(num_created_gestures));
 }








//KINECT LISTENER
//--------------------------------------------------------------------



void MaestroController::gestureInit(ofxUser & user){
	cout << "-INT-" << endl;
    if(!APPC->windows[0].isBlinking()){
        APPC->windows[0].startBlinking();
    }
    
}


void MaestroController::notGestureInit(ofxUser & user){
    if(APPC->windows[0].isBlinking()){
        APPC->windows[0].stopBlinking();
        cout << "-Stop Blinking-" << endl; 

    }
}





void MaestroController::completedMove(ofxUser & user){
	cout << "-------Completed MaestroController---------" << endl; 
    
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




void MaestroController::gestureRecognized(gesture &g){
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



void MaestroController::generateColors(){
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
    //if(!bIsjumping){
        for(int i=0;i<APPC->windowNum;i++){
            //APPC->windows[i].setFadeColor(APPC->colorfactory.getSwatchAtIndex(i),ofRandom(0,CIRCLE_TIME));
            APPC->windows[i].setFadeColor(APPC->colorfactory.getSwatchAtIndex(i),generalFadeSpeed);
        }
    //}
}





ofColor MaestroController::generateColorVariantFromColor(float range, ofColor _col){
    
    //blah
    //cout<<"num"<<num<<endl;
    
    float hue=_col.getHue();
    int sat=_col.getSaturation();
    int brightness=_col.getBrightness();
   
    float deltahue=hue-ofRandom(range);
    
    // cout<<hue<<" "<<deltahue<<endl;
    
    float deltabrightness=100;
    float deltasat;
    
    ofColor col;
    
    
        
        //  deltabrightness=ofRandom(100,255);
        // deltasat=ofRandom(100,255);
        deltabrightness=ofRandom(brightness-range,brightness+range);
        deltasat=ofRandom(sat-range,sat+range);
        deltabrightness=ofClamp(deltabrightness, 0, 255);
        deltasat=ofClamp(deltasat, 0, 255);
        
        if(deltahue<0)deltahue=255+deltahue;
        if(deltahue>255)deltahue=255-deltahue;
        
        
        // if(deltasat<0)deltasat=255+deltasat;
        // if(deltasat>255)deltasat=255-deltasat;
        
        //if(deltabrightness<0)deltabrightness=255+deltabrightness;
        //if(deltabrightness>255)deltabrightness=255-deltabrightness;
        
        col.setHsb(deltahue, deltasat, deltabrightness);
    return col;
        
    
}





//KEY LISTENER
//--------------------------------------------------------------
void MaestroController::keyPressed(ofKeyEventArgs &e){
    int key=e.key;
    
    switch (key) {
        case 'c':
            wavespeed=ofRandom(0.5);
            ColorWave w=*new ColorWave();
            // w.setSpeed(0.03);
            w.setSpeed(wavespeed);
            w.setColor(ofColor((int)ofRandom(255),(int)ofRandom(255),(int)ofRandom(255)));
            wave.push_back(w);
            break;

    }
}



void MaestroController::turnOn(){
    if(!bAddedListeners){
        addListeners();
        colorposColor=APPC->windows[0].getColor();
        colorpos=colorposColor.getHue();
    }
    generateColors();
    bAddedListeners=true;
}

void MaestroController::turnOff(){
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

