//
//  Hips.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Hips.h"

Hips::Hips(){
    
    
    
    printf("nova classe Hips\n");
    
    
    
}

Hips::~Hips(){
    
    printf("destruir classe Hips\n");

}

Hips::Hips(ofxOscMessage* msg){
    setOscMsg(msg);
}