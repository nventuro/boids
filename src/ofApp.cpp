#include "ofApp.h"
#include "Settings.h"

void ofApp::setup() {
    ofSeedRandom();

    behaviours.clear();
    // For each boid type, there are behaviours
    for (std::map<BoidMisc::Type, std::vector<Settings::Behaviour> >::iterator bt_it = Settings::behaviourType.begin(); bt_it != Settings::behaviourType.end(); ++bt_it) {
        behaviours.insert(std::make_pair<BoidMisc::Type, std::vector<Behaviour*> > (bt_it->first, std::vector<Behaviour*>()));

        // We create each behaviour, and configure it accordingly
        for (std::vector<Settings::Behaviour>::iterator beh_it = bt_it->second.begin(); beh_it != bt_it->second.end(); ++beh_it) {
            behaviours[bt_it->first].push_back(Behaviour::createFromName(beh_it->typeName));

            behaviours[bt_it->first].back()->setWeight(beh_it->weight);
            behaviours[bt_it->first].back()->setInfluencerType(beh_it->influencerType);

            // Test for the different derived types (some of which have special configuration that needs to be performed)
            Separation* sep = dynamic_cast<Separation*>(behaviours[bt_it->first].back());
            if (sep) {
                sep->setNearnessSelectivity(beh_it->nearnessSelectivity);
            }
        }
    }

    flock.clear();
    // For each boid type, there are boids with different configuration (but they all are part of the flock)
    for (std::map<BoidMisc::Type, Settings::Boid>::iterator b_it = Settings::boidType.begin(); b_it != Settings::boidType.end(); ++b_it) {
        for (int i = 0; i < b_it->second.amount; ++i) {
            flock.push_back(Boid());
            flock.back().setup(Settings::width, Settings::height, b_it->first, b_it->second.maxDist, b_it->second.period, b_it->second.maxSpeed, behaviours[b_it->first]);
            flock.back().setupGraphics(b_it->second.graphics.color, b_it->second.graphics.size);
        }
    }

    ofSetFrameRate(Settings::fps);
}

void ofApp::update() {
    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->calculateUpdate(flock);
    }

    for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
        boid_it->update();
    }
}

void ofApp::draw() {
    ofBackground(Settings::graphics.backgroundColor);

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
