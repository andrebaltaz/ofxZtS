#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofx3DModelLoader.h"
#include "ofxAssimpModelLoader.h"
#include "ofxThreadedImageLoader.h"
#include "Master.h"
#include "Skel.h"
#include "Globals.h"

#include "Gui.h"


//define the OSC Port to listen to
//choose wich one you're using or leave both open

//OSCeleton
#define PORT 7110
#define PORTSEND 4444
#define IPSEND "127.0.0.1"

//Synapse
#define PORT2 12345


class testApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo info);
    void gotMessage(ofMessage msg);		
   
    bool synapse;
    int tempo_savefile;
    
    int feed_drawmode;
    int feed_trainingHmm;
    int feed_gestrecord;
    int feed_handcontrol;
    int trigger_gesture;
    vector<Skel*> skeletos;
        
    
    FILE * txtfile;
    ofxOscReceiver oscIn;
    ofxOscSender oscOut;
    ofxOscMessage* oscMsg;
    ofTrueTypeFont text;
    ofTrueTypeFont text1;
    Gui* pt_gui;
    
    
    bool show_gui;
    ofVec4f neck;
    float perto;
    
    
    //dragevents
    ofPoint dragPt;
	vector<vector<ofVec4f> > gest_load;
    ofVec4f aux;
    vector<ofVec4f> auxVec;

    
};
