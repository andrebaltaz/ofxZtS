//
//  Knees.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 02/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Knees_h
#define allAddonsExample_Knees_h

#include "Body_Parts.h"


class Knees:public Body_Parts {
    
public:
    Knees();
    ~Knees();
    
    Knees(ofxOscMessage* msg);
};




#endif
