#include "Boid.h"

#include "Behaviour.h"

#include "ofMath.h"
#include "ofGraphics.h"

Boid::Boid(void) {
    id = getNextID();
}

void Boid::setup(int w, int h, BoidMisc::Type type, float maxDist, int behaviourPeriod) {
    maxX = w;
    maxY = h;
    
    this->type = type;

    this->maxDist = maxDist;
    this->behaviourPeriod = behaviourPeriod;

    pos.x = ofRandom(maxX);
    pos.y = ofRandom(maxY);

    speed.x = ofRandom(-1, 1);
    speed.y = ofRandom(-1, 1);
    speed = speed.getNormalized() * 2;

    accel.x = 0;
    accel.y = 0;

    if (type == BoidMisc::REGULAR) {
        Separation* sep = new Separation();
        sep->setWeight(7);
        sep->setInfluencerType(BoidMisc::REGULAR);
        sep->setNearnessSelectivity(10);
        behaviours.push_back(sep);

        Alignment* alg = new Alignment();
        alg->setWeight(3);
        alg->setInfluencerType(BoidMisc::REGULAR);
        behaviours.push_back(alg);

        Cohesion* coh = new Cohesion();
        coh->setWeight(2);
        coh->setInfluencerType(BoidMisc::REGULAR);
        behaviours.push_back(coh);

        Cage* cage = new Cage();
        cage->setWeight(1);
        cage->setThreshold(80);
        cage->setInfluencerType(BoidMisc::REGULAR);
        behaviours.push_back(cage);
        
        Separation* esc = new Separation(); // Escape from predators
        esc->setWeight(12);
        esc->setInfluencerType(BoidMisc::PREDATOR);
        esc->setNearnessSelectivity(0.5);
        behaviours.push_back(esc);
    }
    else if (type == BoidMisc::PREDATOR) {
    }
    else {
        ofLogNotice("boid", "unexpected boid type at setup.");
    }
}

void Boid::update(std::vector<Boid> &flock) {
    if ((++noBehaviourUpdates) >= behaviourPeriod) {
        noBehaviourUpdates = 0;

        float sqMaxDist = maxDist * maxDist;

        std::vector<Boid*> nearbyBoids;
        for (std::vector<Boid>::iterator boid_it = flock.begin(); boid_it != flock.end(); ++boid_it) {
            if ((id != boid_it->getId()) && (pos.squareDistance(boid_it->getPos()) < sqMaxDist)) {
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
    if (speed.length() > 8) {
        speed = speed.getNormalized() * 8;
    }

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
    if (type == BoidMisc::REGULAR) {
        ofSetColor(ofColor::white);
        ofCircle(pos, 2);
    }
    else if (type == BoidMisc::PREDATOR) {
        ofSetColor(ofColor::red);
        ofCircle(pos, 3);
    }
    else {
        ofLogNotice("boid", "unexpected boid type at draw.");
    }
}

void Boid::exit(void) {
    for (std::vector<Behaviour*>::iterator beh_it = behaviours.begin(); beh_it != behaviours.end(); ++beh_it) {
        delete *beh_it;
    }
}

ofVec2f Boid::getPos(void) {
    return pos;
}

ofVec2f Boid::getSpeed(void) {
    return speed;
}

ofVec2f Boid::getAccel(void) {
    return accel;
}

BoidMisc::Type Boid::getType(void) {
    return type;
}

int Boid::getMaxX(void) {
    return maxX;
}

int Boid::getMaxY(void) {
    return maxY;
}

int Boid::getId(void) {
    return id;
}

int Boid::getNextID(void) {
    return idGen++;
}

int Boid::idGen;
