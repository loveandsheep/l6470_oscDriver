#pragma once

#include "ofMain.h"
#include "ofxOscReceiver.h"
#include "ofxKsmrRPiToL6470.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	
	ofxKsmrRPiToL6470	driver;
	ofxOscReceiver		receiver;
	
};
