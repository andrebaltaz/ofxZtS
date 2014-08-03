/*
 *  skel.cpp
 *  oscReceiveExample
 *
 *  Created by Andre Baltazar on 11/02/16.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 
 Gets the skel coordinates and does the drawings
 *
 */

#include "skel.h"
#include "ofMain.h"

Skel::Skel(){
    
    flag_capture=0;
    
    verdana_skel.loadFont("verdana.ttf", 20, true, true);
	verdana_skel.setLineHeight(18.0f);
	verdana_skel.setLetterSpacing(1.037);
    
    
}

Skel::Skel(ofxOscMessage* msg){
    setOscMsg(msg);
    
    if(oscMsg_->getAddress() == "/new_skel"){
        
        index_ = oscMsg_->getArgAsInt32(0);
        printf("nova classe Skel %d\n", index_);
        
    }
    //cout<<endl<<"to vendo isso "<<oscMsg_->getArgAsInt32(0)<<endl;
    else
        index_ = oscMsg_->getArgAsInt32(1);
    
    printf("Skel %d\n", index_);
    
    pt_handR= new Hand(oscMsg_);
    pt_handL= new Hand(oscMsg_);
    pt_hipL=new Hips(oscMsg_);
    pt_hipR=new Hips(oscMsg_);
    pt_neck=new Neck(oscMsg_);
    pt_head=new Head(oscMsg_);
    pt_shoulderL= new Shoulders(oscMsg_);
    pt_shoulderR= new Shoulders(oscMsg_);
    pt_torso= new Torso(oscMsg_);
    pt_elbowR=new Elbow(oscMsg_);
    pt_elbowL=new Elbow(oscMsg_);
    pt_kneeR=new Knees(oscMsg_);
    pt_kneeL=new Knees(oscMsg_);
    pt_footR=new Feet(oscMsg_);
    pt_footL=new Feet(oscMsg_);
    pt_timer=new Timer();
}

Skel::~Skel(){
    
    printf("destruir classe Skel\n");
    /*
     delete pt_handR;
     delete pt_handL;
     delete pt_hipL;
     delete pt_hipR;
     delete pt_neck;
     delete pt_head;
     delete pt_shoulderL;
     delete pt_shoulderR;
     delete pt_torso;
     delete pt_elbowR;
     delete pt_elbowL;
     */
    
}

void Skel::clear(){
    
    delete pt_handR;
    delete pt_handL;
    delete pt_hipL;
    delete pt_hipR;
    delete pt_neck;
    delete pt_head;
    delete pt_shoulderL;
    delete pt_shoulderR;
    delete pt_torso;
    delete pt_elbowR;
    delete pt_elbowL;
    delete pt_kneeL;
    delete pt_kneeR;
    delete pt_footL;
    delete pt_footR;
    delete pt_timer;
    
}

