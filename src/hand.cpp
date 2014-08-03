//
//  hand.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "hand.h"

Hand::Hand(){
    
   
    
    printf("nova classe Hand\n");
    
    
    
}

Hand::~Hand(){
    
    printf("destruir classe Hand\n");
    
    
    
}

Hand::Hand(ofxOscMessage* msg){
    setOscMsg(msg);
}

