//
//  Master.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Master.h"


Master::Master(){

}

Master::~Master(){

}


Master::Master(ofxOscMessage* msg){
    setOscMsg(msg);
    
}


void Master::setOscMsg(ofxOscMessage *msg){
    oscMsg_ = msg;
}

int Master::getId(){
    return index_;
}

void Master::setup(){
    
   
}

//--------------------------------------------------------------
void Master::update(){
    
}

//--------------------------------------------------------------
void Master::draw(){
    
}
