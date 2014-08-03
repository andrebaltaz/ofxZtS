//
//  Body_Parts.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Body_Parts_h
#define allAddonsExample_Body_Parts_h

#include "Master.h"
#include "ofMain.h"
#include "Globals.h"
#include "vectordtw.h"
#include "HMM.h"


#define M 100

//contains prototypes
class Body_Parts: public Master{

public:
    Body_Parts();
    ~Body_Parts();
    void keyPressed(int key);
    void set_coords(float x, float y, float z, float t);
    void Save_coords();
    void Test_coordDist();
    void draw();
    Body_Parts(ofxOscMessage* msg);
    void Distance();
    void update();
    void ClearHistory();
    float Compare(ofVec4f test , ofVec4f gtruth);
    int Calculate_DTW();
    int Calculate_HMM();
    void Set_Gestos(vector<ofVec4f>gest_file);
    void TrainHmm();
    void TrainDtw();
    
    vector<ofVec4f> Smooth(vector<ofVec4f> vector_smooth);
    
    
    ofVec4f Get_coords();
    float Get_distance();
    vector<vector<ofVec4f> > Get_gestures();
    
    
    void Features();
    vector<int> HmmVocabulary(vector<ofVec4f> v_word);
    
private:
    int draw_distance;
    vector<double> dist_dtw;
   
    int count;
    bool recognized;
    float vel, avgVel, accel, avgAccel;
    float CompX;
    float CompY;
    float thresh;
    ofVec4f coords;
    ofVec4f previous_coords;
    ofVec4f dist;
    int tempo;
    double log_rec;
    vector<int> hmm_seq;
    vector<ofVec4f> history;
    vector<ofVec4f> history_aux;
    vector<ofVec4f> visual_cue;
    vector<ofVec4f> ground_truth;
    vector<ofVec4f> ground_truth_coords;
    vector<ofVec4f> coordDist;
    vector<ofVec4f> found_gest_cue;
    vector<ofVec4f> mark_gest;
    
    vector<vector<ofVec4f> > gestureshistory;
    vector<vector<ofVec4f> > gestures;
    vector<vector<ofVec4f> > gesturesDtw;
    vector<vector<int> > gestureshmm;
    vector<int> test_hmm;
    vector<vector<int> >gesture_testing;
    
    FILE * txtfile;
    
    ofVec4f feat;
    vector<ofVec4f> gest_features;
    
    vector<int> aux_gthmm;
    vector <ofVec4f> aux_gt;
    vector<Point1> auxMain;
    vector<Point1> auxTest;
    
    int gestureCount;
    float prov_distance;
    float min_tresh;
    int index;
    double dist_aux;
    bool HmmTrained;
    
    vector<double>logHmmModel;
    ofTrueTypeFont	verdana14;
    
    vector<testHMM*> vec_hmm_models;
};



#endif
