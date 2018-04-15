#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

    ofShader shader, shaderBlurX, shaderBlurY, shaderGlow;
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    ofFbo fboBlurThreePass;
    //ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    ofImage img, img2;
    ofImage bumpmap;
    GLUquadricObj *quadric;
    int first = 0;
    ofFbo fbo;
};
