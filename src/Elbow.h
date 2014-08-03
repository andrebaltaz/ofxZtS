//
//  Elbow.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 29/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Elbow_h
#define allAddonsExample_Elbow_h

#include "Body_Parts.h"


class Elbow:public Body_Parts {
    
public:
    Elbow();
    ~Elbow();
    
     Elbow(ofxOscMessage* msg);
};



#endif
