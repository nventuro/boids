#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

#include "Boid.h"
#include "Behaviour.h"

#include <vector>
#include <map>

class ofApp : public ofBaseApp
{
public:
    void setup(void);
    void setupGUI(void);
    void update(void);
    void draw(void);
    void exit(void);

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    std::vector<Boid> flock;
    std::map<BoidMisc::Type, std::vector<Behaviour*> > behaviours;

    ofxDatGui *gui;
};
