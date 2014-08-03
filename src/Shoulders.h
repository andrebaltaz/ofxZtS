//
//  Shoulders.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Shoulders_h
#define allAddonsExample_Shoulders_h

#include "Body_Parts.h"

class Shoulders:public Body_Parts {
    
public:
    Shoulders();
    ~Shoulders();
    
     Shoulders(ofxOscMessage* msg);
};

#endif