void Skel::update(){
    
    
    
    if(oscMsg_->getArgAsString(0) == "l_hand" && ignore==false){
        
        
        // cout<<"updating "<<oscMsg_->getArgAsString(0)<<endl;
        pt_handL->update();
        
        if (LEFTHAND==true) {
         
        
        //The recording of a gesture to file
        if (SaveGestureToFile) {
            
            SaveGestureToFile=false;
            //  if (count_save==0) {
            string path=ofFilePath::getAbsolutePath("", true)+ofToString(gestnum)+"_"+ofGetTimestampString()+".txt";
            txtfile=fopen(path.c_str(), "a");
            string a="Gesto: "+ofToString(gestnum);
            fprintf (txtfile,"%s\n", a.c_str());
            //count_save++;
            //  }
            
            if (txtfile!=NULL)
            {
                
                gestRec=pt_handL->Get_gestures();
                
                for (int i=0; i<gestRec.size(); i++) {
                    
                    for (int j=0; j<gestRec[i].size(); j++) {
                        
                        string a= ofToString(i)+" "+ofToString(gestRec[i][j].x)+" "+ofToString(gestRec[i][j].y)+" "+ofToString(gestRec[i][j].z)+" "+ofToString(gestRec[i][j].w)+"\n";
                        
                        fprintf (txtfile,"%s", a.c_str());
                        
                    }
                    string a="\n";
                    fprintf (txtfile,"%s", a.c_str());
                }
                
                
            }
            fclose (txtfile);
        }
        
        
        if (capture) {
            pt_handL->Save_coords();
        }
        else {
            if (flag_capture==false) {
                pt_handL->Test_coordDist();
            }
            
        }
        if(clear_history){
            pt_handL->ClearHistory();
            
        }
        }
    }
    
    if(oscMsg_->getArgAsString(0) == "r_hand" && ignore==false){
        
        
        pt_handR->update();
        
        if (RIGHTHAND==true) {
            
            
            //The recording of a gesture to file
            if (SaveGestureToFile) {
                
                SaveGestureToFile=false;
                //  if (count_save==0) {
                string path=ofFilePath::getAbsolutePath("", true)+ofToString(gestnum)+"_"+ofGetTimestampString()+".txt";
                txtfile=fopen(path.c_str(), "a");
                string a="Gesto: "+ofToString(gestnum);
                fprintf (txtfile,"%s\n", a.c_str());
                //count_save++;
                //  }
                
                if (txtfile!=NULL)
                {
                    
                    gestRec=pt_handR->Get_gestures();
                    
                    for (int i=0; i<gestRec.size(); i++) {
                        
                        for (int j=0; j<gestRec[i].size(); j++) {
                            
                            string a= ofToString(i)+" "+ofToString(gestRec[i][j].x)+" "+ofToString(gestRec[i][j].y)+" "+ofToString(gestRec[i][j].z)+" "+ofToString(gestRec[i][j].w)+"\n";
                            
                            fprintf (txtfile,"%s", a.c_str());
                            
                        }
                        string a="\n";
                        fprintf (txtfile,"%s", a.c_str());
                    }
                    
                    
                }
                fclose (txtfile);
            }
            
            
            if (capture) {
                pt_handR->Save_coords();
            }
            else {
                if (flag_capture==false) {
                    pt_handR->Test_coordDist();
                }
                
            }
            if(clear_history){
                pt_handR->ClearHistory();
                
            }
        }
        
        
        //x1= pt_handR->Get_coords();
        //x2=pt_handR->Get_coords();
        
        
        // float close=sqrt((x1.x-x2.x)*(x1.x-x2.x)+(x1.y-x2.y)*(x1.y-x2.y)+(x1.z-x2.z)*(x1.z-x2.z));
        
        //cout<<x2.x<<"-"<<x2.y<<"-"<<x2.z<<endl;
        //if the arm is straight or stretched will begin capture
        
       // float close=sqrt((x2.x-0.21)*(x2.x-0.21)+(x2.y-0.52)*(x2.y-0.52));
        //float close=sqrt((x2.x-x1.x)*(x2.x-x1.x)+(x2.y-x2.y)*(x2.y-x2.y));
        
        //cout<<close<<endl;
        
        //if (close<0.02) {
            
            // pt_timer->On();
            
            
        //}
        
    }
    
    if(oscMsg_->getArgAsString(0) == "r_hip"){
        pt_hipR->update();
        
        
    }
    
    if(oscMsg_->getArgAsString(0) == "l_hip"){
        pt_hipL->update();
        
    }
    if(oscMsg_->getArgAsString(0) == "head"){
        pt_head->update();
    }
    
    if(oscMsg_->getArgAsString(0) == "neck"){
        pt_neck->update();
    }
    if(oscMsg_->getArgAsString(0) == "torso"){
        pt_torso->update();
    }
    
    if(oscMsg_->getArgAsString(0) == "r_shoulder"){
        pt_shoulderR->update();
    }
    
    if(oscMsg_->getArgAsString(0) == "l_shoulder"){
        pt_shoulderL->update();
    }
    if(oscMsg_->getArgAsString(0) == "r_elbow"){
        pt_elbowR->update();
    }
    if(oscMsg_->getArgAsString(0) == "l_elbow"){
        pt_elbowL->update();
    }
    if(oscMsg_->getArgAsString(0) == "l_knee"){
        pt_kneeL->update();
    }
    if(oscMsg_->getArgAsString(0) == "r_knee"){
        pt_kneeR->update();
    }
    if(oscMsg_->getArgAsString(0) == "l_foot"){
        pt_footL->update();
    }
    if(oscMsg_->getArgAsString(0) == "r_foot"){
        pt_footR->update();
    }
    
    
    
}

