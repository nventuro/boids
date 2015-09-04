#include "ofApp.h"
#include "Settings.h"

void ofApp::setup() {
    ofSeedRandom();

    flock.clear();
    for (std::map<BoidMisc::Type, Settings::BoidTypeData>::iterator b_it = Settings::boidType.begin(); b_it != Settings::boidType.end(); ++b_it) {
        for (int i = 0; i < b_it->second.amount; ++i) {
            flock.push_back(Boid());
            flock.back().setup(Settings::width, Settings::height, b_it->first, b_it->second.maxDist, b_it->second.period, b_it->second.maxSpeed);
        }
    }

    ofSetFrameRate(Settings::fps);
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
