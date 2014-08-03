//
//  hand.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_hand_h
#define allAddonsExample_hand_h

#include "Body_Parts.h"

class Hand:public Body_Parts {

public:
    Hand();
    ~Hand();
    
    Hand(ofxOscMessage* msg);
   
};

#endif
