//
//  Neck.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Neck_h
#define allAddonsExample_Neck_h
#include "Body_Parts.h"


class Neck:public Body_Parts {
    
public:
    Neck();
    ~Neck();
    
     Neck(ofxOscMessage* msg);
};

#endif
