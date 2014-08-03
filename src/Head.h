//
//  Head.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Head_h
#define allAddonsExample_Head_h
#include "Body_Parts.h"


class Head:public Body_Parts {
    
public:
    Head();
    ~Head();
    
     Head(ofxOscMessage* msg);
};


#endif
