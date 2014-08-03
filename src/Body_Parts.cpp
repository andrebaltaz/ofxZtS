//
//  Body_Parts.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 28/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Body_Parts.h"
#define nSeqTrainHmm 5


Body_Parts::Body_Parts(){
    
    add_to_gestures=false;
    HmmTrained=false;
 
    //printf("nova classe Body_parts\n");
    // pt_Hmm = new Hmm();
    
    thresh=0.1;
    count=0;
    gestureCount=0;
    draw_distance= false;
    dist_aux=10.0;
    
    verdana14.loadFont("verdana.ttf", 18, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
    recognized=false;
}

Body_Parts::~Body_Parts(){
    
    printf("destruir classe Body_parts\n");
    
    
    
}

//receives the osc message
Body_Parts::Body_Parts(ofxOscMessage* msg){
    setOscMsg(msg);
}

//retrieves the elements of the osc message and stores it on the respective vector
void Body_Parts::update(){
    set_coords(oscMsg_->getArgAsFloat(2), oscMsg_->getArgAsFloat(3), oscMsg_->getArgAsFloat(4), ofGetElapsedTimeMillis()-t0);
    
    
    if (hmmMode==true) {
        draw_distance=true;
    }
    
    /*
     if (SavetoFile) {
     
     if (count==0) {
     string path=ofFilePath::getAbsolutePath("", true)+oscMsg_->getArgAsString(0)+".txt";
     txtfile=fopen(path.c_str(), "a");
     string a="START: "+ofGetTimestampString();
     fprintf (txtfile,"\n---%s---\n", a.c_str());
     count++;
     }
     
     if (txtfile!=NULL)
     {
     string a=ofToString(oscMsg_->getArgAsString(0))+" "+ofToString(oscMsg_->getArgAsFloat(2))+" "+ofToString(oscMsg_->getArgAsFloat(3))+" "+ofToString(oscMsg_->getArgAsFloat(4))+" "+ofToString(ofGetElapsedTimeMillis()-t0)+"\n";
     fprintf (txtfile,"%s", a.c_str());
     
     }
     
     }
     if (!SavetoFile && count>0) {
     string a="STOP: " +ofGetTimestampString();
     fprintf (txtfile,"---%s---\n", a.c_str());
     fclose (txtfile);
     count=0;
     }
     */
}

//stores the coordinates x y z and the time they arrived, also keeps a copy of the previous coord to do some maths with
//them: distances, velocities, accelerations...

void Body_Parts::set_coords(float x, float y, float z, float t){
    
    previous_coords.set(coords.x, coords.y, coords.z, coords.w);
    coords.set(x, y, z, t);
}

//returns the coords to other classes
ofVec4f Body_Parts::Get_coords(){
    
    return coords;
    
}

vector<vector<ofVec4f> > Body_Parts::Get_gestures(){
    
    return gestureshistory;
}

void Body_Parts::Set_Gestos(vector<ofVec4f> gest_file){
    
    for (int i=0; i<gest_file.size(); i++) {
        set_coords(gest_file[i].x, gest_file[i].y, gest_file[i].z, gest_file[i].w);
        Save_coords();
    }
    add_to_gestures=true;
    Test_coordDist();
}


float Body_Parts::Get_distance(){
    
    float aux_dist= (abs(coords.x-previous_coords.x)+ abs(coords.y-previous_coords.y)+ abs(coords.z-previous_coords.z));
    
    return aux_dist;
    
}


//records gestures, called from skel.c when in capture mode
void Body_Parts::Save_coords(){
    
    //if vector of gestures is full delete the first one (fifo stack)
    if (ground_truth.size()<=M){
        
       // ground_truth_coords.push_back(coords);
        Distance();
        ground_truth.push_back(dist);
         history.push_back(coords);
       
    }
    
    
}

//calculus of distance between the actual coord and the previous one
void Body_Parts::Distance(){
    
    double result=atan2((coords.y-previous_coords.y)*ofGetHeight(),(coords.x-previous_coords.x)*ofGetWidth())* 180 / PI;
    int word;
    
    if (result<0) {
        word=(result+360)/30;
    }
    else
        word=result/30;
    
    dist.set(coords.x-previous_coords.x, coords.y-previous_coords.y, coords.z-previous_coords.z, word);
    
}


vector<int> Body_Parts::HmmVocabulary(vector<ofVec4f> v_word){
    
    //dist.set(coords.x-previous_coords.x, coords.y-previous_coords.y, coords.z-previous_coords.z, coords.w-previous_coords.w);
    
    double x, y, result;
     int word=0;
    hmm_seq.clear();
    for (int i=0 ; i<v_word.size() ; i++){
       
        result=atan2((-1*v_word[i].y)*ofGetHeight(),(v_word[i].x)*ofGetWidth())* 180 / PI;
        
        if (result<0) {
            word=(result+360)/30;
        }
        else
            word=result/30;
        
        if (hmm_seq.size()>=M){
            hmm_seq.erase(hmm_seq.begin()+0);
        }
        hmm_seq.push_back(word);
        
       // printf ("hmm: i=%d, x=%f y=%f dify=%f, difx=%f atg=%f   %d\n", i,ground_truth_coords[i].x*ofGetWidth(), ground_truth_coords[i].y*ofGetHeight(), (ground_truth[i].y*ofGetHeight()),(ground_truth[i].x*ofGetWidth()), result, word );
        
        
    }
    //while (hmm_seq.size()<=M) {
    //    hmm_seq.push_back(word);
    //}
    return hmm_seq;
}



//clears the recorded gestures
void Body_Parts::ClearHistory(){
    
    dist_dtw.clear();
    gestureshistory.clear();
    gestureshmm.clear();
    gestures.clear();
    //cout<<" reset gestos= "<<gestures.size()<<endl;
    history.clear();
    ground_truth.clear();
    found_gest_cue.clear();
    mark_gest.clear();
    history_aux.clear();
    gest_features.clear();
    clear_history=false;
    gestureCount=0;
    
    cout<<gestureshistory.size()<<endl;
}

//tests the incoming gestures against the recorded ones
void Body_Parts::Test_coordDist(){
    
    if (add_to_gestures) {
        HmmTrained=false;
        gestureCount++;
        
        if (ground_truth.size()>10) {
            
            //store gestures with the consecutive difference for testing with DTW and HMM
            gestures.push_back(Smooth(ground_truth));
            
            gestureshistory.push_back(Smooth(history));
            
            //gestureshistory.push_back(history);
            
            //create a new slot to store the dtw distance
            double a=10.0;
            dist_dtw.push_back(a);
            history.clear();
            
           
            history_aux.push_back(coords);
            Features();
            
            gestureshmm.push_back(HmmVocabulary(gestures[gestures.size()-1]));
            
            //store gestures as HMMvocabulary, this case the artg(y,x) giving the orientation
            //gestureshmm.push_back(hmm_seq);
            
            //cout<<"GT.size= "<<ground_truth.size()<< endl;//" HMM seq="<<gestures[gestures.size()-1].size() <<" gestures recorded= "<<gestures.size()<<" HMM gest "<<gestureshmm.size()<<endl;
            
            ground_truth.clear();
            
                        
        }
 
        
        
        
        ground_truth.clear();
        add_to_gestures=false;
        // ground_truth.clear();
    }
    
    if (delete_last==true && gestureshistory.size()>0 && gestureshmm.size()>0) {
        delete_last=false;
        
        gestureshistory.erase(gestureshistory.end());
        gestures.erase(gestures.end());
        gestureshmm.erase(gestureshmm.end());
        //dist_dtw.erase(dist_dtw.end());
        history_aux.erase(history_aux.end());
    }else delete_last=false;

    
    if (visual_cue.size()>50)
        visual_cue.erase(visual_cue.begin()+0);
    visual_cue.push_back(coords);
    
    
    if (coordDist.size()>M*5)
        coordDist.erase(coordDist.begin()+0);
    Distance();
    coordDist.push_back(dist);
    
    if (test_hmm.size()>=M) {
        test_hmm.erase(test_hmm.begin()+0);
    }
    test_hmm.push_back(dist.w);
    
    if (gestureCount>0 && dtwMode==true) {
        
        //cout<<"DTW: "<<gestures.size()<<endl;
        //Calculate_DTW();
       
           }
    
    if (HmmTrained==true && test_hmm.size()>M-1 && hmmMode==true) {
        //Calculate_HMM();
    }
}

void Body_Parts::TrainHmm(){
    double time;
    // TODO:DECIDE WHEN TO train the HMM by pressing a key
    if (gestureshmm.size()>=nSeqTrainHmm) {
        gestnum=9;
              time=ofGetElapsedTimeMillis();  
        vec_hmm_models.push_back(new testHMM(gestureshmm, gestnum));
        logHmmModel.push_back(vec_hmm_models[vec_hmm_models.size()-1]->Run(3, gestureshmm));
        
        vec_hmm_models[vec_hmm_models.size()-1]->Run(2, gestureshmm);
        
        
        
       /* if (logHmmModel[vec_hmm_models.size()-1]<-500) {
            cout<<"DEleting last model"<<endl;
            vec_hmm_models.erase(vec_hmm_models.end());
        }*/
        gestureshmm.clear();
        HmmTrained=true;
        double took=ofGetElapsedTimeMillis()-time;
        printf("%.4f\n", took);
        cout<<"train time "<<took<<endl;
        
           }
    
    
    ignore=false;
   

    
}


int Body_Parts::Calculate_HMM(){

    double time;
    double min=300;
    int min_index=20;

    for (int j=0; j<gestureshmm.size(); j++) {
        gesture_testing.push_back(gestureshmm[j]);
        //gestureshmm.push_back(test_hmm);
        
        for (int i=0; i<vec_hmm_models.size(); i++) {
            
            time=ofGetElapsedTimeMillis();
            logHmmModel[i]= vec_hmm_models[i]->Run(1, gesture_testing);
            cout<<i<<" "<<logHmmModel[i]<<" ";
            
            // cout<<logHmmModel[i]<<" ";
            
        }
        
        
        for (int i=0; i<vec_hmm_models.size(); i++) {
            
            if (logHmmModel[i]*(-1)<min) {
                min=logHmmModel[i]*(-1);
                min_index=i;
            }
            
        }
    }
    
    gesture_testing.clear();
    cout<<endl;
    //gestureshmm.clear();
    ignore=false;
    
    cout<<min_index<<endl;
   // if (min*(-1)>hmmthreshold) {
        return min_index;
        //}
        
   // }
}


void Body_Parts::TrainDtw(){
    double time;
    // TODO:DECIDE WHEN TO train the HMM by pressing a key
    if (gestures.size()>=1) {
        
        time=ofGetElapsedTimeMillis();
       
        for (int i=0; i<gestures.size(); i++) {
            gesturesDtw.push_back(gestures[i]);
        }
        
        double took=ofGetElapsedTimeMillis()-time;
        printf("%.4f\n", took);
        cout<<"train time "<<took<<endl;
        
    }
    
    
    ignore=false;
    draw_distance=true;
    
    
}


//calculus of the DTW distance original
/*int Body_Parts::Calculate_DTW(){
    
    Point1 aux(0, 0, 0, 0);
    
    for (int gest=0; gest<gestures.size(); gest++) {
        
        aux_gt=gestures[gest];
        
        // for (int xis=1; xis>1; xis=xis/2){
        int xis=1;
        int step=aux_gt.size()/xis;
        
        if (coordDist.size()>aux_gt.size()-1) {
            
            int i = coordDist.size()-step;
            int j=0;
            int k=0;
            
            while(k<=step){
                
                aux.x=aux_gt[j].x;
                aux.y=aux_gt[j].y;
                aux.z=aux_gt[j].z;
                
                auxMain.push_back(aux);
                
                aux.x = coordDist[i].x;
                aux.y=coordDist[i].y;
                aux.z=coordDist[i].z;
                
                auxTest.push_back(aux);
                i++;
                j=j+xis;
                k++;
            }
            
            
            //select the maximum warping distance
            //tipically n/10
            VectorDTW dtw1(auxMain.size(), auxMain.size()/10);
            
            prov_distance=dtw1.fastdynamic(auxMain, auxTest);
            if (dist_dtw.size()>=gest) {
                dist_dtw[gest]=prov_distance;
            }
            
            auxMain.clear();
            auxTest.clear();
            
            draw_distance=true;
            
        }
        //}
    }
    
    min_tresh=10;
    
    for (int i=0; i<dist_dtw.size(); i++) {
        
        if (min_tresh>dist_dtw[i]) {
            min_tresh=dist_dtw[i];
            index=i;
        }
    }
    
    if (min_tresh<1) {
        if (found_gest_cue.size()>200){
            found_gest_cue.erase(found_gest_cue.begin()+0);
        }
        
        found_gest_cue.push_back(coords);
    }
}*/



//DTW calculus modified for testing
int Body_Parts::Calculate_DTW(){
    
    Point1 aux(0, 0, 0, 0);
    
    
    
    for (int i=0; i<gestures.size(); i++) {
        double min_distance=500;
        int gest_index=50;
        for (int gest=0; gest<gesturesDtw.size(); gest++) {
            
            aux_gt=gestures[i];
            int j=aux_gt.size()-1;
            
            if (gesturesDtw[gest].size()>aux_gt.size()) {
                while (gesturesDtw[gest].size()>aux_gt.size()) {
                    aux_gt.push_back(aux_gt[j]);
                    
                }
                
            }
            else{
                
                while (gesturesDtw[gest].size()<aux_gt.size()) {
                    aux_gt.erase(aux_gt.begin()+j);
                    if (j<aux_gt.size()-3) {
                        j=j+3;
                    }
                    
                }
            }
            
            //cout<<gesturesDtw[gest].size()<<" "<<gestures[i].size()<<endl;
            
            //select the maximum warping distance
            //tipically n/10
            VectorDTW dtw1(gesturesDtw[gest].size(), gesturesDtw[gest].size()/10);
            
            prov_distance=dtw1.fastdynamic(gesturesDtw[gest], aux_gt)/100;
            
            if (prov_distance<min_distance) {
                min_distance=prov_distance;
                gest_index=gest;
            }
            
            if (dist_dtw.size()>=gest) {
                dist_dtw[gest]=prov_distance;
            }
            
            cout<< prov_distance<<" ";
            
        }
        
        cout<<gest_index;
        cout<<endl;
        ignore=false;
        
        
        //}
    }
    
    min_tresh=10;
    
    for (int i=0; i<dist_dtw.size(); i++) {
        
        if (min_tresh>dist_dtw[i]) {
            min_tresh=dist_dtw[i];
            index=i;
        }
    }
    
    if (min_tresh<dtwthreshold) {
        if (found_gest_cue.size()>200){
            found_gest_cue.erase(found_gest_cue.begin()+0);
        }
        
        found_gest_cue.push_back(coords);
    }
}


// not being used
float Body_Parts::Compare(ofVec4f test , ofVec4f gtruth){
    
    float diferenca= test.x-gtruth.x;
    //cout<<" "<<diferenca<<endl;
    
    return diferenca;
    
}



void Body_Parts::Features(){
    
    if (gestures.size()>0){
        
        float last_vel=0;
        vel=0;
        accel=0;
        
        for (int i=0 ; i<ground_truth.size() ; i++){
            
            float vel_temp= sqrt((ground_truth[i].x*ofGetWidth())*(ground_truth[i].x*ofGetWidth())+(ground_truth[i].y*ofGetHeight())*(ground_truth[i].y*ofGetHeight())+(ground_truth[i].z)*(ground_truth[i].z))*ofGetFrameRate();
            
            if (i>=1) {
                accel=+((vel_temp-last_vel)/ofGetFrameRate());
            }
            
            vel=vel+vel_temp;
            last_vel=vel_temp;
            
        }
        
        
        
        avgVel=vel/ground_truth.size();
        avgAccel=accel/ground_truth.size();
        feat.set(avgVel, avgAccel, 0 ,0);
        
        
        gest_features.push_back(feat);
        
    }
    
}

vector<ofVec4f> Body_Parts::Smooth(vector<ofVec4f> vector_smooth){
 
    int window=1;
    double x=0;
    double y=0;
    double z=0;
    double t=0;
    ofVec4f aux;
    vector<ofVec4f> aux_smooth;
    
           for (int j=0; j<vector_smooth.size()-window; j=j+window) {
            for (int k=0; k<window; k++) {
                x= x+ vector_smooth[j+k].x;
                y= y+vector_smooth[j+k].y;
                z=z+ vector_smooth[j+k].z;
                t=vector_smooth[j+k].w;
            }
            x=x/window;
            y=y/window;
            z=z/window;
            
            aux.set(x, y, z, t);
            aux_smooth.push_back(aux);
            x=0;
            y=0;
            z=0;
        }
        return aux_smooth;
    
    
    
}

void Body_Parts::draw(){
    
   // ofSetColor(0, 0, 250);
   // ofCircle(0.21*ofGetWidth(), 0.51*ofGetHeight(), 5);
    // printf("draw %f %f %f\n", coords.x, coords.y, coords.z);
    ofSetColor(255,255,255);
    
    float middle=ofGetWidth()/2;
    float midtop=ofGetHeight()/8;
    //draw the joints
    //ofCircle(coords.x*ofGetWidth(), coords.y*ofGetHeight()-10, 10-coords.z*2);
    verdana14.drawString("Gestures recorded " + ofToString(gestures.size(), 3), middle+middle-320, 40);
    if (draw_distance) {
        
      
        
        if (dtwMode) {
            
            verdana14.drawString("Gestures recorded " + ofToString(gesturesDtw.size(), 3), middle+middle-320, 40);
            verdana14.drawString("DTW mode", middle+middle-320, 20);
            verdana14.drawString("Treshold " + ofToString(dtwthreshold, 2), middle+middle-320, 60);
            dist_aux=MIN(prov_distance, dist_aux);
            //verdana14.drawString("Distance min " + ofToString(dist_aux, 3), middle+middle-200, midtop+40);
            
            for (int i=0; i<gesturesDtw.size(); i++) {
                
                //if (dist_dtw[i]<1.5) {
                    
                    
                    if (index==i) {
                        ofSetColor(50+(50*i),200-(10*i),50+(20*i));
                    }
                    else
                        ofSetColor(100, 100, 100);
                
                if (dist_dtw[i]<dtwthreshold) {
                    verdana14.drawString("---->Found G"+ ofToString(i, 1) + ": "+ ofToString(dist_dtw[i], 2), middle+middle-310, 80+(i*20));
                }else
                    verdana14.drawString("Distance G"+ ofToString(i, 1) + ": "+ ofToString(dist_dtw[i], 2), middle+middle-300, 80+(i*20));
                    
                //}
            }
            
            if (min_tresh<dtwthreshold) {
                //verdana14.drawString("Gesture closer: "+ ofToString(index, 3), middle+middle-200, midtop+40);
                
                //cout<<"FoundGesture "<<index<<endl;
                
                ofSetColor(0, 255, 0);
                for (int i =0; i<found_gest_cue.size(); i++) {
                    
                    ofCircle(found_gest_cue[i].x*ofGetWidth() ,found_gest_cue[i].y*ofGetHeight(), 5);
                    
                    //ofLine(ground_truth[i].x*ofGetWidth(), ground_truth[i].y*ofGetHeight(), ground_truth[i+1].x*ofGetWidth(), ground_truth[i+1].y*ofGetHeight());
                }
                
                
                
            }//else verdana14.drawString("To far "+ofToString(min_tresh, 3), middle+middle-200, midtop+100);
            
            
            
            for (int i =0; i<history_aux.size(); i++) {
                ofSetColor(255, 255, 255);
                ofDrawBitmapString("  Gesture  " + ofToString(i, 3) +"\n Vel = " + ofToString(gest_features[i].x,3)+ "\n Accel= "+ ofToString(gest_features[i].y), history_aux[i].x*ofGetWidth(),history_aux[i].y*ofGetHeight());
                
            }
            
        }
        
        if (hmmMode) {
            
            if (trainMode==true) {
                verdana14.drawString("Train mode" , 2, ofGetHeight()/2);
            }else
                verdana14.drawString("Testing mode" , 2, ofGetHeight()/2);
            
            verdana14.drawString("HMMs trained: " + ofToString(vec_hmm_models.size(), 1), 2, 40);
            verdana14.drawString("HMM treshold: " + ofToString(hmmthreshold, 2), 2, 20);

            
            float closesthmm=-500;
            int indexhmm=0;
            
            for (int i=0; i<vec_hmm_models.size(); i++) {
                
                if (closesthmm<logHmmModel[i]) {
                    closesthmm=logHmmModel[i];
                     indexhmm=i;
                }
            }

            
            for (int i=0; i<vec_hmm_models.size(); i++) {
               
                if (indexhmm==i) {
                    
                    ofSetColor(50+(50*i),200-(10*i),50+(20*i));
                }
                else
                    ofSetColor(100, 100, 100);
                
                if (logHmmModel[i]>hmmthreshold) {
                    
                    recognized=i;
                    log_rec=logHmmModel[i];
                    tempo=ofGetElapsedTimeMillis();
                    
                   // while (ofGetElapsedTimeMillis()-tempo<1000) {
                   //     verdana14.drawString("RECOGNIZED ", 200, 60+20*i);
                        
                //}
                    
                    
                    
                    
                }
                    
                verdana14.drawString("Gesture " + ofToString(i) + " Likelyhood "+ ofToString(logHmmModel[i], 3), 2, 60+20*i);

                    
                                  
                //}

               
            }
            
            ofSetColor(255, 255, 255);
            
            if (recognized<10) {
            
                if (ofGetElapsedTimeMillis()-tempo<1000) {
                //verdana14.drawString("  <---RECOGNIZED this "+ ofToString(log_rec, 3), 400, 60+20*recognized);
            }
                else recognized=11;
            
                }
            
                       //verdana14.drawString("LogHmm " + ofToString(logHmmModel[logHmmModel.size()-1], 3), 22, midtop+250);
//            if (logHmmModel[logHmmModel.size()-1]>-100) {
//                ofSetColor(255,255,255,255);
//                verdana14.drawString("LogHmm " + ofToString(logHmmModel[logHmmModel.size()-1], 3)+" "+ofToString(logHmmModel.size(), 3) , 22, midtop+300);
//            }
        }

        
    }
    
    /* 3D drawing
     glPushMatrix();
     glTranslatef(coords.x*ofGetWidth(), coords.y*ofGetHeight(), ofMap(coords.z, 0, 1, -100, 100));
     ofCircle(0, 0, 10);
     glPopMatrix();
     */
    
    
    
    if (history.size()>3) {
        for (int i=0; i<history.size(); i++) {
            ofSetColor(150, 150, 150);
            ofCircle(history[i].x*ofGetWidth() ,history[i].y*ofGetHeight(),3);
        }
    }
    
    
    //draw history vector...the gestures or drawings recorded
    for (int j=0; j<gestureshistory.size(); j++) {
        int k=200;
        for (int i =0; i<gestureshistory[j].size(); i++) {
            
            if (j==gestureshistory.size()-1) {
                 ofSetColor(255-2*gestureshistory[j].size()+2*i, 255-gestureshistory[j].size()+i ,255-gestureshistory[j].size()+i);
            }else
            ofSetColor((10*j+ 3*i),300-2*j,(20+j),255+ 2*j-(150-50/gestureshistory.size()));
            //////////////////////////////////////////////////////////////////ver aqui////////////
            ofCircle(gestureshistory[j][i].x*ofGetWidth() ,gestureshistory[j][i].y*ofGetHeight(), 5);// history[i+1].w-history[i].w);
        }
    }
    
    
    // just the red dots as visual clue of what we did
    ofSetColor(255, 0, 0);
    for (int i =0; i<visual_cue.size(); i++) {
        
        ofCircle(visual_cue[i].x*ofGetWidth() ,visual_cue[i].y*ofGetHeight(), 1);
        
        //ofLine(ground_truth[i].x*ofGetWidth(), ground_truth[i].y*ofGetHeight(), ground_truth[i+1].x*ofGetWidth(), ground_truth[i+1].y*ofGetHeight());
    }
}