//
//  timer.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 14/02/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "testApp.h"


Timer::Timer(){

    setup();

}

Timer::~Timer(){


}


void Timer::On(){
    
    if (first_run) {
        startTime=ofGetElapsedTimeMillis();
        runTimer=true;
        first_run=false;
    }
    

}
//--------------------------------------------------------------
void Timer::setup() {
    //ofBackgroundHex(0xc5c9b2);
    runTimer=false;
    bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = 1000; // in milliseconds
}

//--------------------------------------------------------------
void Timer::update() {
    
}
//--------------------------------------------------------------
void Timer::draw(){
    
    if (runTimer) {
        
    
    float barWidth = 500;

    // the background to the progress bar
    ofSetColor(100);
    ofRect((ofGetWidth()-barWidth)/2, ofGetHeight()-50, barWidth, 30);
    
        if (!bTimerReached) {
           
            // update the timer this frame
            
            float timer = ofGetElapsedTimeMillis() - startTime;
            if(timer >= endTime && !bTimerReached) {
                bTimerReached = true;        
                startTime=ofGetElapsedTimeMillis();
            }
            
    // get the percantage of the timer
    float pct = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
    ofSetHexColor(0xf02589);
    ofRect((ofGetWidth()-barWidth)/2, ofGetHeight()-50, barWidth*pct, 30);
    
    // draw the percantage
    ofSetColor(20);
    ofDrawBitmapString(ofToString(pct*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/2)+20);
    
                
        
    }
    // the timer has reached the end :)
    if(bTimerReached) {
        
        //capture=true;
        //flag_capture=1;
        
       // ofSetColor(255,255,255);
       // ofDrawBitmapString("Start Recording the gesture!", (ofGetWidth()-100)/2, (ofGetHeight()-25));
        // update the timer this frame
        
        float timer = ofGetElapsedTimeMillis() - startTime;
        if(timer >= endTime && bTimerReached) {
            bTimerReached = false; 
            runTimer=false;
            first_run=true;
           // capture=false;
           // cout<<"capture OFF"<<endl;
           // add_to_gestures=true;
           // flag_capture=0;
            
        }
    
        // get the percantage of the timer
        float pct = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
        ofSetColor(0,255,0);
        ofRect((ofGetWidth()-barWidth)/2, ofGetHeight()-50, barWidth*pct, 30);
        
        // draw the percantage
        ofSetColor(20);
        ofDrawBitmapString(ofToString(pct*100, 0)+"%", ((ofGetWidth()-barWidth)/2)+barWidth+10, (ofGetHeight()/2)+20);
        
        
    }
    
    // some information about the timer
    //string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0)+"\n";
    //info += "Start Time: "+ofToString(startTime, 1)+"\n";
    //info += "End Time:   "+ofToString(endTime/1000.0, 1)+" seconds\n";
    //info += "Timer:      "+ofToString(timer/1000.0, 1)+" seconds\n";
    //info += "Percentage: "+ofToString(pct*100, 1)+"%\n";
    //info += "\nPress ' ' to get a new random end time\n";
    //ofSetColor(255,255,255);
    //ofDrawBitmapString(info, 20, 20);
    }
}

//--------------------------------------------------------------
void Timer::keyPressed(int key) {

}


//--------------------------------------------------------------
void Timer::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::keyReleased(int key){
    
}

//--------------------------------------------------------------
void Timer::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void Timer::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Timer::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void Timer::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void Timer::dragEvent(ofDragInfo dragInfo){ 
    
}