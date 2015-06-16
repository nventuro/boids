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

    speed.x = ofRandom(1);
    speed.y = ofRandom(1);
    speed = speed.getNormalized();
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

        std::vector<ofVec2f> desiredSpeeds;
        for (std::vector<Behaviour*>::iterator beh_it = behaviours.begin(); beh_it != behaviours.end(); ++beh_it) {
            desiredSpeeds.push_back((*beh_it)->apply(this, nearbyBoids));
        }

        for (std::vector<ofVec2f>::iterator dspeed_it = desiredSpeeds.begin(); dspeed_it != desiredSpeeds.end(); ++dspeed_it) {
            speed += *dspeed_it;
        }

        speed /= desiredSpeeds.size() + 1;
    }

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
