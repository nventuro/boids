#include "Boid.h"

#include "Behaviour.h"

#include "ofMath.h"
#include "ofGraphics.h"

void Boid::setup(int w, int h, float maxDist, int behaviourPeriod) {
    maxX = w;
    maxY = h;

    this->maxDist = maxDist;
    this->behaviourPeriod = behaviourPeriod;

    pos.x = ofRandom(maxX);
    pos.y = ofRandom(maxY);

    speed.x = ofRandom(-1, 1);
    speed.y = ofRandom(-1, 1);
    speed = speed.getNormalized();

    accel.x = 0;
    accel.y = 0;
}

void Boid::update(std::vector<Boid> &flock) {
    if ((++noBehaviourUpdates) > behaviourPeriod) {
        noBehaviourUpdates = 0;

        float sqMaxDist = maxDist * maxDist;

        std::vector<Boid*> nearbyBoids;
        for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
            if (pos.squareDistance(boid_it->getPos()) < sqMaxDist) {
                nearbyBoids.push_back(&(*boid_it));
            }
        }

        std::vector<ofVec2f> desiredAccels;
        for (std::vector<Behaviour*>::iterator beh_it = behaviours.begin(); beh_it != behaviours.end(); ++beh_it) {
            desiredAccels.push_back((*beh_it)->apply(this, nearbyBoids));
        }

        for (std::vector<ofVec2f>::iterator daccel_it = desiredAccels.begin(); daccel_it != desiredAccels.end(); ++daccel_it) {
            accel += *daccel_it;
        }
        accel /= desiredAccels.size() + 1;
    }

    speed += accel;
    pos += speed;

    if (pos.x > maxX) {
        pos.x -= maxX;
    }
    else if (pos.x < 0) {
        pos.x += maxX;
    }

    if (pos.y > maxY) {
        pos.y -= maxY;
    }
    else if (pos.y < 0) {
        pos.y += maxY;
    }
}

void Boid::draw(void) {
    ofSetColor(ofColor::white);
    ofCircle(pos, 2);
}

ofVec2f Boid::getPos(void) {
    return pos;
}

ofVec2f Boid::getSpeed(void) {
    return speed;
}

int Boid::getNextID(void) {
    return idGen++;
}

int Boid::idGen;
