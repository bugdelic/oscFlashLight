#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"

#define OSC_RECEIVER_PORT 2192

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofxSyphonServer mainOutputSyphonServer;
        ofxSyphonServer individualTextureSyphonServer;
        ofxSyphonClient mClient;

        ofxPanel gui;
        ofxIntSlider pointX, pointY;
        ofxIntSlider widthX, widthY;
        ofxColorSlider flashColor;
        ofxIntSlider flashCount;
        ofxIntSlider flashTiming;
        bool showMenu = true;
    
        ofxOscReceiver    oscReceiver;

        int flashCounter = 0;
        bool isFlashing = false;
};
