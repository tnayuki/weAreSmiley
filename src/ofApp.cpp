#include "ofApp.h"

#include "ofxIldaFrame.h"
#include "ofxIldaRenderTarget.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofImage smileyImage("smiley.png");

    ofxIlda::RenderTarget renderTarget;
    memset(&renderTarget.params, 0, sizeof(renderTarget.params));
    renderTarget.params.cv.doFindHoles = true;
    renderTarget.setup(smileyImage.getWidth(), smileyImage.getHeight());
    
    ofPushStyle();
    renderTarget.begin();
    ofClear(0);
    smileyImage.draw(0, 0);
    renderTarget.end();
    ofPopStyle();
    
    ofxIlda::Frame frame;
    memset(&frame.params, 0, sizeof(frame.params));
    frame.clear();
    renderTarget.update(frame);
    frame.update();
    
    smileyPoints = frame.getPoints();
    
    videoGrabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);
    
    videoCvColorImage.allocate(videoGrabber.width, videoGrabber.height);
    videoCvGrayscaleImage.allocate(videoGrabber.width, videoGrabber.height);
    
    cvHaarFinder.setup("haarcascade_frontalface_default.xml");
    
    etherdream.setup();
    etherdream.setPPS(30000);
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();
    
    if (videoGrabber.isFrameNew()) {
        videoCvColorImage.setFromPixels(videoGrabber.getPixels(), CAM_WIDTH, CAM_HEIGHT);
        videoCvColorImage.convertRgbToHsv();
        videoCvColorImage.convertToGrayscalePlanarImage(videoCvGrayscaleImage, 2);
        cvHaarFinder.findHaarObjects(videoCvGrayscaleImage, 100, 100);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    videoCvGrayscaleImage.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());

    vector<ofxIlda::Point> points;
    for(int i = 0; i < cvHaarFinder.blobs.size(); i++) {
        float x = (cvHaarFinder.blobs[i].centroid.x / CAM_WIDTH) - 0.5;
        float y = (cvHaarFinder.blobs[i].centroid.y / CAM_WIDTH) - 0.5;
        
        for (int j = 0; j < smileyPoints.size(); j++) {
            float px = (float)smileyPoints[j].x / 65535.0 * cvHaarFinder.blobs[i].boundingRect.width / CAM_WIDTH;
            float py = (float)smileyPoints[j].y / 65535.0 * cvHaarFinder.blobs[i].boundingRect.width / CAM_HEIGHT;
            
            ofCircle(ofGetWidth() - (x + px + 0.5) * ofGetWidth(), (y + py + 0.5) * ofGetHeight(), 2);

            points.push_back(ofxIlda::Point((x + px) * 65535.0, (y + py) * 65535.0, 65535, 65535, 65535, 65535);
        }
    }
    
    etherdream.addPoints(points);
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