void Skel::draw(){
    
    
    if (LEFTHAND==true) {
        pt_handL->draw();
        
    }
    
    if (RIGHTHAND==true) {
        pt_handR->draw();
        
    }

//    pt_handR->draw();
//    pt_hipR->draw();
//    pt_hipL->draw();
//    pt_neck->draw();
//    pt_head->draw();
//    pt_shoulderL->draw();
//    pt_shoulderR->draw();
//    pt_torso->draw();
//    pt_elbowL->draw();
//    pt_elbowR->draw();
//    pt_kneeR->draw();
//    pt_kneeL->draw();
//    pt_footR->draw();
//    pt_footL->draw();
    
    drawjoints(pt_handR->Get_coords());
   drawjoints(pt_handL->Get_coords());
    drawjoints(pt_elbowR->Get_coords());
    drawjoints(pt_handL->Get_coords());
    drawjoints(pt_elbowL->Get_coords());
    drawjoints(pt_shoulderL->Get_coords());
    drawjoints(pt_shoulderR->Get_coords());
    drawjoints(pt_hipR->Get_coords());
    drawjoints(pt_hipL->Get_coords());
    drawjoints(pt_kneeL->Get_coords());
    drawjoints(pt_kneeR->Get_coords());
    drawjoints(pt_footL->Get_coords());
    drawjoints(pt_footR->Get_coords());
    
    drawjoints(pt_neck->Get_coords());
    drawjoints(pt_head->Get_coords());
    drawjoints(pt_torso->Get_coords());
    
    
    drawbones(pt_handR->Get_coords(), pt_elbowR->Get_coords());
    drawbones(pt_elbowR->Get_coords(), pt_shoulderR->Get_coords());
    drawbones(pt_handL->Get_coords(), pt_elbowL->Get_coords());
    drawbones(pt_elbowL->Get_coords(), pt_shoulderL->Get_coords());
    drawbones(pt_shoulderL->Get_coords(), pt_shoulderR->Get_coords());
    drawbones(pt_shoulderL->Get_coords(), pt_hipL->Get_coords());
    drawbones(pt_shoulderR->Get_coords(), pt_hipR->Get_coords());
    drawbones(pt_hipR->Get_coords(), pt_kneeR->Get_coords());
    drawbones(pt_hipL->Get_coords(), pt_kneeL->Get_coords());
    drawbones(pt_kneeL->Get_coords(), pt_footL->Get_coords());
    drawbones(pt_kneeR->Get_coords(), pt_footR->Get_coords());
    drawbones(pt_hipR->Get_coords(), pt_hipL->Get_coords());
    drawbones(pt_neck->Get_coords(), pt_head->Get_coords());
    
    
    
    pt_timer->draw();
    
}

void Skel::drawjoints(ofVec4f v){
    ofFill();
    ofSetColor(200, 200, 200, 200);
    //draw the joints
    ofCircle(v.x*ofGetWidth(), v.y*ofGetHeight(), 10-v.z*2);

}


void Skel::drawbones(ofVec4f v, ofVec4f w){
    ofSetColor(200, 200, 200);
    //draw the joints
    //ofCircle(v.x*ofGetWidth(), v.y*ofGetHeight()-10, 10-v.z*2);
    
    ofLine(ofMap(v.x, 0, 1, 0, ofGetWidth()), ofMap(v.y, 0, 1, 0, ofGetHeight()), ofMap(v.z, 0, 15, -10,0), ofMap(w.x, 0, 1, 0, ofGetWidth()), ofMap(w.y, 0, 1,0, ofGetHeight()), ofMap(w.z, 0, 15, -10,0));
    
    
}




