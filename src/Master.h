//
//  Master.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Master_h
#define allAddonsExample_Master_h

#include "ofMain.h"
#include "ofxOsc.h"

//Master class with all the prototype classes for skels
class Master{
    
public:
    
    
    Master();
    ~Master();
    
    Master(ofxOscMessage* msg);
    
    void setup();
    void update();
    void draw();
    void Record();
    
    void setOscMsg(ofxOscMessage* msg);
    
    int getId();
    
protected:
    ofxOscMessage* oscMsg_;
    int index_;
};

#endif
