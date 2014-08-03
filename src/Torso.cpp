//
//  Torso.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Torso.h"

Torso::Torso(){
    
    
    
    printf("nova classe Torso\n");
    
    
    
}

Torso::~Torso(){
    
    printf("destruir classe Torso\n");
    
}

Torso::Torso(ofxOscMessage* msg){
    setOscMsg(msg);
}
