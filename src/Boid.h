#ifndef _BOID_H
#define _BOID_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"
#include "Config.h"

#include <vector>
#include "ofVec2f.h"
#include "ofColor.h"

class Boid
{
public:
    Boid(BoidMisc::Type type, const std::vector<Behaviour*> &behaviours);

    // update is carried out in two steps: first the new acceleration is calculated in calculateUpdate(),
    // and then the Boid's speed and position are updated in update(). Because calculateUpdate()'s result
    // depends on the flock's speed and position, update should only be called after calculateUpdate
    // has been called on the whole flock.
    void calculateUpdate(const std::vector<Boid> &flock);
    void update(void);

    void draw(void) const;

    ofVec2f getPos(void) const;
    ofVec2f getSpeed(void) const;
    ofVec2f getAccel(void) const;

    BoidMisc::Type getType(void) const;

    int getId(void) const;

private:
    int id;

    BoidMisc::Type type;
    const Config::Boid &config;

    const std::vector<Behaviour*> &behaviours;

    ofVec2f pos;
    ofVec2f speed;
    ofVec2f accel;
    ofVec2f next_accel; // calculated by calculateUpdate, only used internally

    static int getNextID(void);
    static int id_gen;
};

#endif // _BOID_H
