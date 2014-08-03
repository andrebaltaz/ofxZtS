//
//  Knees.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 02/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Knees.h"

Knees::Knees(){
    
    
    
    printf("nova classe Knees\n");
    
    
    
}

Knees::~Knees(){
    
    printf("destruir classe Knees\n");
    
    
    
}

Knees::Knees(ofxOscMessage* msg){
    setOscMsg(msg);
}