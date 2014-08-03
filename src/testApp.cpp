#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(100,120,100);
    oscIn.setup(PORT);
    oscOut.setup(IPSEND, PORTSEND);
    oscMsg = new ofxOscMessage;
    t0=tempo_savefile=0;
    capture=false;
    dtwMode=false;
    SavetoFile=false;
    SaveGestureToFile=false;
    pt_gui = new Gui;
    show_gui=false;
    pt_gui->gui1->toggleVisible();
    text.loadFont("verdana.ttf", 15, true, true);
    text1.loadFont("verdana.ttf", 13, true, true);
	text.setLineHeight(18.0f);
	text.setLetterSpacing(1.037);
    show_gui==false;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // pt_gui->update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    //take care of the OSC messages arriving
    while(oscIn.hasWaitingMessages()){
		// get the next message
		oscIn.getNextMessage(oscMsg);
        
        //if "lost_user" delete the respective skeleton
        if(oscMsg->getAddress() == "/lost_user"){
            for(int i=0; i<skeletos.size(); i++){
                if(skeletos[i]->getId() == oscMsg->getArgAsInt32(0)){
                    skeletos[i]->clear();
                    skeletos.erase(skeletos.begin()+i);
                }
            }
            
		}
        //if "new_skel" create a new instance of skel class
		if(oscMsg->getAddress() == "/new_skel"){
            
            printf("received new skel\n");
			skeletos.push_back(new Skel(oscMsg));
		}
        //if a skel was already present when the application started running
        else if(oscMsg->getAddress() == "/joint"){
            

            if (skeletos.size()==0) {
                printf("received skel already there\n");
                skeletos.push_back(new Skel(oscMsg));
            }
            else
                
                //do the skels update
                for(int i=0; i<skeletos.size(); i++){
                    
                    if(skeletos[i]->getId() == oscMsg->getArgAsInt32(1)){
                        skeletos[i]->update();
                        
                        
                        if (skeletos.size()>0) {
                            
                            perto=300.0;
                            
                            for(int j=0; j<skeletos.size(); j++){
                                
                                neck=skeletos[j]->pt_neck->Get_coords();
                                
                                if (neck.x*ofGetWidth()>ofGetWidth()/10 && neck.x*ofGetWidth()<ofGetWidth()*9/10)
                                    if (neck.z< perto) {
                                        skel_index=skeletos[j]->getId();
                                        perto=neck.z;
                                    }
                                
                            }
                            
                            if (skel_index==skeletos[i]->getId()) {
                                
                                neck=skeletos[i]->pt_neck->Get_coords();
                                if (neck.x*ofGetWidth()>ofGetWidth()/10 && neck.x*ofGetWidth()<ofGetWidth()*9/10){
                                    
                                    // fx.skeleton = skeletos[i];
                                    //  printf("im in\n");
                                    //  triggers(i);
                                }
                            }
                            
                        }
                        
                        
                    }
                }
        }
        
        if (SavetoFile) {
            
            if (count_save==0) {
                string path=ofFilePath::getAbsolutePath("", true)+ ofToString(ofGetHours())+ofToString(ofGetMinutes())  +".txt";
                txtfile=fopen(path.c_str(), "a");
                string a="START: "+ofGetTimestampString();
                fprintf (txtfile,"\n---%s---\n", a.c_str());
                count_save++;
            }
            
            if (txtfile!=NULL)
            {   //string a=ofToString(oscMsg_)+" "+ofToString(ofGetElapsedTimeMillis()-t0)+"\n";
                string a= ofToString(oscMsg->getAddress())+" "+ofToString(oscMsg->getArgAsString(0))+" "+ofToString(oscMsg->getArgAsInt32(1))+" "+ofToString(oscMsg->getArgAsFloat(2))+" "+ofToString(oscMsg->getArgAsFloat(3))+" "+ofToString(oscMsg->getArgAsFloat(4))+" "+ofToString(ofGetElapsedTimeMillis()-t0)+"\n";
                fprintf (txtfile,"%s", a.c_str());
                
            }
            
        }
        if (!SavetoFile && count_save>0) {
            string a="STOP: " +ofGetTimestampString();
            fprintf (txtfile,"---%s---\n", a.c_str());
            fclose (txtfile);
            count_save=0;
        }
        
        
               
        
        
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    pt_gui->draw();
    
    //draw each skeleton
    if (skeletos.size()>0){
        
        for(int i=0; i<skeletos.size(); i++){
            if (skeletos[i]->getId()==skel_index){
                neck=skeletos[i]->pt_neck->Get_coords();
                if (neck.x*ofGetWidth()>ofGetWidth()/10 && neck.x*ofGetWidth()<ofGetWidth()*9/10){
                    
                    
                    skeletos[i]->draw();
                }
                
                
            }
        }
        
    } else{
        for(int i=0; i<skeletos.size(); i++){
            
            // skeletos[i]->draw();
        }
    }
    
    
    text1.drawString("Press 'i' to access info/control panel", ofGetWidth()-350, ofGetHeight()-10);
    
  if (ofGetElapsedTimeMillis()>2500) {
      
    if (ofGetElapsedTimeMillis()-feed_gestrecord<2000) {
        ofSetColor(255, 0, 0);
        
        text.drawString("Saving Gesture to File", ofGetWidth()/2, ofGetHeight()-30);
    }
    
    if (ofGetElapsedTimeMillis()-feed_drawmode<2000) {
        ofSetColor(255, 0, 0);
        text.drawString("Drawing Mode", ofGetWidth()/2, ofGetHeight()-30);
    }
    
    if (ofGetElapsedTimeMillis()-feed_trainingHmm<2000) {
        ofSetColor(255, 0, 0);
        text.drawString("Training Gesture Model", ofGetWidth()/2, ofGetHeight()-30);
    }

    
  }

    
    
    if (SavetoFile) {
        
        
        if (ofGetElapsedTimeMillis()-tempo_savefile>1500) {
            tempo_savefile=ofGetElapsedTimeMillis();
            ofSetColor(0, 0, 0);
            text.drawString("Saving to File", 10, ofGetHeight()-10);
        }
        if (ofGetElapsedTimeMillis()-tempo_savefile<1000)
        {
            ofSetColor(255, 0, 0);
            text.drawString("Saving to File", 10, ofGetHeight()-10);
            
        }
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case '0':
            gestnum=0;
            //capture=true;
            //cout<<"capture ON"<<endl;
            break;
        case '1':
            gestnum=1;
            //capture=true;
            //cout<<"capture ON"<<endl;
            break;
            
        case '2':
            gestnum=2;
            //capture=false;
            //add_to_gestures=true;
            break;
            
        case '3':
            gestnum=3;
            //clear_history=true;
            //cout<<"clear history"<<endl;
            break;
        case '4':
            gestnum=4;
            break;
        case '5':
            gestnum=5;
            break;
        case '6':
            gestnum=6;
            break;
        case '7':
            gestnum=7;
            break;
        case '8':
            gestnum=8;
            break;
        case '9':
            gestnum=9;
            break;
        case 'd':
            dtwMode=!dtwMode;
            cout<<"DTW Mode "<<dtwMode<<endl;
            break;
        case 'h':
            hmmMode=!hmmMode;
            cout<<"Hmm Mode "<<hmmMode<<endl;
            break;
        case 'r':
            feed_drawmode=ofGetElapsedTimeMillis();
            hmmMode=false;
            dtwMode=false;
            drawmode=true;
            cout<<"draw Mode"<<endl;
            break;
        case 'c':
            clear_history=true;
            gest_load.clear();
            break;
        case 's':
            SavetoFile=!SavetoFile;
            cout<<"SAvetoFile is "<<SavetoFile<<endl;
            break;
        case 'g':
            
            feed_gestrecord=ofGetElapsedTimeMillis();
            SaveGestureToFile=true;
            cout<<"SAveGesturetoFile"<<endl;
            break;
        case 'i':
            show_gui=!show_gui;
            pt_gui->gui1->toggleVisible();
            
            break;
        case 'j':
            trainMode=!trainMode;
            
            break;

            
        case 't':
            if (hmmMode==true) {
                
              // cout<<"im in T"<<endl;
                //feed_trainingHmm=ofGetElapsedTimeMillis();
                
                
                for (int j=0; j<skeletos.size(); j++) {
                    if (skeletos[j]->getId()==skel_index)
                        ignore=true;
                    
                    if (LEFTHAND==true) {
                     trigger_gesture=skeletos[j]->pt_handL->Calculate_HMM();
                    }
                    if (RIGHTHAND==true) {
                    trigger_gesture=skeletos[j]->pt_handR->Calculate_HMM();
                    }
                    
                    
                }
                
                cout<<"triggering gesture "<<trigger_gesture<<endl;
                ofxOscMessage m;
                m.setAddress("/Gesture");
                //m.addStringArg("handLV");
                m.addIntArg(trigger_gesture);
                oscOut.sendMessage(m);
                m.clear();

            }

            if (dtwMode==true) {
                
                // cout<<"im in T"<<endl;
                //feed_trainingHmm=ofGetElapsedTimeMillis();
                
                
                for (int j=0; j<skeletos.size(); j++) {
                    if (skeletos[j]->getId()==skel_index)
                        ignore=true;
                    
                    if (LEFTHAND==true) {
                        skeletos[j]->pt_handL->Calculate_DTW();
                    }
                    if (RIGHTHAND==true) {
                        skeletos[j]->pt_handR->Calculate_DTW();
                    }
                    
                }
            }

            
            
            break;
            
        case ' ':
            if (hmmMode==true) {
                
                feed_trainingHmm=ofGetElapsedTimeMillis();
                
                
                for (int j=0; j<skeletos.size(); j++) {
                    if (skeletos[j]->getId()==skel_index)
                        ignore=true;
                    
                    if (LEFTHAND==true) {
                         skeletos[j]->pt_handL->TrainHmm();
                    }
                    if (RIGHTHAND==true) {
                        skeletos[j]->pt_handR->TrainHmm();
                    }

                }
                
            }
            
            if (dtwMode==true) {
                
               // feed_trainingHmm=ofGetElapsedTimeMillis();
                
                
                for (int j=0; j<skeletos.size(); j++) {
                    if (skeletos[j]->getId()==skel_index)
                        ignore=true;
                    
                    if (LEFTHAND==true) {
                        skeletos[j]->pt_handL->TrainDtw();
                    }
                    if (RIGHTHAND==true) {
                        skeletos[j]->pt_handR->TrainDtw();
                    }
                    
                }
                
            }

            
    }
    
    /*
    //press 1 to record a new gesture and 2 to stop recording
    if(key == 'f')
        ofToggleFullscreen();
    
    
    if(key == '1'){
        
        gestnum=1;
        //capture=true;
        cout<<"capture ON"<<endl;
    }
    
    if(key == '2'){
        
        //capture=false;
		//add_to_gestures=true;
            cout<<"capture OFF"<<endl;
    }
    
    //press 3 to clear the gestures recorded
    if(key == '3'){
        clear_history=true;
        cout<<"clear history"<<endl;
    }
    
    if(key == 'd'){
        
        dtwMode=true;
        cout<<"DTW Mode"<<endl;
    }
    if(key == 'h'){
        
        hmmMode=true;
        cout<<"Hmm Mode"<<endl;
    }

    
    if(key == 'c'){
        hmmMode=false;
        dtwMode=false;
        cout<<"draw Mode"<<endl;
    }
    if(key == 's'){
        
        SavetoFile=!SavetoFile;
        cout<<"SAvetoFile is "<<SavetoFile<<endl;
    }
    if(key == 'g'){
        
        SaveGestureToFile=true;
        cout<<"SAveGesturetoFile"<<endl;
    }

    */
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if (show_gui==false){
        
        if (button==0) {
        capture=true;
        cout<<"capture ON"<<endl;
        }
        
        if (button==2) {
            delete_last=true;
        }
    }
   }

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if (show_gui==false) {
        
        if (button==0) {
            capture=false;
            cout<<"capture OFF"<<endl;
            add_to_gestures=true;
            
            for (int j=0; j<skeletos.size(); j++) {
                if (skeletos[j]->getId()==skel_index)
                    
                    
                    if (LEFTHAND==true) {
                        skeletos[j]->pt_handL->Test_coordDist();
                    }
                if (RIGHTHAND==true) {
                    skeletos[j]->pt_handR->Test_coordDist();
                }
                
            }
            if (trainMode==false) {
                // cout<<"keypressed"<<endl;
                keyPressed('t');
            }
            
        }
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo info){
    ignore=true;
    
    if( info.files.size() > 0 ){
        dragPt = info.position;
        
        //draggedImages.assign( info.files.size(), ofImage() );
       // for(int k = 0; k < info.files.size(); k++){
            //cout<<info.files[k]<<endl;
            // draggedImages[k].loadImage(info.files[k]);
       // }
    }
    
    //Path to the comma delimited file
    string filePath = info.files[0];
    
    
    //Load file placed in bin/data
    ofFile file(filePath);
    
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    
    ofBuffer buffer(file);
    
    //Read file line by line
    while (!buffer.isLastLine()) {
        
        string line = buffer.getNextLine();
        
        //Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        if (line.empty() && auxVec.size()>3) {
            
            gest_load.push_back(auxVec);
            auxVec.clear();
            //cout<<"linha vazia ";
            //cout<<auxVec.size()<<" "<<gest_load.size()<<endl;
            
        }
        
        if (words.size()>4) {
            
            aux.x=ofToFloat(words[1]);
            aux.y=ofToFloat(words[2]);
            aux.z=ofToFloat(words[3]);
            aux.w=ofToInt(words[4]);
            
            auxVec.push_back(aux);
        }
        
        //if (auxVec.size()>4) {
        //    gest_load.push_back(auxVec);
        //}
        
    }
    
    for (int i=0; i<gest_load.size(); i++) {
        
       // for (int j=0; j<gest_load[i].size(); j++) {
       //     cout<<gest_load[i][j]<<endl;
       // }
       // 
        //cout<<"testing "<<i<<endl;
        
       // vector<ofVec4f> teste;
       // teste.push_back(aux);
        add_to_gestures=false;
        
        for (int j=0; j<skeletos.size(); j++) {
            if (skeletos[j]->getId()==skel_index)
                skeletos[j]->pt_handL->Set_Gestos(gest_load[i]);
        }
       }
    ignore=false;
     gest_load.clear();
    
    // for (int i=0; i<words.size(); i++) {
    //     cout<<ofToString(words[i])<<endl;
    
    //}
    
    
}


