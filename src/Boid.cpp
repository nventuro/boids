#include "Boid.h"

#include "ofMath.h"
#include "ofGraphics.h"

void Boid::setup(int w, int h, float maxDist, int behaviourPeriod) {
    maxX = w;
    maxY = h;

    this->maxDist = maxDist;
    this->behaviourPeriod = behaviourPeriod;

    pos.x = ofRandom(maxX);
    pos.y = ofRandom(maxY);

    speed.x = ofRandom(1);
    speed.y = ofRandom(1);
    speed = speed.getNormalized();
}

void Boid::update(std::vector<Boid> &flock) {
    pos += speed;

    if (pos.x > maxX) {
        pos.x = maxX;
        speed.x *= -1;
    }
    else if (pos.x < 0) {
        pos.x = 0;
        speed.x *= -1;
    }

    if (pos.y > maxY) {
        pos.y = maxY;
        speed.y *= -1;
    }
    else if (pos.y < 0) {
        pos.y = 0;
        speed.y *= -1;
    }
}

void Boid::draw(void) {
    ofSetColor(ofColor::white);
    ofCircle(pos, 3);
}

int Boid::getNextID(void) {
    return idGen++;
}

int Boid::idGen;
