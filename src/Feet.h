//
//  Feet.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Feet_h
#define allAddonsExample_Feet_h

#include "Body_Parts.h"

class Feet:public Body_Parts {
    
public:
    Feet();
    ~Feet();
    
     Feet(ofxOscMessage* msg);
};

#endif
