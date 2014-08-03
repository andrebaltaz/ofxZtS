/*
 *  skel.h
 *  oscReceiveExample
 *
 *  Created by Andre Baltazar on 11/02/16.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SKEL
#define _SKEL

#include "Globals.h"
#include "Master.h"
#include "Hand.h"
#include "Hips.h"
#include "Elbow.h"
#include "Feet.h"
#include "Shoulders.h"
#include "Head.h"
#include "Neck.h"
#include "Torso.h"
#include "Knees.h"
#include "timer.h"

#define SIZEOFVEL 5
#define Vel_treshold 0.12

class Skel: public Master{
private:
    ofVec4f x1, x2;
    float start_time;
    vector<float> velocity;
    float vel_treshold;
    float avg_vel;
    
    
public:
	
	Skel ();
	~Skel ();
    
    Skel(ofxOscMessage* msg);
    
    //assembles the skeleton with the routines in body_parts
    void update();
    void draw();
    void clear();
    void drawbones(ofVec4f v, ofVec4f w);
    void drawjoints(ofVec4f v);
    
    
    ofTrueTypeFont verdana_skel;
    
    Head* pt_head;
    Neck* pt_neck;
    Shoulders* pt_shoulderR;
    Shoulders* pt_shoulderL;
    Elbow* pt_elbowR;
    Elbow* pt_elbowL;
    Hand* pt_handL;
    Hand* pt_handR;
    Torso* pt_torso;
    Hips* pt_hipR;
    Hips* pt_hipL;
    Knees* pt_kneeR;
    Knees* pt_kneeL;
    Feet* pt_footR;
    Feet* pt_footL;
    Timer* pt_timer;
    
    vector<vector<ofVec4f> > gestRec;

    
    string temp_string;
     ofBuffer databuffer;
    FILE * txtfile;

    
};
#endif