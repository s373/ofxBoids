#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// num, center x, center y, center z, dev
	flock.setup(500, ofGetWidth()/2, ofGetHeight()/2,-ofGetWidth()/2, 100);

	flock.setBounds(0,0,-ofGetWidth(),ofGetWidth(), ofGetHeight(),0);
	flock.setBoundmode(1)->setDt(2.5);

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	ofBackground(0);
	ofSetColor(255,100);
}

//--------------------------------------------------------------
void ofApp::update(){

	flock.update();

	if(ofGetFrameNum()%240==0){
	    flock.removeBoid(0);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	for(int i=0; i<flock.size(); i++){
	    Boid3d * b = flock.get(i);

   		ofPushMatrix();
    	ofTranslate(b->x, b->y, b->z);
    	ofRect(-5,-5,10,10);
    	ofPopMatrix();
	    
	    float lm = 10.f;
	    ofLine(b->x, b->y, b->z, b->x + b->vx*lm, b->y + b->vy*lm, b->z + b->vz*lm);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(button==0)
    	flock.add(x, y, -ofGetWidth()/2);
	else
    	flock.removeBoid(0);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
