//
//  timer.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 14/02/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_timer_h
#define allAddonsExample_timer_h

#include "Globals.h"
#include "Master.h"

class Timer: public Master{
    
public:
    
    Timer();
    ~Timer();
    
    void On();
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
   
    
    float startTime; // store when we start time timer
    float endTime; // when do want to stop the timer
    
private:
    bool first_run;
    float pct;
    float timer;
    bool runTimer;
    bool  bTimerReached; // used as a trigger when we hit the timer
	
  //  testApp * pt_testApp;
    
};


#endif
