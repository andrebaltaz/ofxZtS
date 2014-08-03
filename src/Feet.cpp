//
//  Feet.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Feet.h"

Feet::Feet(){
    
    
    
    printf("nova classe Feet\n");
    
    
    
}

Feet::~Feet(){
    
    printf("destruir classe Feet\n");
    
    
}
    
    Feet::Feet(ofxOscMessage* msg){
        setOscMsg(msg);
    }
