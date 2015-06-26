#include "ofApp.h"

void ofApp::setup() {
    ofSeedRandom();

    for (int i = 0; i < 300; ++i) {
        flock.push_back(Boid());
        flock.back().setup(1280, 720, BoidMisc::REGULAR, 70, 1);
    }
    
    for (int i = 0; i < 2; ++i) {
        flock.push_back(Boid());
        flock.back().setup(1280, 720, BoidMisc::PREDATOR, 100, 1);
    }
}

void ofApp::update() {
    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->update(flock);
    }
}

void ofApp::draw() {
    ofBackground(ofColor::black);

    ofSetColor(ofColor::white);
    ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 10, 10);

    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->draw();
    }
}

void ofApp::exit() {
    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->exit();
    }
}

void ofApp::keyPressed(int key) {

}

void ofApp::mousePressed(int x, int y, int button) {

}
