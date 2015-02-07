#pragma once

#include "ofMain.h"

#define CAM_WIDTH 1024
#define CAM_HEIGHT 1024

#include "ofxCvColorImage.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxCvHaarFinder.h"
#include "ofxIldaFrame.h"
#include "ofxIldaRenderTarget.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        ofImage smileyImage;
    
        ofVideoGrabber videoGrabber;

        ofxCvHaarFinder cvHaarfinder;
        ofxCvColorImage videoCvColorImage;
        ofxCvGrayscaleImage videoCvGrayscaleImage;
};
