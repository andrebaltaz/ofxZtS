//
//  Shoulders.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Shoulders.h"

Shoulders::Shoulders(){
    
    
    
    printf("nova classe Shoulders\n");
    
    
    
}

Shoulders::~Shoulders(){
    
    printf("destruir classe Shoulders\n");
    
    
    
}

Shoulders::Shoulders(ofxOscMessage* msg){
    setOscMsg(msg);
}