//
//  Elbow.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 29/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Elbow.h"

Elbow::Elbow(){
    
    
    
    printf("nova classe Hips\n");
    
    
    
}

Elbow::~Elbow(){
    
    printf("destruir classe Hips\n");
    
    
    
}

Elbow::Elbow(ofxOscMessage* msg){
    setOscMsg(msg);
}

