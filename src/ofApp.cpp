#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    smileyImage.loadImage("smiley.png");
    
    videoGrabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);

    videoCvColorImage.allocate(videoGrabber.width, videoGrabber.height);
    videoCvGrayscaleImage.allocate(videoGrabber.width, videoGrabber.height);
    
    cvHaarfinder.setup("haarcascade_frontalface_default.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();

    if (videoGrabber.isFrameNew()) {
        videoCvColorImage.setFromPixels(videoGrabber.getPixels(), CAM_WIDTH, CAM_HEIGHT);
        videoCvColorImage.convertRgbToHsv();
        videoCvColorImage.convertToGrayscalePlanarImage(videoCvGrayscaleImage, 2);
        cvHaarfinder.findHaarObjects(videoCvGrayscaleImage, 100, 100);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //videoGrabber.draw(CAM_WIDTH, 0, -CAM_WIDTH, CAM_HEIGHT);
    videoCvGrayscaleImage.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());
    
    ofScale((float)ofGetWidth() / CAM_WIDTH, (float)ofGetHeight() / CAM_HEIGHT);
    for(int i = 0; i < cvHaarfinder.blobs.size(); i++) {
        smileyImage.draw(CAM_WIDTH - cvHaarfinder.blobs[i].boundingRect.x,
                         cvHaarfinder.blobs[i].boundingRect.y,
                         -cvHaarfinder.blobs[i].boundingRect.width,
                         cvHaarfinder.blobs[i].boundingRect.height);
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
