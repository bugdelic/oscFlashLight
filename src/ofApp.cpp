#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetFrameRate(30);
    ofSetBackgroundAuto(true);

    // syphon 出力用
    mainOutputSyphonServer.setName("Screen Outputh");
    mClient.setup();
    mClient.setApplicationName("oscFlashLight");
    mClient.setServerName("");
    
    // OSC用
    oscReceiver.setup(OSC_RECEIVER_PORT);
    
    // GUI用
    gui.setup();

    gui.add(pointX.setup("start position X", 200, 0, ofGetWidth()));
    gui.add(pointY.setup("start position Y", 200, 0, ofGetHeight()));
    gui.add(printInterval.setup("print iterval", 5, 1, 60));
    gui.add(widthX.setup("draw width", 200, 0, ofGetWidth()));
    gui.add(widthY.setup("draw height", 200, 0, ofGetHeight()));
    gui.add(flashCount.setup("flash count", 100, 1, 300));
    gui.add(flashTiming.setup("flash % frame count", 3, 1, 30));
    
    // 点滅のデフォルトの色
    ofColor minColor = ofColor(0, 0, 0, 255);
    ofColor maxColor = ofColor(255,255,255,255);
    gui.add(flashColor.setup("flash color", maxColor, minColor, maxColor));
    
    isFlashing = false;
    flashCounter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!isFlashing) {
        while(oscReceiver.hasWaitingMessages()) {
            ofxOscMessage message;
            oscReceiver.getNextMessage(&message);
            
            // flash指示
            if (message.getAddress() == "/osc/flashlight") {
                if (message.getNumArgs() > 0) {
                    printInterval = message.getArgAsInt(0);
                }
                if (message.getNumArgs() > 3) {
                    flashColor = ofColor(message.getArgAsInt(1), message.getArgAsInt(2), message.getArgAsInt(3));
                }
                sleep(printInterval);
                isFlashing = true;
                flashCounter = 0;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0);
    
    if (showMenu) {
        ofSetColor(0, 0, 0);
        gui.draw();
    }
    
    if (isFlashing) {
        if (ofGetFrameNum() % flashTiming == 0) {
            ofSetColor(flashColor);
            ofDrawRectangle(pointX, pointY, widthX, widthY);
            flashCounter++;
        }
        
        if (flashCounter >= flashCount) {
            isFlashing = false;
        }
    }
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'h':
            showMenu = !showMenu;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
