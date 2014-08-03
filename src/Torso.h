//
//  Torso.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Torso_h
#define allAddonsExample_Torso_h

#include "Body_Parts.h"


class Torso:public Body_Parts {
    
public:
    Torso();
    ~Torso();
    
    Torso(ofxOscMessage* msg);
};


#endif
