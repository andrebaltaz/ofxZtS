//
//  Gui.h
//  allAddonsExample
//
//  Created by Andre Baltazar on 05/08/13.
//
//
#include "ofxUi.h"
#include "Globals.h"

#ifndef allAddonsExample_Gui_h
#define allAddonsExample_Gui_h

class Gui{

public:
ofxUICanvas *gui1;
void guiEvent(ofxUIEventArgs &e);

void setup();
void update();
void draw();
    Gui();
    ~Gui();
    
    
private:

    int red, green, blue;
    	bool bdrawGrid; 
    
    float dim ;
	float xInit;
    float length;
	bool hideGUI;

};


#endif
