#include "testApp.h"
#include "ApplicationController.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    APPC->initialize();

    
	ofSetFrameRate(60 );
	ofSetVerticalSync( true );
    ofBackground(0,0,0);
    
    
    setGUI(); 
    setGUI2();
    setGUI3();
    setGUI4();

    gui->loadSettings("GUI/guiSettings.xml"); 
    gui2->loadSettings("GUI/guiSettings2.xml");    
    gui3->loadSettings("GUI/guiSettings3.xml");    
    gui4->loadSettings("GUI/guiSettings3.xml");    
    
    gui->setDrawBack(true);

    
   }


//--------------------------------------------------------------
void testApp::update(){

    }

//--------------------------------------------------------------
void testApp::draw(){

       


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'q':
            if(APPC->bUseKinect){
        //    APPC->kinect_manager->turnOnKeyListener();
            }
            break;  
            
        case 'Q':
           
            if(APPC->bUseKinect){
      //         APPC->kinect_manager->turnOffKeyListener();
            }
            break;    
        
        case 'd':
            if(APPC->bUseKinect){
        //        APPC->kinect_manager->toggleDebug();
            }
            break;  
            
        case 'i':
            if(APPC->bUseKinect){
                APPC->drawInterfaceDebug=!APPC->drawInterfaceDebug;
            }
            break;  
   
            
        case 'w':
                APPC->showWindows=!APPC->showWindows;
            break;  
            

            
       case '1':
            cout<<"set app"<<endl;
            APPC->setAppById("testClass");
            break;
            
    
        case '2':
            cout<<"set screensaver app"<<endl;
            APPC->setAppById("screenSaver");
            break;
    
            
        case '3':
            cout<<"set maestro app "<<endl;
            APPC->setAppById("maestro");
            break;
            
            
        case '4':
            cout<<"fade all"<<endl;
            APPC->fadeAllWindows();
            break;

            
            
       case 'b':
            //__windows___________________________
            for(int i=0;i<APPC->windowNum;i++){
                APPC->windows[i].startFeedbacking();
            }
            break;
            
        case 'r':
            //__windows___________________________
            for(int i=0;i<APPC->windowNum;i++){
                APPC->windows[i].setFadeColor(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)), 1,false,true,true);
            }
            break;
            
            
        case 'p':
            gui->setDrawWidgetPadding(true);
            break;
        case 'P':
            gui->setDrawWidgetPadding(false);
            break;
            
    
        case 'h':
            gui->toggleVisible(); 
            gui2->toggleVisible(); 
            gui3->toggleVisible(); 
            gui4->toggleVisible(); 

			break;
            
        case 's':
            
            gui->saveSettings("GUI/guiSettings.xml");
            gui2->saveSettings("GUI/guiSettings2.xml");
            gui3->saveSettings("GUI/guiSettings3.xml");
            gui4->saveSettings("GUI/guiSettings4.xml"); 

			break;     
       
            
            
        case 357: // up key
            APPC->inter.openni.hardware.setTiltAngle(APPC->inter.openni.hardware.tilt_angle++);
            break;
        case 359: // down key
            APPC->inter.openni.hardware.setTiltAngle(APPC->inter.openni.hardware.tilt_angle--);
            break;
    
            
            
            
            
        case 't':
            for(int i = 0; i < triggersliders.size(); i++)
            {
                int val=60;
                ofxUISlider *s = (ofxUISlider *) triggersliders[i];
                s->setValue(val);
                APPC->udp_manager->setTriggervaluesAtId(i,val);

            }
            break;
      
            
        case 'T':
            for(int i = 0; i < triggersliders.size(); i++)
            {
                int val=200;
                ofxUISlider *s = (ofxUISlider *) triggersliders[i];
                s->setValue(val);
                APPC->udp_manager->setTriggervaluesAtId(i,val);            } 
            break;
       
        case 'v':
            for(int i = 0; i < triggersliders.size(); i++)
            {
                ofxUISlider *s = (ofxUISlider *) triggersliders[i];
                float val=s->getScaledValue();
                APPC->udp_manager->setTriggervaluesAtId(i,val);
                        }
            break;
            
            
            
        case '0':
            //   APPC->udp_manager->setAllTriggervalues(90);
            for(int i = 0; i < colorsliders.size(); i++)
            {
                int value =90;
                ofxUISlider *s = (ofxUISlider *) colorsliders[i];
                s->setValue(value);
                ofColor col;
                col.setHsb(value,0,0);
                APPC->windows[i].setColor(col);
            }
            break;   
    }  

}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    cout << e.widget->getName() << endl; 
    cout << e.widget->getKind() << endl; 

    
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    
    
    vector<string> number = ofSplitString(name, "_");   
    for (int i=0;i<number.size();i++){
    cout<<number[i]<<endl;
    }

    
    if(number[0]=="Window"){
        cout<<"set Window "<<number[1]<<endl;
       ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float val=slider->getScaledValue();
        APPC->udp_manager->setTriggervaluesAtId(ofToInt(number[1]),val);
    }
   
    
    if(number[0]=="Color"){
        cout<<"set color "<<number[1]<<endl;
        int nr=ofToInt(number[1]);
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float val=slider->getScaledValue();
        ofColor col;
        col.setHsb(val,255,255);
        APPC->windows[nr].setColor(col);

    }
	
     if(name == "DEBUG")
	{
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
		bdebug = toggle->getValue();  
	}
 
    
    if(name == "a_debug")
     {
         ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
         arduinodebug = toggle->getValue();  
         APPC->udp_manager->setDebug(arduinodebug);

     
     }
    
    
    if(name == "Infront Fadespeed")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
       float val=slider->getScaledValue();
        globalIsInFrontFadeSpeed=val; 
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    if(name == "jump")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bIsjumping = toggle->getValue();        
    }

    
    if(name == "General Fadespeed")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        generalFadeSpeed=val;
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    
    if(name == "General Lerpspeed")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
       // generalLerpSpeed=val;
        APPC->setGeneralLerpSpeed(val);
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    
    
    
    if(name == "Wave Dumping")
    {
        cout<<"Wavedumping"<<endl;
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float val=slider->getScaledValue();
        globalWaveDumping=val; 
        cout<<slider->getScaledValue()<<endl;
    }    
    

    
    if(name == "Maxwavespeed")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        maxwavespeed=val;
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    if(name == "MaxSpeedScale")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        maxwavespeedscale=val;
        cout<<slider->getScaledValue()<<endl;
    }
    
    if(name == "Wavelerp")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        wavelerp=val;
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    if(name == "Hue Range")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float val=slider->getScaledValue();
        factoryHueRange=val; 
        cout<<slider->getScaledValue()<<endl;
    }    

    if(name == "Saturation Range")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float val=slider->getScaledValue();
        factorySaturationRange=val; 
        cout<<slider->getScaledValue()<<endl;
    }
    
    if(name == "Saturation Base")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        factorySaturationBase=val;
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    if(name == "Brightness Range")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        float val=slider->getScaledValue();
        factoryBrightnessRange=val;
        cout<<slider->getScaledValue()<<endl;
    }    
    
   
    if(name == "Brightness Base")
    {
        
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        factoryBrightnessBase=val;
        cout<<slider->getScaledValue()<<endl;
    }
    
    
    if(name == "Hue")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        fadeAllSaturation=val;
    }
    if(name == "Bright")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        float val=slider->getScaledValue();
        fadeAllBrightness=val;
    }

    
}




