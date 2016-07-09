#include "Boid.h"

#include "ofMath.h"
#include "ofGraphics.h"
#include "Behaviour.h"

Boid::Boid(void)
{
    id = getNextID();
}

void Boid::setup(int w, int h, BoidMisc::Type type, float maxDist, int behaviourPeriod, float maxSpeed, std::vector<Behaviour*> behaviours)
{
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
    this->maxSpeed = maxSpeed;

    accel.x = 0;
    accel.y = 0;

    this->behaviours = behaviours;
}

void Boid::setupGraphics(ofColor color, int size)
{
    this->color = color;
    this->size = size;
}

void Boid::calculateUpdate(std::vector<Boid> &flock)
{
    if ((++noBehaviourUpdates) >= behaviourPeriod) {
        noBehaviourUpdates = 0;

        float sqMaxDist = maxDist * maxDist;

        std::vector<Boid*> nearbyBoids;
        for (auto &boid : flock) {
            if ((id != boid.getId()) && (pos.squareDistance(boid.getPos()) < sqMaxDist)) {
                nearbyBoids.push_back(&boid);
            }
        }

        nextAccel = accel;
        for (auto &behaviour : behaviours) {
            nextAccel += behaviour->apply(this, nearbyBoids);
        }
        nextAccel /= behaviours.size() + 1; // +1 because we're also taking into account our old acceleration
    }
}

void Boid::update(void)
{
    accel = nextAccel;

    speed += accel;
    if (speed.length() > maxSpeed) {
        speed = speed.getNormalized() * maxSpeed;
    }

    pos += speed;

    // Horizontal wrap-around
    if (pos.x > maxX) {
        pos.x -= maxX;
    }
    else if (pos.x < 0) {
        pos.x += maxX;
    }

    // Vertical wrap-around
    if (pos.y > maxY) {
        pos.y -= maxY;
    }
    else if (pos.y < 0) {
        pos.y += maxY;
    }
}

void Boid::draw(void)
{
    ofSetColor(color);
    ofDrawCircle(pos, size);
}

void Boid::exit(void)
{
    for (auto &behaviour : behaviours) {
        delete behaviour;
    }
}

ofVec2f Boid::getPos(void)
{
    return pos;
}

ofVec2f Boid::getSpeed(void)
{
    return speed;
}

ofVec2f Boid::getAccel(void)
{
    return accel;
}

float Boid::getMaxSpeed(void)
{
    return maxSpeed;
}

BoidMisc::Type Boid::getType(void)
{
    return type;
}

int Boid::getMaxX(void)
{
    return maxX;
}

int Boid::getMaxY(void)
{
    return maxY;
}

int Boid::getId(void)
{
    return id;
}

int Boid::getNextID(void)
{
    return idGen++;
}

int Boid::idGen;
