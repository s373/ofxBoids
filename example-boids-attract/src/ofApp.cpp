#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofEnableAlphaBlending();

	// num, center x, center y, dev
	flock.setup(250, ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4 );

	flock.setBounds(0,0,ofGetWidth(), ofGetHeight());
	flock.setBoundmode(1);

	// make attrPts
	for(int i=0; i<10; i++) {   
	     float x = ofRandom(ofGetWidth());
	     float y = ofRandom(ofGetHeight());
	     float force = ofRandom (-125,125);
	     float dist = ofRandom(100,200); 
	     flock.addAttractionPoint(x,y,force,dist);
	  }
}

//--------------------------------------------------------------
void ofApp::update(){

	flock.update(   );


}

//--------------------------------------------------------------
void ofApp::draw(){
	
 	//view attrpoints
	ofColor attrColor(100,255,0);
	ofColor repelColor(255,128,0); 
	  
	for(int i=0; i<flock.attractionPoints.size(); i++){   
	    AttractionPoint2d * ap = flock.attractionPoints[i];            
	    ofSetColor( ap->force > 0 ? attrColor : repelColor, 100);
	    ofRect(ap->x, ap->y, ap->sensorDist, ap->sensorDist);
	    ofRect(ap->x, ap->y, 5, 5);    
	  }


	ofSetColor(0);
	for(int i=0; i<flock.size(); i++){
	    Boid2d * b = flock.get(i);

	    ofRect(b->x, b->y, 5,5);
	    float lm = 10.f;
	    ofLine(b->x, b->y, b->x + b->vx*lm, b->y + b->vy*lm);
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
    	flock.add(x, y);
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
