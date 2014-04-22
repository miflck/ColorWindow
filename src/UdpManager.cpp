//
//  UdpManager.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 24.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "UdpManger.h"

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



UdpManager::UdpManager(){
    init();
}


UdpManager::~UdpManager(){
    
}


//------------------------------------------------------


void UdpManager::init(){
     
    
    int c=0;
    for(int i=NUM_WINDOWS;i>=0;i--){
        //create the socket and set to send to 127.0.0.1:11999
        
        udpConnection[c].Create();
        string ipstring="192.168.1.";
      //  string ipstring="0.0.0.";

        ipstring+=ofToString(i);
        
        
         char* valChar = ( char*) ipstring.c_str(); // cast from string to unsigned char*
        udpConnection[c].Connect(valChar,8888);

        
        cout<<valChar<<endl;
        udpConnection[c].SetNonBlocking(true);
        c++;
        
    }
    cout<<"c"<<c<<endl;
    udpConnection[c].Create();
   // string ipstring="192.168.1.152";
    string ipstring="192.168.1.152";

    
    char* valChar = ( char*) ipstring.c_str(); // cast from string to unsigned char*
    
    
    udpConnection[c].Connect(valChar,8888);
    cout<<valChar<<endl;
    udpConnection[c].SetNonBlocking(true);
    
    //udpConnection[14].Connect("192.168.1.22",8888);

    
    //create the socket and set to send to 127.0.0.1:11999
    udpConnection[14].Connect("10.0.1.20",8888);
   udpConnection[0].Connect("0.0.0.0",8888);

    udpConnection[c].Connect("10.0.1.5",8888);

    
}


void UdpManager::update(){
    // cout<<"SerialManager is updating"<<endl;
    //__color buffer______________________
    // updateColorBuffer();
    
    for(int i=0;i<NUM_WINDOWS;i++){
       // APPC->setIsInFront(i,false);
        char udpMessage[100000];
        udpConnection[i].Receive(udpMessage,100000);
        string message=udpMessage;
        if(message!=""){
            // bool b=toBool(message);
            cout<<"message: "<< message<< " from window "<<i<<endl;

            if(message=="1"){
                APPC->setIsInFront(i,true);
                                
                
                cout<<"message: "<< message<< " from window "<<i<<endl;
               // APPC->windows[i].setIsInfront(true);
                if(i==16) APPC->windows[1].setIsInfront(true);


            }
            if(message=="0"){
                APPC->setIsInFront(i,false);
                if(i==17)APPC->setIsInFront(1,false);

            }
            
            if(message=="2"){
                APPC->setIsInFront(i,false);
                if(i==17)APPC->setIsInFront(1,false);
                
            }
            
            
        }
    }
    
    
    
    
    //updateUdpSendData();


}


bool UdpManager::toBool(std::string const& s) {
    return s != "0";
}


void UdpManager::draw(){
    //  cout<<"SerialManager is Drawing"<<endl;
}


void UdpManager::exit(){
    // cout<<"exit SerialManager"<<endl;
}




//EVENTS
//------------------------------------------------------

void UdpManager::addListeners() {
    if(!bAddedListeners){
        ofAddListener(ofEvents().update, this, &UdpManager::_update);
        ofAddListener(ofEvents().draw, this, &UdpManager::_draw);
        ofAddListener(ofEvents().exit, this, &UdpManager::_exit);
        
    }
    bAddedListeners = true;
}


void UdpManager::removeListeners() {
	ofRemoveListener(ofEvents().update,this,&UdpManager::_update);
    ofRemoveListener(ofEvents().draw,this,&UdpManager::_draw);
    ofRemoveListener(ofEvents().exit,this,&UdpManager::_exit);
    
    bAddedListeners = false;
}


//EVENT HANDLER
//------------------------------------------------------

void UdpManager :: _update( ofEventArgs &e )
{
	update();
}

void UdpManager :: _draw( ofEventArgs &e )
{
	draw();
}


void UdpManager :: _exit( ofEventArgs &e )
{
	exit();
}



void UdpManager::sendToId(int _id, ofColor _col, float _speed, int _mode, int _trigger,int _garbage){

    int sendId=_id;
    
    
    string r,g,b,speed,mode,trigger;
    
    //int br=_col.getBrightness();
   // _col.setBrightness(br/2);
    
    int temp;
    temp=_col.r;
    if (temp==44) temp=45;   
    r=ofToString(floor(ofMap(temp, 0, 255, 0, 127)));
    temp=_col.g;
    if (temp==44) temp=45;   
    g=ofToString(floor(ofMap(temp, 0, 255, 0, 127)));
    temp=_col.b;
    if (temp==44) temp=45;   
    b=ofToString(floor(ofMap(temp, 0, 255, 0, 127)));
    if(_id==0){
    }
    temp=_speed;
    if (temp==44) temp=45;   
    
    speed =ofToString(temp);
    mode=ofToString(_mode);
    trigger=ofToString(_trigger);
    string message="";
    message+=r+","+g+","+b+","+speed+","+mode+","+trigger;
   message+=ofToString(0)+r+","+g+","+b+","+speed+","+mode+","+trigger+","+ofToString(_garbage);
    
    
    if(sendId==1){
    int sent = udpConnection[sendId].Send(message.c_str(),message.length());
    sent = udpConnection[NUM_WINDOWS+1].Send(message.c_str(),message.length());
    }
    else{
        int sent = udpConnection[sendId].Send(message.c_str(),message.length());}
   // cout<<message<<"was sent to "<<sendId<<endl;

}

//--------------------------------------------------------------

void UdpManager::setAllTriggervalues(int _t){
    for(int i=0;i<NUM_WINDOWS;i++){
        //create the socket and set to send to 127.0.0.1:11999
        
        ofColor sendCol= APPC->windows[i].getColor();
        sendToId(i,sendCol,_t,SET_TRIGGERVALUE,_t);
             
    }

}

//--------------------------------------------------------------


void UdpManager::setTriggervaluesAtId(int _id, int _t){
        ofColor sendCol= APPC->windows[_id].getColor();
        sendToId(_id,sendCol,_t,SET_TRIGGERVALUE,_t,0);
}




void UdpManager::setDebug(bool _d){
    cout<<_d<<endl;
    for(int i=0;i<NUM_WINDOWS;i++){        
        ofColor sendCol= APPC->windows[i].getColor();
        sendToId(i,sendCol,_d,SET_DEBUG,_d,0);
    }

    
}


//--------------------------------------------------------------

void UdpManager::updateUdpSendData(){
    
    for(int i=0;i<NUM_WINDOWS;i++){
        
        if(APPC->windows[i].hasUpdatedColor()){
            if(ofGetFrameNum()%1==0){
            ofColor sendCol= APPC->windows[i].getColor();
            sendToId(i,sendCol,0,SET_COLOR);
            APPC->windows[i].hasReadUpdateBuffer();
            }

           
        }
    }
}



//--------------------------------------------------------------

void UdpManager::updateColorBuffer(){
    
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

void UdpManager::turnOn(){
    if(!bAddedListeners){
        addListeners();
    }
}


void UdpManager::turnOff(){
    if(bAddedListeners){
        removeListeners();
    }
}


bool UdpManager::isRunning(){
    return bAddedListeners;
}


void UdpManager::reset(){
    //reset App
}

void UdpManager::setWindowNum(int _num){
    windowNum=_num;
}

