#include "ofApp.h"

#include "ofxIldaRenderTarget.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofPolyline circlePolyline;
    circlePolyline.arc(ofPoint(0, 0, 0), 1, 1, 0, 360, true, 20);

    ofPolyline leftEyePolyline;
    leftEyePolyline.arc(ofPoint(0.4, -0.3, 0), 0.1, 0.2, 0, 360, true, 4);

    ofPolyline rightEyePolyline;
    rightEyePolyline.arc(ofPoint(-0.4, -0.3, 0), 0.1, 0.2, 0, 360, true, 4);

    ofPolyline mouthPolyline;
    mouthPolyline.arc(ofPoint(0, 0, 0), 0.8, 0.8, 30, 150, true, 8);

    smileyPolylines.push_back(circlePolyline);
    smileyPolylines.push_back(leftEyePolyline);
    smileyPolylines.push_back(rightEyePolyline);
    smileyPolylines.push_back(mouthPolyline);
    
    videoGrabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);
    
    videoCvColorImage.allocate(videoGrabber.width, videoGrabber.height);
    videoCvGrayscaleImage.allocate(videoGrabber.width, videoGrabber.height);
    
    cvHaarFinder.setup("haarcascade_frontalface_default.xml");
    
    ildaFrame.params.output.transform.doFlipY = true;
    ildaFrame.polyProcessor.params.targetPointCount = 2000;
    
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
        cvHaarFinder.findHaarObjects(videoCvGrayscaleImage, 80, 80);

        ildaFrame.clear();

        unsigned char smileyColorHue = 0;
        for(int i = 0; i < cvHaarFinder.blobs.size(); i++) {
            float x = (cvHaarFinder.blobs[i].centroid.x / CAM_WIDTH);
            float y = (cvHaarFinder.blobs[i].centroid.y / CAM_HEIGHT);
            
            for (int j = 0; j < smileyPolylines.size(); j++) {
                vector<ofPoint> points;
                vector<ofPoint> vertices = smileyPolylines[j].getVertices();
                for (int k = 0; k < vertices.size(); k++) {
                    points.push_back(ofPoint(x + vertices[k].x * cvHaarFinder.blobs[i].boundingRect.width / CAM_WIDTH / 2,
                                             y + vertices[k].y * cvHaarFinder.blobs[i].boundingRect.height / CAM_HEIGHT / 2)
                                     );
                }
                ildaFrame.addPoly(points, ofColor::fromHsb(smileyColorHue,255,255));
            }
            
            smileyColorHue += 32;
        }
    
        ildaFrame.update();
    }

    etherdream.setPoints(ildaFrame);
}

//--------------------------------------------------------------
void ofApp::draw(){
    videoCvGrayscaleImage.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());

    ildaFrame.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());
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