//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if (APPC->drawInterfaceDebug) {
		APPC->inter.mouseDragged(x,y,button);
	}

}


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


void testApp::exit(){
    gui->saveSettings("GUI/guiSettings.xml"); 
    gui2->saveSettings("GUI/guiSettings2.xml"); 
    gui3->saveSettings("GUI/guiSettings3.xml"); 
    gui4->saveSettings("GUI/guiSettings4.xml"); 


	delete gui; 
	delete gui2; 
    delete gui3; 
	delete gui4; 
}


void testApp::setGUI(){

    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float dim = 16; 
    float length = 255-xInit; 
    //    length*=.25; 
    
    gui = new ofxUIScrollableCanvas(0, 0, length+xInit, ofGetHeight()); 
    gui->setScrollAreaToScreen();
    gui->setScrollableDirections(false, true);
    
    gui->setFont("GUI/frabk.ttf");                     //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 10);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 12);           
    gui->setFontSize(OFX_UI_FONT_SMALL, 8);            //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
    
    
    gui->addWidgetDown(new ofxUILabel("MISC", OFX_UI_FONT_MEDIUM)); 
    gui->addSpacer(length-xInit, 2);
    
    gui->addWidgetDown(new ofxUILabel("DEBUG", OFX_UI_FONT_MEDIUM)); 
	gui->addToggle( "DEBUG", false, dim, dim);
    
    
    
    
    gui->addSpacer(length-xInit, 2);
    
    gui->addWidgetDown(new ofxUILabel("toggle Arduino Debug", OFX_UI_FONT_MEDIUM)); 
	gui->addToggle("a_debug", false, dim, dim);
    
    gui->addSpacer(length-xInit, 2);

    gui->addWidgetDown(new ofxUILabel("Windows", OFX_UI_FONT_MEDIUM)); 
    gui->addSlider("Infront Fadespeed", 0, 10, 1, length-xInit, dim);
    gui->addSpacer(length-xInit, 2);
    
    gui->addWidgetDown(new ofxUILabel("Wave", OFX_UI_FONT_MEDIUM)); 
    gui->addSlider("Wave Dumping", 0.9, 1, 0.98, length-xInit, dim);
    gui->addSlider("Maxwavespeed", 0, 100, 50, length-xInit, dim);
    gui->addSlider("MaxSpeedScale", 0, 0.5, 0.3, length-xInit, dim);
    gui->addSlider("Wavelerp", 0, 1, 0.3, length-xInit, dim);

    
    gui->addWidgetDown(new ofxUILabel("Fade etc", OFX_UI_FONT_MEDIUM));
    gui->addSpacer(length-xInit, 5);
    gui->addWidgetDown(new ofxUILabel("toggle jump", OFX_UI_FONT_MEDIUM));
	gui->addToggle("jump", true, dim, dim);
    
    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("Windows Fade", OFX_UI_FONT_MEDIUM));
    gui->addSlider("General Fadespeed", 0, 10, 1, length-xInit, dim);

    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("Windows Lerp", OFX_UI_FONT_MEDIUM));
    gui->addSlider("General Lerpspeed", 0, 1, 0.2, length-xInit, dim);
    
    
   // gui->autoSizeToFitWidgets();
   // gui->getRect()->setWidth(ofGetWidth());
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 


}

