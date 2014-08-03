//
//  Neck.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Neck.h"

Neck::Neck(){
    
    
    
    printf("nova classe Neck\n");
    
    
    
}

Neck::~Neck(){
    
    printf("destruir classe Neck\n");
    
    
    
}

Neck::Neck(ofxOscMessage* msg){
    setOscMsg(msg);
}