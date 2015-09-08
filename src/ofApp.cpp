#include "ofApp.h"
#include "Settings.h"

void ofApp::setup() {
    ofSeedRandom();

    behaviours.clear();
    // For each boid type, there are behaviours
    for (auto &type_behaviours_pair : Settings::behavioursByType) {
        behaviours.insert(std::make_pair(type_behaviours_pair.first, std::vector<Behaviour*>()));

        // We create each behaviour, and configure it accordingly
        for (auto &behaviour : type_behaviours_pair.second) {
            behaviours[type_behaviours_pair.first].push_back(Behaviour::createFromName(behaviour.typeName));

            behaviours[type_behaviours_pair.first].back()->setWeight(behaviour.weight);
            behaviours[type_behaviours_pair.first].back()->setInfluencerType(behaviour.influencerType);

            // Test for the different derived types (some of which have special configuration that needs to be performed)
            Separation* sep = dynamic_cast<Separation*>(behaviours[type_behaviours_pair.first].back());
            if (sep) {
                sep->setNearnessSelectivity(behaviour.nearnessSelectivity);
            }
        }
    }

    flock.clear();
    // For each boid type, there are boids with different configuration (but they all are part of the flock)
    for (auto &type_boid_pair : Settings::boidsByType) {
        for (int i = 0; i < type_boid_pair.second.amount; ++i) {
            flock.push_back(Boid());
            flock.back().setup(Settings::width, Settings::height, type_boid_pair.first, type_boid_pair.second.maxDist, type_boid_pair.second.period, type_boid_pair.second.maxSpeed, behaviours[type_boid_pair.first]);
            flock.back().setupGraphics(type_boid_pair.second.graphics.color, type_boid_pair.second.graphics.size);
        }
    }

    ofSetFrameRate(Settings::fps);
}

void ofApp::update() {
    for (auto &boid : flock) {
        boid.calculateUpdate(flock);
    }

    for (auto &boid : flock) {
        boid.update();
    }
}

void ofApp::draw() {
    ofBackground(Settings::graphics.backgroundColor);

    ofSetColor(ofColor::white);
    ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 10, 10);

    for (auto &boid : flock) {
        boid.draw();
    }
}

void ofApp::exit() {
    for (auto &boid : flock) {
        boid.exit();
    }
}

void ofApp::keyPressed(int key) {

}

void ofApp::mousePressed(int x, int y, int button) {

}
