#include "ofApp.h"

void ofApp::setup() {
    for (int i = 0; i < 30; ++i) {
        flock.push_back(Boid());
        flock.back().setup(640, 480);
    }
}

void ofApp::update() {
    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->update(flock);
    }
}

void ofApp::draw() {
    ofBackground(ofColor::black);

    ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 10, 10);

    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->draw();
    }
}

void ofApp::exit() {
}

void ofApp::keyPressed(int key) {

}

void ofApp::mousePressed(int x, int y, int button) {

}