void testApp::setGUI2()
{	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
    

    
      
    gui2 = new ofxUIScrollableCanvas(length+xInit+2, 0, length+xInit, ofGetHeight());      
    gui2->setScrollAreaToScreen();
    gui2->setScrollableDirections(false, true);
    
    gui2->setFont("GUI/frabk.ttf");                     //This loads a new font and sets the GUI font
    gui2->setFontSize(OFX_UI_FONT_LARGE, 10);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui2->setFontSize(OFX_UI_FONT_MEDIUM, 12);           
    gui2->setFontSize(OFX_UI_FONT_SMALL, 8);            //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI

    

    
	gui2->addWidgetDown(new ofxUILabel("COLOR FACTORY", OFX_UI_FONT_MEDIUM)); 
    gui2->addSpacer(length-xInit, 2);
    gui2->addSlider("Hue Range", 0, 50, 5, length-xInit, dim);
    gui2->addSlider("Saturation Range", 0, 200, 100, length-xInit, dim);
    gui2->addSlider("Saturation Base", 0, 255, 10, length-xInit, dim);

    gui2->addSlider("Brightness Range", 0, 200, 100, length-xInit, dim);
    gui2->addSlider("Brightness Base", 0, 250, 150, length-xInit, dim);

    
    gui2->addSpacer(length-xInit, 2);
    gui2->addWidgetDown(new ofxUILabel("Werfen Dimm", OFX_UI_FONT_MEDIUM));
    gui2->addSpacer(length-xInit, 2);
    gui2->addSlider("Hue", 0, 255, 200, length-xInit, dim);
    gui2->addSlider("Bright", 0, 255, 200, length-xInit, dim);


    
	ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::setGUI3()
{	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
    
    
    
    
    gui3 = new ofxUIScrollableCanvas(length+xInit+2+length+xInit, 0, length+xInit, ofGetHeight());      

    //gui3->setScrollAreaToScreen();
    gui3->setScrollableDirections(false, true);
    
    gui3->setFont("GUI/frabk.ttf");                     //This loads a new font and sets the GUI font
    gui3->setFontSize(OFX_UI_FONT_LARGE, 10);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui3->setFontSize(OFX_UI_FONT_MEDIUM, 12);           
    gui3->setFontSize(OFX_UI_FONT_SMALL, 8);            //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
    
    
    
	gui3->addWidgetDown(new ofxUILabel("SENSOR", OFX_UI_FONT_MEDIUM)); 
    gui3->addSpacer(length-xInit, 2);
    
    for(int i = 0; i < 16; i++)
    {
        gui3->addSlider("Window_"+ofToString(i), 20, 200,90, length-xInit, dim);
        gui3->addSpacer(length-xInit, 2);
    }
    
triggersliders = gui3->getWidgetsOfType(OFX_UI_WIDGET_SLIDER_H);
    cout<<triggersliders.size()<<endl;
    
    for(int i = 0; i < triggersliders.size(); i++)
    {
        ofxUISlider *s = (ofxUISlider *) triggersliders[i];
        s->setIncrement(1);
    }
    gui3->autoSizeToFitWidgets();

    
	ofAddListener(gui3->newGUIEvent,this,&testApp::guiEvent);
}


void testApp::setGUI4()
{	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
    
    
    
    
    gui4 = new ofxUIScrollableCanvas(3*length+3*xInit+2, 0, length+xInit, ofGetHeight());      
    gui4->setScrollableDirections(false, true);
    
    gui4->setFont("GUI/frabk.ttf");                     //This loads a new font and sets the GUI font
    gui4->setFontSize(OFX_UI_FONT_LARGE, 10);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui4->setFontSize(OFX_UI_FONT_MEDIUM, 12);           
    gui4->setFontSize(OFX_UI_FONT_SMALL, 8);            //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
    
    
    
	gui4->addWidgetDown(new ofxUILabel("COLOR", OFX_UI_FONT_MEDIUM)); 
    gui4->addSpacer(length-xInit, 2);
    
    for(int i = 0; i < 16; i++)
    {
        gui4->addSlider("Color_"+ofToString(i), 0, 255,90, length-xInit, dim);
        gui4->addSpacer(length-xInit, 2);
    }
    
    colorsliders = gui4->getWidgetsOfType(OFX_UI_WIDGET_SLIDER_H);
    cout<<colorsliders.size()<<endl;
    
    for(int i = 0; i < triggersliders.size(); i++)
    {
        ofxUISlider *s = (ofxUISlider *) triggersliders[i];
        s->setIncrement(1);
    }
    gui4->autoSizeToFitWidgets();
    
    
	ofAddListener(gui4->newGUIEvent,this,&testApp::guiEvent);
}

