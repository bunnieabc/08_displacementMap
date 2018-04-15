#include "ofApp.h"
float pxs;
//--------------------------------------------------------------
void ofApp::setup(){
    
#ifdef TARGET_OPENGLES
	shader.load("shadersES2/shader");
#else
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader");
        cout << "test" << "\n";
	}else{
		shader.load("shadersGL2/shader");
        cout << "test2" << "\n";
	}
#endif

    img.allocate(320, 160, OF_IMAGE_COLOR);
    img.update();
    bumpmap.load("test_tex.jpg");
    float width     = 300;
    float height    = ofGetHeight() * .35;
    sphere.setRadius( width );
    sphere.setResolution(100);
    sphere.mapTexCoordsFromTexture(img.getTexture());
    quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    img2.allocate(320, 160, OF_IMAGE_COLOR);
    img2.update();
    pxs = ofRandom(2,11);
}

//--------------------------------------------------------------
void ofApp::update(){
    float noiseScale = ofMap(mouseX, 0, ofGetWidth(), 0, 0.1);
    float noiseVel = ofGetElapsedTimef();
	ofPixels pixels = img.getPixels();
    int w = img.getWidth();
    int h = img.getHeight();
    
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            int i = y * w + x;
            float noiseVelue = ofNoise(x * noiseScale, y * noiseScale, noiseVel);
            float valc = ofMap(255 * noiseVelue, 0, 255, 200, 255);
            ofColor c(valc, valc, ofRandom(100, 255));
            pixels.setColor(x,y, c);
        }
    }
    
    float noiseScale2 = ofMap(mouseY, 0, ofGetWidth(), 0, 0.6);
    int hasBuilding = ofRandom(0,1);
    
    for(int y=0; y<h; y+= 14) {
        for(int x=0; x<w; x+= 14) {
            float val = ofRandom(0,200);
            float noiseVelue = ofNoise(x * noiseScale, y * noiseScale, noiseVel);
            float noiseVelue_pxs = ofNoise(x * 0.5, y * 0.5, noiseVel);
            for(int j = 0; j< 15* noiseVelue_pxs * 0.9; j++) {
                for(int k = 0; k< 15* noiseVelue_pxs * 0.9; k++){
                    ofColor c2(255 * noiseVelue);
                    pixels.setColor(x + j, y + k, c2);
                }
            }
        }
    }
	img.setFromPixels(pixels);
    img.update();
    
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            int i = y * w + x;
            float r = ofMap(x, 0, w, 0, 255);
            float g = ofMap(y, 0, h, 0, 255);
            float b = 255;
            float a = 1.0;
            ofColor c(r , g, b);
            pixels.setColor(x,y, c);

        }
    }
    img2.setFromPixels(pixels);
    img2.update();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    // bind our texture. in our shader this will now be tex0 by default
    // so we can just go ahead and access it there.
    img.getTexture().bind();
    
    shader.begin();
    shader.setUniformTexture("colormap", img2, 2);
    shader.setUniform1f("maxHeight", mouseX);
    shader.setUniform1f("iTime", ofGetElapsedTimef());
    shader.setUniform2f("iResolution", (float)ofGetWidth(), (float)ofGetHeight());
    
    ofPushMatrix();
    
    // translate plane into center screen.
    float tx = ofGetWidth() / 2;
    float ty = ofGetHeight() / 2;
    ofTranslate(tx, ty);

    // the mouse/touch Y position changes the rotation of the plane.
    float percentY = mouseY / (float)ofGetHeight();
    float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
    //ofRotate(rotation, 1, 0, 0);
    ofRotateY(360 * sinf(float(ofGetFrameNum())/500.0f));
    ofRotate(-90,1,0,0);
    
    sphere.draw(ofPolyRenderMode::OF_MESH_FILL);
    //sphere.drawWireframe();
    ofPopMatrix();
    
    shader.end();

    ofSetColor(ofColor::white);
    //img.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
