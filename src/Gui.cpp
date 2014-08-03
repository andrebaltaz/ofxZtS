//
//  Gui.cpp
//  allAddonsExample
//
//  Created by Andre Baltazar on 05/08/13.
//
//

#include "Gui.h"

 Gui::Gui(){

    setup();

}

Gui::~Gui(){




}


void Gui::setup(){

//    float dim = 16;
//	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
//    float length = 320-xInit;
//	
//    gui = new ofxUICanvas(10,50,length+xInit*2.0,50);
//	gui->addWidgetDown(new ofxUILabel("IP de destino", OFX_UI_FONT_LARGE));
//    
//    gui->addWidgetDown(new ofxUILabel("Change IP", OFX_UI_FONT_MEDIUM));
//	gui->setWidgetFontSize(OFX_UI_FONT_LARGE);
//    gui->addTextInput("TEXT INPUT", "", length-xInit)->setAutoClear(true);

    
     red = 150;
     blue = 150;
     green = 150;
	
	 dim = 16;
	xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    length = 255-xInit;
	hideGUI = false;
	
    vector<string> names;
	names.push_back("Right_Hand");
	names.push_back("Left_Hand");
	//names.push_back("ETC");

    vector<string> modes;
    modes.push_back("Draw");
    modes.push_back("DTW");
    modes.push_back("HMM");
    
    gui1 = new ofxUICanvas(0, ofGetHeight()/2, length+xInit, ofGetHeight());
	//gui1->addWidgetDown(new ofxUILabel("PANEL 1: BASICS", OFX_UI_FONT_LARGE));
    gui1->addWidgetDown(new ofxUILabel("Press 'i' to Hide GUIs", OFX_UI_FONT_LARGE));
    gui1->drawFillHighlight();
//    gui1->addSpacer(length-xInit, 2);
//	gui1->addWidgetDown(new ofxUILabel("H SLIDERS", OFX_UI_FONT_MEDIUM));
//	gui1->addSlider("RED", 0.0, 255.0, red, length-xInit, dim);
//	gui1->addSlider("GREEN", 0.0, 255.0, green, length-xInit,dim);
//	gui1->addSlider("BLUE", 0.0, 255.0, blue, length-xInit,dim);
    
//    gui1->addSpacer(length-xInit, 2);
//    gui1->addWidgetDown(new ofxUILabel("V SLIDERS", OFX_UI_FONT_MEDIUM));
//	gui1->addSlider("0", 0.0, 255.0, 150, dim, 160);
//	gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
//	gui1->addSlider("1", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("2", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("3", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("4", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("5", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("6", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("7", 0.0, 255.0, 150, dim, 160);
//	gui1->addSlider("8", 0.0, 255.0, 150, dim, 160);
//	gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui1->addSpacer(length-xInit, 2);
    gui1->addWidgetDown(new ofxUILabel("Choose Hand to control", OFX_UI_FONT_MEDIUM));
	gui1->addRadio("RADIO HORIZONTAL", names, OFX_UI_ORIENTATION_HORIZONTAL, dim, dim);
    //gui1->addRadio("RADIO VERTICAL", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    gui1->addSpacer(length-xInit, 2);
	//gui1->addWidgetDown(new ofxUILabel("BUTTONS", OFX_UI_FONT_MEDIUM));
	//gui1->addButton("HMM Mode", false, dim, dim);
	gui1->addWidgetDown(new ofxUILabel("Choose Function Mode", OFX_UI_FONT_MEDIUM));
    gui1->addRadio("RADIO VERTICAL", modes, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    //	gui1->addToggle( "Hmm Mode", false, dim, dim);
//    gui1->addToggle( "DTW Mode", false, dim, dim);
//    gui1->addToggle( "Draw Mode", false, dim, dim);
    
    gui1->addSpacer(length-xInit, 2);
    gui1->addWidgetDown(new ofxUILabel("Choose Thresholds", OFX_UI_FONT_MEDIUM));
	gui1->addSlider("HMM Thresh", -300.0, 0.0, hmmthreshold, length-xInit, dim);
    gui1->addSlider("DTW Thresh", 0.0, 5.0, dtwthreshold, length-xInit, dim);
    //gui1->addRangeSlider("RSLIDER", 0.0, 255.0, 50.0, 100.0, length-xInit,dim);
    
    gui1->addSpacer(length-xInit, 2);
    gui1->addWidgetDown(new ofxUILabel("IP to send triggers", OFX_UI_FONT_MEDIUM));
    gui1->addTextInput("TEXT INPUT2", "IP", length-xInit)->setAutoClear(false);
    gui1->addTextInput("TEXT INPUT2", "Port", length-xInit)->setAutoClear(false);
    //gui1->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM));
	//gui1->add2DPad("PAD", ofPoint(0,length-xInit), ofPoint(0,120), ofPoint((length-xInit)*.5,120*.5), length-xInit,120);
    gui1->addSpacer(length-xInit, 2);
    gui1->addWidgetDown(new ofxUILabel("Keyboard Shortcuts", OFX_UI_FONT_LARGE));
    gui1->addWidgetDown(new ofxUILabel("f: toggle fullscreen", OFX_UI_FONT_MEDIUM));
    gui1->addWidgetDown(new ofxUILabel("s: Record performance", OFX_UI_FONT_MEDIUM));
    gui1->addWidgetDown(new ofxUILabel("g: Record gesture", OFX_UI_FONT_MEDIUM));
    gui1->addWidgetDown(new ofxUILabel("d: DTW MODE", OFX_UI_FONT_MEDIUM));
    gui1->addWidgetDown(new ofxUILabel("h: HMM MODE", OFX_UI_FONT_MEDIUM));
    gui1->addWidgetDown(new ofxUILabel("r: Draw MODE", OFX_UI_FONT_MEDIUM));
    gui1->addWidgetDown(new ofxUILabel("c: Clear screen", OFX_UI_FONT_MEDIUM));
    
     ofAddListener(gui1->newGUIEvent,this,&Gui::guiEvent);
//    bdrawGrid = false;
//	bdrawPadding = false;
//	ofAddListener(gui1->newGUIEvent,this,&testApp::guiEvent);
//

}


void Gui::draw()
{
  
	//ofSetColor(150, 100, 100);
	//ofRect(0, ofGetHeight()/2, length+xInit, length+xInit);
    
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    
		ofPopStyle();
    
    ofSetRectMode(OF_RECTMODE_CENTER);
}


void Gui::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	cout << "got event from: " << name << endl;
	
	if(name == "DTW Thresh")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	//	cout << "RED " << slider->getScaledValue() << endl;
		dtwthreshold = slider->getScaledValue();
	}
    
    if(name == "Right_Hand")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		int value = toggle->getValue();
        if (value==1) {
            
            //a imagem e espelhada por isso abaixo esta trocado
            LEFTHAND=true;
            RIGHTHAND=false;
        }
	}
    if(name == "Left_Hand")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		int value = toggle->getValue();
        if (value==1) {
            
            //a imagem e espelhada por isso abaixo esta trocado
            LEFTHAND=false;
            RIGHTHAND=true;
        }
	}
    
    
    
    
	else if(name == "HMM Thresh")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
	//	cout << "GREEN " << slider->getScaledValue() << endl;
		hmmthreshold= slider->getScaledValue();
	}
	
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		cout << "BLUE " << slider->getScaledValue() << endl;
		blue = slider->getScaledValue();
	}
	else if(name == "DRAW GRID")
	{
		ofxUIButton *button = (ofxUIButton *) e.widget;
		bdrawGrid = button->getValue();
	}
	else if(name == "Draw")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		int value = toggle->getValue();
        if (value==1) {
            hmmMode=false;
            dtwMode=false;
        }
        
	}
    else if(name == "DTW")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		int value = toggle->getValue();
        if (value==1) {
            hmmMode=false;
            dtwMode=true;
        }
        
	}
    
    else if(name == "HMM")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		int value = toggle->getValue();
        if (value==1) {
            hmmMode=true;
            dtwMode=false;
        }
        
	}

    
    else if(name == "TEXT INPUT")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        string output = textinput->getTextString();
        cout << output << endl;
    }
    
    
    
}
