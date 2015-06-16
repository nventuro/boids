#pragma once

#include "ofMain.h"

#include "Boid.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    std::vector<Boid> flock;
};
