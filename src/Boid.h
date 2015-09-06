#ifndef _BOID_H
#define _BOID_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include "ofVec2f.h"

class Boid {
public:
    Boid(void);

    void setup(int w, int h, BoidMisc::Type type, float maxDist, int behaviourPeriod, float maxSpeed, std::vector<Behaviour*> behaviours);

    // update is carried out in two steps: first the new acceleration is calculated in calculateUpdate(),
    // and then the Boid's speed and position are updated in update(). Because calculateUpdate()'s result
    // depends on the flock's speed and position, update should only be called after calculateUpdate
    // has been called on the whole flock.
    void calculateUpdate(std::vector<Boid> &flock);
    void update(void);

    void draw(void);
    void exit(void);

    ofVec2f getPos(void);
    ofVec2f getSpeed(void);
    ofVec2f getAccel(void);

    float getMaxSpeed(void);

    BoidMisc::Type getType(void);

    int getMaxX(void);
    int getMaxY(void);

    int getId(void);

private:
    int maxX;
    int maxY;

    float maxDist;

    int behaviourPeriod;
    int noBehaviourUpdates;

    ofVec2f pos;
    ofVec2f speed;
    ofVec2f accel;
    ofVec2f nextAccel; // calculated by calculateUpdate, only used internally

    float maxSpeed;

    std::vector<Behaviour*> behaviours;

    BoidMisc::Type type;

    int id;

    static int getNextID(void);
    static int idGen;
};

#endif // _BOID_H
