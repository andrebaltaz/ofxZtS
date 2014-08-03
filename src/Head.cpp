//
//  Head.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Head.h"

Head::Head(){
    
    
    
    printf("nova classe Head\n");
    
    
    
}

Head::~Head(){
    
    printf("destruir classe Head\n");

}

Head::Head(ofxOscMessage* msg){
    setOscMsg(msg);
}
