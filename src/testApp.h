#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include   "global.h"



class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit(); 

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
 
    
   

    
    ofxUIScrollableCanvas *gui; 
    ofxUIScrollableCanvas *gui2; 
    ofxUIScrollableCanvas *gui3; 
    ofxUIScrollableCanvas *gui4; 

    vector<ofxUIWidget*> triggersliders ;
    vector<ofxUIWidget*> colorsliders ;


    void setGUI(); 
    void setGUI2();
    void setGUI3();
    void setGUI4();
    
    void guiEvent(ofxUIEventArgs &e);    
    
    
    /*   
    void gestureRecognized(gesture &g);
    bool bUseKinect;
    KinectManager kinectManager;
  
  */
    
       
};
