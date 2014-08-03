//
//  Hips.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef allAddonsExample_Hips_h
#define allAddonsExample_Hips_h
#include "Body_Parts.h"


class Hips:public Body_Parts {
    
public:
    Hips();
    ~Hips();
  Hips(ofxOscMessage* msg);  
    
};

#endif
